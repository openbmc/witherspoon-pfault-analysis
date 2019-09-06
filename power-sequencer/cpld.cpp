/**
 * cpld.cpp & cpld.hpp are added for Mihawk platform 
 * by reference "witherspoon-pfault-analysis" architecture.
 * Andy YF Wang<Andy_YF_Wang@wistron.com>
 */
#include "config.h"
#include <iostream>		
#include "cpld.hpp"

#include "names_values.hpp"
#include "utility.hpp"

#include <elog-errors.hpp>
#include <map>
#include <memory>
#include <org/open_power/Witherspoon/Fault/error.hpp>
#include <phosphor-logging/elog.hpp>
#include <phosphor-logging/log.hpp>
#include <xyz/openbmc_project/Common/Device/error.hpp>


#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string>
#include <chrono>


extern "C" {
#include <linux/i2c.h>
#include <i2c/smbus.h>
#include <linux/i2c-dev.h>
}

#define MAX 32

// SMLink Status Register(PSU Register)
const static constexpr size_t StatusReg = 0x05;

// SMLink Status Register(Interrupt-control-bit Register)
const static constexpr size_t StatusReg_1 = 0x20;

// SMLink Status Register(Power-on error code Register)
const static constexpr size_t StatusReg_2 = 0x21;


using namespace std;	
namespace witherspoon
{
namespace power
{
const auto DEVICE_NAME = "CPLD"s;

namespace fs = std::filesystem;
using namespace phosphor::logging;
using namespace sdbusplus::org::open_power::Witherspoon::Fault::Error;

namespace device_error = sdbusplus::xyz::openbmc_project::Common::Device::Error;


CPLD::CPLD(size_t instance, sdbusplus::bus::bus& bus) :
    Device(DEVICE_NAME, instance),
     bus(bus)
{
}

void CPLD::onFailure()
{
        
		bool pError = checkPSUdevice();
		bool vError = checkPoweronFault();

        if (pError==1)
		{
			//If PSU not present, report the error log & event.
			std::cerr << "CPLD : PSU Present Error !" << endl;
			report<PSUPresentError>();
		}
		else if(pError==0)
		{
				
			// If PSU isn't enble and the interrupt of power_on_error is switch on,
			// read CPLD_register error code to analyze and report the error log & event.
			if (vError==1)
			{
				std::cerr << "CPLD : Power_ON error !" << endl;
				report<PowerOnError>();
				int busId=11, slaveAddr=0x40;
				int errorcode;
				errorcode=ReadFromCPLDPSUErrorCode(busId, slaveAddr);
		

				if(errorcode==1)
				{
					std::cerr << "Power_on error : psu0_pgood fail!" << endl;
					report<PowerOnErrorPSU0PGOODFail>();
				}
				else if(errorcode==2)
				{
					std::cerr << "Power_on error : psu1_pgood fail!" << endl;
					report<PowerOnErrorPSU1PGOODFail>();
				}
				else if(errorcode==3)
				{
					std::cerr << "Power_on error : 240Va_Fault_A fail!" << endl;
					report<PowerOnError240VaFaultAFail>();
				}
				else if(errorcode==4)
				{
					std::cerr << "Power_on error : 240Va_Fault_B fail!" << endl;
					report<PowerOnError240VaFaultBFail>();
				}
				else if(errorcode==5)
				{
					std::cerr << "Power_on error : 240Va_Fault_C fail!" << endl;
					report<PowerOnError240VaFaultCFail>();
				}
				else if(errorcode==6)
				{
					std::cerr << "Power_on error : 240Va_Fault_D fail!" << endl;
					report<PowerOnError240VaFaultDFail>();
				}
				else if(errorcode==7)
				{
					std::cerr << "Power_on error : 240Va_Fault_E fail!" << endl;
					report<PowerOnError240VaFaultEFail>();
				}
				else if(errorcode==8)
				{
					std::cerr << "Power_on error : 240Va_Fault_F fail!" << endl;
					report<PowerOnError240VaFaultFFail>();
				}
				else if(errorcode==9)
				{
					std::cerr << "Power_on error : 240Va_Fault_G fail!" << endl;
					report<PowerOnError240VaFaultGFail>();
				}
				else if(errorcode==10)
				{
					std::cerr << "Power_on error : 240Va_Fault_H fail!" << endl;
					report<PowerOnError240VaFaultHFail>();
				}
				else if(errorcode==11)
				{
					std::cerr << "Power_on error : 240Va_Fault_J fail!" << endl;
					report<PowerOnError240VaFaultJFail>();
				}
			
			}
		}
}

void CPLD::analyze()
{
	bool pError = checkPSUdevice();
	if (pError==1)
	{
		//If PSU not present, report the error log & event.
		std::cerr << "CPLD : PSU Present Error !" << endl;
		report<PSUPresentError>();
	}
	
}

//Read CPLD_register error code and return the result to analyze.
int CPLD::ReadFromCPLDPSUErrorCode(int bus, int Addr)
{
    std::string i2cBus = "/dev/i2c-" + std::to_string(bus);
	
	
	//open i2c device(CPLD-PSU-register table)
    int fd = open(i2cBus.c_str(), O_RDWR | O_CLOEXEC);
    if (fd < 0)
    {
		//report<PgoodFailure>();
        std::cerr << "Unable to open i2c device \n";
        return -1;
    }
	
	//set i2c slave address
    if (ioctl(fd, I2C_SLAVE_FORCE, Addr) < 0)
    {
        std::cerr << "Unable to set device address\n";
        close(fd);
        return -1;
    }

	//check whether support i2c function
    unsigned long funcs = 0;
    if (ioctl(fd, I2C_FUNCS, &funcs) < 0)
    {
        std::cerr << "Not support I2C_FUNCS \n";
        close(fd);
        return -1;
    }

	//check whether support i2c-read function
    if (!(funcs & I2C_FUNC_SMBUS_READ_BYTE_DATA))
    {
        std::cerr << "Not support I2C_FUNC_SMBUS_READ_BYTE_DATA \n";
        close(fd);
        return -1;
    }

    int statusValue_2;
    //unsigned int statusMask = RegMask;
    unsigned int statusReg_2 = StatusReg_2;

    statusValue_2 = i2c_smbus_read_byte_data(fd, statusReg_2);
	

    close(fd);

    if (statusValue_2 < 0)
    {
        std::cerr << "i2c_smbus_read_byte_data failed \n";
        return -1;
    }

	
	//return the i2c-read data
    return statusValue_2;
}

//Check PSU present.
bool CPLD::checkPSUdevice()
{
	bool result = 0;
	int bin[MAX], num;
	int i=0, length=0;
	int busId=11, slaveAddr=0x40;
	std::string i2cBus = "/dev/i2c-" + std::to_string(busId);
	
	
	//open i2c device(CPLD-PSU-register table)
    int fd = open(i2cBus.c_str(), O_RDWR | O_CLOEXEC);
    if (fd < 0)
    {
		//report<PgoodFailure>();
        std::cerr << "Unable to open i2c device \n";
        return -1;
    }
	
	//set i2c slave address
    if (ioctl(fd, I2C_SLAVE_FORCE, slaveAddr) < 0)
    {
        std::cerr << "Unable to set device address\n";
        close(fd);
        return -1;
    }

	//check whether support i2c function
    unsigned long funcs = 0;
    if (ioctl(fd, I2C_FUNCS, &funcs) < 0)
    {
        std::cerr << "Not support I2C_FUNCS \n";
        close(fd);
        return -1;
    }

	//check whether support i2c-read function
    if (!(funcs & I2C_FUNC_SMBUS_READ_BYTE_DATA))
    {
        std::cerr << "Not support I2C_FUNC_SMBUS_READ_BYTE_DATA \n";
        close(fd);
        return -1;
    }

    int statusValue;
    unsigned int statusReg = StatusReg;

    statusValue = i2c_smbus_read_byte_data(fd, statusReg);
	

    close(fd);

    if (statusValue < 0)
    {
        std::cerr << "i2c_smbus_read_byte_data failed \n";
        return -1;
    }
	
	//Transfer decimal value to binary value
	num = statusValue;
	do
	{
		bin[i] = num % 2 ;
		num = num / 2 ;
		i++;
		length++;
	}while(num != 1);
	bin[length] = num;
	length++;
	
	if (bin[3] == 1 && bin[4]==1)
	{
		//If power_on-interrupt-bit is read as 1, 
		//switch on the flag.
		result = 1;
	}
	else
	{
		result = 0;
	}


    return result;
}

//Check for PoweronFault
bool CPLD::checkPoweronFault()
{
	bool result_1 = 0;
	int bin1[MAX], num1;
	int i=0, length=0;
	int busId=11, slaveAddr=0x40;
	std::string i2cBus = "/dev/i2c-" + std::to_string(busId);
	
	
	//open i2c device(CPLD-PSU-register table)
    int fd = open(i2cBus.c_str(), O_RDWR | O_CLOEXEC);
    if (fd < 0)
    {
		//report<PgoodFailure>();
        std::cerr << "Unable to open i2c device \n";
        return -1;
    }
	
	//set i2c slave address
    if (ioctl(fd, I2C_SLAVE_FORCE, slaveAddr) < 0)
    {
        std::cerr << "Unable to set device address\n";
        close(fd);
        return -1;
    }

	//check whether support i2c function
    unsigned long funcs = 0;
    if (ioctl(fd, I2C_FUNCS, &funcs) < 0)
    {
        std::cerr << "Not support I2C_FUNCS \n";
        close(fd);
        return -1;
    }

	//check whether support i2c-read function
    if (!(funcs & I2C_FUNC_SMBUS_READ_BYTE_DATA))
    {
        std::cerr << "Not support I2C_FUNC_SMBUS_READ_BYTE_DATA \n";
        close(fd);
        return -1;
    }

    int statusValue_1;
    unsigned int statusReg_1 = StatusReg_1;

    statusValue_1 = i2c_smbus_read_byte_data(fd, statusReg_1);
	

    close(fd);

    if (statusValue_1 < 0)
    {
        std::cerr << "i2c_smbus_read_byte_data failed \n";
        return -1;
    }
	
	//Transfer decimal value to binary value
	num1 = statusValue_1;
	do
	{
		bin1[i] = num1 % 2 ;
		num1 = num1 / 2 ;
		i++;
		length++;
	}while(num1 != 1);
	bin1[length] = num1;
	length++;
	
	if (bin1[5] == 1)
	{
		//If power_on-interrupt-bit is read as 1, 
		//switch on the flag.
		result_1 = 1;
	}


    return result_1;
}


} // namespace power
} // namespace witherspoon
