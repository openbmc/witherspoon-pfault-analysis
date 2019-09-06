#pragma once

#include "device.hpp"
#include "pmbus.hpp"
#include <algorithm>
#include <filesystem>

#include <sdbusplus/bus.hpp>

namespace witherspoon
{
namespace power
{

/**
 * @class CPLD
 *
 * This class implements fault analysis for the CPLD
 * power sequencer device.
 *
 */
class CPLD : public Device
{
  public:
    CPLD() = delete;
    ~CPLD() = default;
    CPLD(const CPLD&) = delete;
    CPLD& operator=(const CPLD&) = delete;
    CPLD(CPLD&&) = default;
    CPLD& operator=(CPLD&&) = default;

    /**
     * Constructor
     *
     * @param[in] instance - the device instance number
     * @param[in] bus - D-Bus bus object
     */
    CPLD(size_t instance, sdbusplus::bus::bus& bus);

    /**
     * Analyzes the device for errors when the device is
     * known to be in an error state.  A log will be created.
     */
    void onFailure() override;

    /**
     * Checks the device for errors and only creates a log
     * if one is found.
     */
    void analyze() override;

    /**
     * Clears faults in the device
     */
    void clearFaults() override
	{	
	}
	
  private:
	/**
	 * If checkPoweronFault() returns "true", 
	 * use ReadFromCPLDPSUErrorCode() to read CPLD-error-code-register 
	 * to analyze the fail reason.
	 */
	int ReadFromCPLDPSUErrorCode(int bus, int Addr);

    /**
     * Checks for PoweronFault on the CPLD-power_on-error-interrupt-bit-register whether is transfered to "1".
     *
     * @return bool - true if power_on fail.
     */
    bool checkPoweronFault();

    /**
     * Checks for PSU0 & PSU1 whether are "prensent".
     *
     * @return bool - true if PSU0 & PSU1 aren't "present".
     */
    bool checkPSUdevice();

    /**
     * The D-Bus bus object
     */
    sdbusplus::bus::bus& bus;

};

} // namespace power
} // namespace witherspoon
