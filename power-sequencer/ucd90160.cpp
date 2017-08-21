/**
 * Copyright © 2017 IBM Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <map>
#include <memory>
#include <phosphor-logging/elog.hpp>
#include <phosphor-logging/log.hpp>
#include <elog-errors.hpp>
#include <xyz/openbmc_project/Sensor/Device/error.hpp>
#include <xyz/openbmc_project/Control/Device/error.hpp>
#include <xyz/openbmc_project/Power/Fault/error.hpp>
#include "ucd90160.hpp"

namespace witherspoon
{
namespace power
{

using namespace std::string_literals;

const auto CLEAR_LOGGED_FAULTS = "clear_logged_faults"s;
const auto MFR_STATUS = "mfr_status"s;

const auto DEVICE_NAME = "UCD90160"s;
const auto DRIVER_NAME = "ucd9000"s;
constexpr auto NUM_PAGES = 16;

using namespace pmbus;
using namespace phosphor::logging;
using namespace sdbusplus::xyz::openbmc_project::Control::Device::Error;
using namespace sdbusplus::xyz::openbmc_project::Sensor::Device::Error;
using namespace sdbusplus::xyz::openbmc_project::Power::Fault::Error;

UCD90160::UCD90160(size_t instance) :
    Device(DEVICE_NAME, instance),
    interface(std::get<ucd90160::pathField>(
                deviceMap.find(instance)->second),
              DRIVER_NAME,
              instance)
{
}

void UCD90160::onFailure()
{
    try
    {
        auto voutError = checkVOUTFaults();

        auto pgoodError = checkPGOODFaults(false);

        //Not a voltage or PGOOD fault, but we know something
        //failed so still create an error log.
        if (!voutError && !pgoodError)
        {
            createPowerFaultLog();
        }
    }
    catch (ReadFailure& e)
    {
        if (!accessError)
        {
            commit<ReadFailure>();
            accessError = true;
        }
    }
}

void UCD90160::analyze()
{
    try
    {
        //Note: Voltage faults are always fatal, so they just
        //need to be analyzed in onFailure().

        checkPGOODFaults(true);
    }
    catch (ReadFailure& e)
    {
        if (!accessError)
        {
            commit<ReadFailure>();
            accessError = true;
        }
    }
}

uint16_t UCD90160::readStatusWord()
{
    uint16_t statusWord = 0;

    interface.read(STATUS_WORD,
            Type::Debug,
            reinterpret_cast<uint8_t*>(&statusWord),
            sizeof(statusWord));

    return statusWord;
}

uint32_t UCD90160::readMFRStatus()
{
    uint32_t mfrStatus = 0;

    interface.read(MFR_STATUS,
            Type::DeviceDebug,
            reinterpret_cast<uint8_t*>(&mfrStatus),
            sizeof(mfrStatus));

    return mfrStatus;
}

void UCD90160::clearFaults()
{
    try
    {
        interface.write(CLEAR_LOGGED_FAULTS, 1, Type::Base);
    }
    catch (WriteFailure& e)
    {
        if (!accessError)
        {
            log<level::ERR>("UCD90160 clear logged faults command failed");
            commit<WriteFailure>();
            accessError = true;
        }
    }
}

bool UCD90160::checkVOUTFaults()
{
    bool errorCreated = false;
    auto statusWord = readStatusWord();

    //The status_word register has a summary bit to tell us
    //if each page even needs to be checked
    if (!(statusWord & status_word::VOUT_FAULT))
    {
        return errorCreated;
    }

    for (size_t page = 0; page < NUM_PAGES; page++)
    {
        if (isVoutFaultLogged(page))
        {
            continue;
        }

        uint8_t vout = 0;
        auto statusVout = interface.insertPageNum(STATUS_VOUT, page);

        interface.read(statusVout,
                Type::Debug,
                &vout,
                sizeof(vout));

        //Any bit on is an error
        if (vout)
        {
            auto& railNames = std::get<ucd90160::railNamesField>
                (deviceMap.find(getInstance())->second);
            auto railName = railNames.at(page);
            auto mfrStatus = readMFRStatus();

            report<PowerSequencerVoltageFault>(
                    xyz::openbmc_project::Power::Fault::
                    PowerSequencerVoltageFault::RAIL(page),
                    xyz::openbmc_project::Power::Fault::
                    PowerSequencerVoltageFault::RAIL_NAME(railName.c_str()),
                    xyz::openbmc_project::Power::Fault::
                    PowerSequencerVoltageFault::STATUS_WORD(statusWord),
                    xyz::openbmc_project::Power::Fault::
                    PowerSequencerVoltageFault::STATUS_VOUT(vout),
                    xyz::openbmc_project::Power::Fault::
                    PowerSequencerVoltageFault::MFR_STATUS(mfrStatus));

            setVoutFaultLogged(page);
            errorCreated = true;
        }
    }

    return errorCreated;
}

bool UCD90160::checkPGOODFaults(bool polling)
{
    return false;
}

void UCD90160::createPowerFaultLog()
{

}

}
}
