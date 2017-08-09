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
#include <phosphor-logging/log.hpp>
#include <phosphor-logging/elog.hpp>
#include <xyz/openbmc_project/Sensor/Device/error.hpp>
#include <xyz/openbmc_project/Control/Device/error.hpp>
#include <xyz/openbmc_project/Power/Fault/error.hpp>
#include "elog-errors.hpp"
#include "power_supply.hpp"
#include "pmbus.hpp"
#include "utility.hpp"

using namespace phosphor::logging;
using namespace sdbusplus::xyz::openbmc_project::Control::Device::Error;
using namespace sdbusplus::xyz::openbmc_project::Sensor::Device::Error;
using namespace sdbusplus::xyz::openbmc_project::Power::Fault::Error;

using PowerSupplyUnderVoltageFaultStatusWord = xyz::openbmc_project::Power::
        Fault::PowerSupplyUnderVoltageFault::STATUS_WORD;

namespace witherspoon
{
namespace power
{
namespace psu
{
constexpr auto INVENTORY_OBJ_PATH = "/xyz/openbmc_project/inventory";
constexpr auto INVENTORY_INTERFACE = "xyz.openbmc_project.Inventory.Item";
constexpr auto PRESENT_PROP = "Present";

PowerSupply::PowerSupply(const std::string& name, size_t inst,
                         const std::string& objpath, const std::string& invpath,
                         sdbusplus::bus::bus& bus)
    : Device(name, inst), monitorPath(objpath), inventoryPath(invpath),
      bus(bus), pmbusIntf(objpath)
{
    updatePresence();

    using namespace sdbusplus::bus;
    auto present_obj_path = INVENTORY_OBJ_PATH + inventoryPath;
    presentMatch = std::make_unique<match_t>(bus,
                                             match::rules::propertiesChanged(
                                                     present_obj_path,
                                                     INVENTORY_INTERFACE),
                                             [this](auto& msg)
    {
        this->inventoryChanged(msg);
    });
}

void PowerSupply::analyze()
{
    using namespace witherspoon::pmbus;

    try
    {
        if (present)
        {
            auto curUVFault = pmbusIntf.readBit(VIN_UV_FAULT, Type::Hwmon);
            //TODO: 3 consecutive reads should be performed.
            // If 3 consecutive reads are seen, log the fault.
            // Driver gives cached value, read once a second.
            // increment for fault on, decrement for fault off, to deglitch.
            // If count reaches 3, we have fault. If count reaches 0, fault is
            // cleared.

            //TODO: INPUT FAULT or WARNING bit to check from STATUS_WORD
            // pmbus-core update to read high byte of STATUS_WORD?

            if ((curUVFault != vinUVFault) || inputFault)
            {

                if (curUVFault)
                {
                    std::uint16_t status_word = 0;
                    pmbusIntf.read(STATUS_WORD, Type::Debug,
                                   reinterpret_cast<std::uint8_t*>(&status_word),
                                   sizeof(status_word));

                    report<PowerSupplyUnderVoltageFault>(
                        PowerSupplyUnderVoltageFaultStatusWord(status_word));
                    vinUVFault = true;
                }
                else
                {
                    log<level::INFO>("VIN_UV_FAULT cleared",
                                     entry("POWERSUPPLY=%s",
                                           inventoryPath.c_str()));
                    vinUVFault = false;
                }
            }
        }
    }
    catch (ReadFailure& e)
    {
        if (!readFailLogged)
        {
            commit<ReadFailure>();
            readFailLogged = true;
            // TODO - Need to reset that to false at start of power on, or
            // presence change.
        }
    }

    return;
}

void PowerSupply::inventoryChanged(sdbusplus::message::message& msg)
{
    std::string msgSensor;
    std::map<std::string, sdbusplus::message::variant<uint32_t, bool>> msgData;
    msg.read(msgSensor, msgData);

    // Check if it was the Present property that changed.
    auto valPropMap = msgData.find(PRESENT_PROP);
    if (valPropMap != msgData.end())
    {
        present = sdbusplus::message::variant_ns::get<bool>(valPropMap->second);

        if (present)
        {
            readFailLogged = false;
            vinUVFault = false;
        }
    }

    return;
}

void PowerSupply::updatePresence()
{
    // Use getProperty utility function to get presence status.
    std::string path = INVENTORY_OBJ_PATH + inventoryPath;
    std::string service = "xyz.openbmc_project.Inventory.Manager";
    util::getProperty(INVENTORY_INTERFACE, PRESENT_PROP, path,
                      service, bus, this->present);
}

void PowerSupply::clearFaults()
{
    //TODO - Clear faults at pre-poweron. openbmc/openbmc#1736
    return;
}

}
}
}
