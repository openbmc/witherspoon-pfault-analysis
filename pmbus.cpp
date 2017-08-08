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

namespace witherspoon
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

bool PMBus::readBitInPage(const std::string& name,
                          size_t page,
                          Type type)
{
    auto pagedBit = insertPageNum(name, page);
    return readBit(pagedBit, type);
}

bool PMBus::readBit(const std::string& name, Type type)
{
    unsigned long int value = 0;
    std::ifstream file;
    fs::path path{basePath};

    if (type == Type::Hwmon)
    {
        path /= hwmonRelPath;
    }

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

        log<level::ERR>("Failed to read sysfs file",
                entry("FILENAME=%s", path.c_str()));

        elog<ReadFailure>(xyz::openbmc_project::Sensor::Device::
                          ReadFailure::CALLOUT_ERRNO(rc),
                          xyz::openbmc_project::Sensor::Device::
                          ReadFailure::CALLOUT_DEVICE_PATH(
                              fs::canonical(basePath).c_str()));
    }

    return value != 0;
}

void PMBus::read(const std::string& name, Type type, std::uint8_t* data, size_t length)
{
    std::ifstream file;
    fs::path path{basePath};

    if (type == Type::Hwmon)
    {
        path /= hwmonRelPath;
    }

    path /= name;

    file.exceptions(std::ifstream::failbit |
                    std::ifstream::badbit |
                    std::ifstream::eofbit);

    try
    {
        char* err = NULL;
        unsigned long value = 0;
        std::string val{1, '\0'};

        file.open(path);

        while((length > 0) && (!*err))
        {
            // The files will be in ASCII format, so each byte will be two
            // characters. Read in 2 bytes of ASCII for each 1 byte of data.
            file.read(&val[0], 2);
            length--;
            value = strtoul(val.c_str(), &err, 16);

            if (*err)
            {
                log<level::ERR>("Invalid character in sysfs file",
                                entry("FILE=%s", path.c_str()),
                                entry("CONTENTS=%s", val.c_str()));

                //Catch below and handle as a read failure
                elog<InternalFailure>();
            }

            *data = value;
             data++;
        }

    }
    catch (std::exception& e)
    {
        auto rc = errno;

        log<level::ERR>("Failed to read sysfs file",
                entry("FILENAME=%s", path.c_str()));

        elog<ReadFailure>(xyz::openbmc_project::Sensor::Device::
                          ReadFailure::CALLOUT_ERRNO(rc),
                          xyz::openbmc_project::Sensor::Device::
                          ReadFailure::CALLOUT_DEVICE_PATH(
                              fs::canonical(basePath).c_str()));
    }

    return;
}

void PMBus::write(const std::string& name, int value, Type type)
{
    std::ofstream file;
    fs::path path{basePath};

    if (type == Type::Hwmon)
    {
        path /= hwmonRelPath;
    }

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

        log<level::ERR>("Failed to write sysfs file",
                entry("FILENAME=%s", path.c_str()));

        elog<WriteFailure>(xyz::openbmc_project::Control::Device::
                           WriteFailure::CALLOUT_ERRNO(rc),
                           xyz::openbmc_project::Control::Device::
                           WriteFailure::CALLOUT_DEVICE_PATH(
                               fs::canonical(basePath).c_str()));
    }
}

void PMBus::findHwmonRelativePath()
{
    fs::path path{basePath};
    path /= "hwmon";

    //look for <basePath>/hwmon/hwmonN/
    for (auto& f : fs::directory_iterator(path))
    {
        if ((f.path().filename().string().find("hwmon") !=
            std::string::npos) &&
            (fs::is_directory(f.path())))
        {
            hwmonRelPath = "hwmon";
            hwmonRelPath /= f.path().filename();
            break;
        }
    }

    //Don't really want to crash here, just log it
    //and let accesses fail later
    if (hwmonRelPath.empty())
    {
        log<level::ERR>("Unable to find hwmon directory "
                        "in device base path",
                        entry("DEVICE_PATH=%s", basePath.c_str()));
    }

}

}
}
