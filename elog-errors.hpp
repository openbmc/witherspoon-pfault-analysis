// This file was autogenerated.  Do not edit!
// See elog-gen.py for more details
#pragma once

#include <string>
#include <tuple>
#include <type_traits>
#include <sdbusplus/exception.hpp>
#include <phosphor-logging/log.hpp>
#include <phosphor-logging/elog.hpp>

namespace sdbusplus
{
namespace xyz
{
namespace openbmc_project
{
namespace Power
{
namespace Fault
{
namespace Error
{
    struct PowerOnFailure;
} // namespace Error
} // namespace Fault
} // namespace Power
} // namespace openbmc_project
} // namespace xyz
} // namespace sdbusplus


namespace phosphor
{

namespace logging
{

namespace xyz
{
namespace openbmc_project
{
namespace Power
{
namespace Fault
{
namespace _PowerOnFailure
{


}  // namespace _PowerOnFailure

struct PowerOnFailure
{
    static constexpr auto L = level::ERR;
    using metadata_types = std::tuple<>;

};

} // namespace Fault
} // namespace Power
} // namespace openbmc_project
} // namespace xyz


namespace details
{

template <>
struct map_exception_type<sdbusplus::xyz::openbmc_project::Power::Fault::Error::PowerOnFailure>
{
    using type = xyz::openbmc_project::Power::Fault::PowerOnFailure;
};

}


} // namespace logging

} // namespace phosphor
