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
    struct Shutdown;
} // namespace Error
} // namespace Fault
} // namespace Power
} // namespace openbmc_project
} // namespace xyz
} // namespace sdbusplus

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
    struct PowerSupplyUnderVoltageFault;
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
namespace _PowerSupplyUnderVoltageFault
{

struct STATUS_WORD
{
    static constexpr auto str = "STATUS_WORD=%d";
    static constexpr auto str_short = "STATUS_WORD";
    using type = std::tuple<std::decay_t<decltype(str)>,uint16_t>;
    explicit constexpr STATUS_WORD(uint16_t a) : _entry(entry(str, a)) {};
    type _entry;
};

}  // namespace _PowerSupplyUnderVoltageFault

struct PowerSupplyUnderVoltageFault
{
    static constexpr auto L = level::ERR;
    using STATUS_WORD = _PowerSupplyUnderVoltageFault::STATUS_WORD;
    using metadata_types = std::tuple<STATUS_WORD>;

};

} // namespace Fault
} // namespace Power
} // namespace openbmc_project
} // namespace xyz


namespace details
{

template <>
struct map_exception_type<sdbusplus::xyz::openbmc_project::Power::Fault::Error::PowerSupplyUnderVoltageFault>
{
    using type = xyz::openbmc_project::Power::Fault::PowerSupplyUnderVoltageFault;
};

}

namespace xyz
{
namespace openbmc_project
{
namespace Power
{
namespace Fault
{
namespace _Shutdown
{


}  // namespace _Shutdown

struct Shutdown
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
struct map_exception_type<sdbusplus::xyz::openbmc_project::Power::Fault::Error::Shutdown>
{
    using type = xyz::openbmc_project::Power::Fault::Shutdown;
};

}


} // namespace logging

} // namespace phosphor
