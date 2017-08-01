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
#include <experimental/filesystem>
#include <fstream>
#include <phosphor-logging/elog.hpp>
#include <phosphor-logging/elog-errors.hpp>
#include <xyz/openbmc_project/Common/error.hpp>
#include <xyz/openbmc_project/Control/Device/error.hpp>
#include <xyz/openbmc_project/Sensor/Device/error.hpp>
#include "pmbus.hpp"

namespace phosphor
{
namespace pmbus
{

using namespace phosphor::logging;
using namespace sdbusplus::xyz::openbmc_project::Common::Error;
using namespace sdbusplus::xyz::openbmc_project::Control::Device::Error;
using namespace sdbusplus::xyz::openbmc_project::Sensor::Device::Error;
namespace fs = std::experimental::filesystem;

std::string PMBus::insertPageNum(const std::string& templateName,
                                 size_t page)
{
    auto name = templateName;

    //insert the page where the P was
    auto pos = name.find('P');
    if (pos != std::string::npos)
    {
        name.replace(pos, 1, std::to_string(page));
    }

    return name;
}

bool PMBus::readBitInPage(const std::string& name, size_t page)
{
    auto pagedBit = insertPageNum(name, page);
    return readBit(pagedBit);
}

bool PMBus::readBit(const std::string& name)
{
    unsigned long int value = 0;
    std::ifstream file;
    fs::path path{basePath};

    path /= name;

    file.exceptions(std::ifstream::failbit |
                    std::ifstream::badbit |
                    std::ifstream::eofbit);

    try
    {
        char* err = NULL;
        std::string val{1, '\0'};

        file.open(path);
        file.read(&val[0], 1);

        value = strtoul(val.c_str(), &err, 10);

        if (*err)
        {
            log<level::ERR>("Invalid character in sysfs file",
                            entry("FILE=%s", path.c_str()),
                            entry("CONTENTS=%s", val.c_str()));

            //Catch below and handle as a read failure
            elog<InternalFailure>();
        }
    }
    catch (std::exception& e)
    {
        auto rc = errno;

        elog<ReadFailure>(xyz::openbmc_project::Sensor::Device::
                          ReadFailure::CALLOUT_ERRNO(rc),
                          xyz::openbmc_project::Sensor::Device::
                          ReadFailure::CALLOUT_DEVICE_PATH(
                              fs::canonical(basePath).c_str()));
    }

    return value != 0;
}

void PMBus::write(const std::string& name, int value)
{
    std::ofstream file;
    fs::path path{basePath};

    path /= name;

    file.exceptions(std::ofstream::failbit |
                    std::ofstream::badbit |
                    std::ofstream::eofbit);

    try
    {
        file.open(path);
        file << value;
    }
    catch (const std::exception& e)
    {
        auto rc = errno;

        elog<WriteFailure>(xyz::openbmc_project::Control::Device::
                           WriteFailure::CALLOUT_ERRNO(rc),
                           xyz::openbmc_project::Control::Device::
                           WriteFailure::CALLOUT_DEVICE_PATH(
                               fs::canonical(basePath).c_str()));
    }
}

}
}
