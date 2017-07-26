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
#include <iostream>
#include <phosphor-logging/log.hpp>
#include <systemd/sd-daemon.h>
#include "argument.hpp"
#include "event.hpp"
#include "power_supply.hpp"
#include "device_monitor.hpp"

using namespace phosphor::power;
using namespace phosphor::logging;

int main(int argc, char* argv[])
{
    auto rc = -1;
    auto options = ArgumentParser(argc, argv);

    auto objpath = (options)["path"];
    auto instnum = (options)["instance"];
    auto invpath = (options)["inventory"];
    if (argc < 3)
    {
        std::cerr << std::endl << "Too few arguments" << std::endl;
        options.usage(argv);
    }
    else if (objpath == ArgumentParser::emptyString)
    {
        log<level::ERR>("Device monitoring path argument required");
    }
    else if (instnum == ArgumentParser::emptyString)
    {
        log<level::ERR>("Device monitoring instance number argument required");
    }
    else if (invpath == ArgumentParser::emptyString)
    {
        log<level::ERR>("Device monitoring inventory path argument required");
    }
    else
    {
        auto objname = "psu" + instnum;
        auto instance = std::stoul(instnum);
        auto psuDevice = std::make_unique<psu::PowerSupply>(objname, instance,
                                                            objpath, invpath);
        log<level::INFO>("new bus");
        auto bus = sdbusplus::bus::new_default();
        sd_event* events = nullptr;

        auto r = sd_event_default(&events);
        if (r < 0)
        {
            log<level::ERR>("Failed call to sd_event_default()",
                            entry("ERROR=%s", strerror(-r)));
            return -1;
        }

        phosphor::power::event::Event eventPtr{events};

        //Attach the event object to the bus object so we can
        //handle both sd_events (for the timers) and dbus signals.
        bus.attach_event(eventPtr.get(), SD_EVENT_PRIORITY_NORMAL);

        // TODO: Use inventory path to subscribe to signal change for power supply presence.

        auto pollInterval = std::chrono::milliseconds(1000);
        DeviceMonitor mainloop(std::move(psuDevice), eventPtr, pollInterval);
        mainloop.run();

        rc = 0;
    }

    return rc;
}
// vim: tabstop=8 expandtab shiftwidth=4 softtabstop=4
