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

namespace sdbusplus
{
namespace xyz
{
namespace openbmc_project
{
namespace Common
{
namespace Callout
{
namespace Error
{
    struct GPIO;
} // namespace Error
} // namespace Callout
} // namespace Common
} // namespace openbmc_project
} // namespace xyz
} // namespace sdbusplus

namespace sdbusplus
{
namespace xyz
{
namespace openbmc_project
{
namespace Common
{
namespace Callout
{
namespace Error
{
    struct Inventory;
} // namespace Error
} // namespace Callout
} // namespace Common
} // namespace openbmc_project
} // namespace xyz
} // namespace sdbusplus

namespace sdbusplus
{
namespace xyz
{
namespace openbmc_project
{
namespace Common
{
namespace Callout
{
namespace Error
{
    struct IIC;
} // namespace Error
} // namespace Callout
} // namespace Common
} // namespace openbmc_project
} // namespace xyz
} // namespace sdbusplus

namespace sdbusplus
{
namespace xyz
{
namespace openbmc_project
{
namespace Common
{
namespace Callout
{
namespace Error
{
    struct Device;
} // namespace Error
} // namespace Callout
} // namespace Common
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

namespace sdbusplus
{
namespace xyz
{
namespace openbmc_project
{
namespace Common
{
namespace Callout
{
namespace Error
{
    struct IPMISensor;
} // namespace Error
} // namespace Callout
} // namespace Common
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
    struct PowerSequencerFault;
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
    struct PowerSequencerPGOODFault;
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
    struct GPUPowerFault;
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
    struct GPUOverTemp;
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
namespace Common
{
namespace Callout
{
namespace _Device
{

struct CALLOUT_ERRNO
{
    static constexpr auto str = "CALLOUT_ERRNO=%d";
    static constexpr auto str_short = "CALLOUT_ERRNO";
    using type = std::tuple<std::decay_t<decltype(str)>,int32_t>;
    explicit constexpr CALLOUT_ERRNO(int32_t a) : _entry(entry(str, a)) {};
    type _entry;
};
struct CALLOUT_DEVICE_PATH
{
    static constexpr auto str = "CALLOUT_DEVICE_PATH=%s";
    static constexpr auto str_short = "CALLOUT_DEVICE_PATH";
    using type = std::tuple<std::decay_t<decltype(str)>,const char*>;
    explicit constexpr CALLOUT_DEVICE_PATH(const char* a) : _entry(entry(str, a)) {};
    type _entry;
};

}  // namespace _Device

struct Device
{
    static constexpr auto L = level::ERR;
    using CALLOUT_ERRNO = _Device::CALLOUT_ERRNO;
    using CALLOUT_DEVICE_PATH = _Device::CALLOUT_DEVICE_PATH;
    using metadata_types = std::tuple<CALLOUT_ERRNO, CALLOUT_DEVICE_PATH>;

};

} // namespace Callout
} // namespace Common
} // namespace openbmc_project
} // namespace xyz


namespace details
{

template <>
struct map_exception_type<sdbusplus::xyz::openbmc_project::Common::Callout::Error::Device>
{
    using type = xyz::openbmc_project::Common::Callout::Device;
};

}

namespace xyz
{
namespace openbmc_project
{
namespace Common
{
namespace Callout
{
namespace _GPIO
{

struct CALLOUT_GPIO_NUM
{
    static constexpr auto str = "CALLOUT_GPIO_NUM=%u";
    static constexpr auto str_short = "CALLOUT_GPIO_NUM";
    using type = std::tuple<std::decay_t<decltype(str)>,uint32_t>;
    explicit constexpr CALLOUT_GPIO_NUM(uint32_t a) : _entry(entry(str, a)) {};
    type _entry;
};

}  // namespace _GPIO

struct GPIO
{
    static constexpr auto L = level::ERR;
    using CALLOUT_GPIO_NUM = _GPIO::CALLOUT_GPIO_NUM;
    using CALLOUT_ERRNO = xyz::openbmc_project::Common::Callout::Device::CALLOUT_ERRNO;
    using CALLOUT_DEVICE_PATH = xyz::openbmc_project::Common::Callout::Device::CALLOUT_DEVICE_PATH;
    using metadata_types = std::tuple<CALLOUT_GPIO_NUM, CALLOUT_ERRNO, CALLOUT_DEVICE_PATH>;

};

} // namespace Callout
} // namespace Common
} // namespace openbmc_project
} // namespace xyz


namespace details
{

template <>
struct map_exception_type<sdbusplus::xyz::openbmc_project::Common::Callout::Error::GPIO>
{
    using type = xyz::openbmc_project::Common::Callout::GPIO;
};

}

namespace xyz
{
namespace openbmc_project
{
namespace Common
{
namespace Callout
{
namespace _IIC
{

struct CALLOUT_IIC_BUS
{
    static constexpr auto str = "CALLOUT_IIC_BUS=%s";
    static constexpr auto str_short = "CALLOUT_IIC_BUS";
    using type = std::tuple<std::decay_t<decltype(str)>,const char*>;
    explicit constexpr CALLOUT_IIC_BUS(const char* a) : _entry(entry(str, a)) {};
    type _entry;
};
struct CALLOUT_IIC_ADDR
{
    static constexpr auto str = "CALLOUT_IIC_ADDR=0x%hx";
    static constexpr auto str_short = "CALLOUT_IIC_ADDR";
    using type = std::tuple<std::decay_t<decltype(str)>,uint16_t>;
    explicit constexpr CALLOUT_IIC_ADDR(uint16_t a) : _entry(entry(str, a)) {};
    type _entry;
};

}  // namespace _IIC

struct IIC
{
    static constexpr auto L = level::ERR;
    using CALLOUT_IIC_BUS = _IIC::CALLOUT_IIC_BUS;
    using CALLOUT_IIC_ADDR = _IIC::CALLOUT_IIC_ADDR;
    using CALLOUT_ERRNO = xyz::openbmc_project::Common::Callout::Device::CALLOUT_ERRNO;
    using CALLOUT_DEVICE_PATH = xyz::openbmc_project::Common::Callout::Device::CALLOUT_DEVICE_PATH;
    using metadata_types = std::tuple<CALLOUT_IIC_BUS, CALLOUT_IIC_ADDR, CALLOUT_ERRNO, CALLOUT_DEVICE_PATH>;

};

} // namespace Callout
} // namespace Common
} // namespace openbmc_project
} // namespace xyz


namespace details
{

template <>
struct map_exception_type<sdbusplus::xyz::openbmc_project::Common::Callout::Error::IIC>
{
    using type = xyz::openbmc_project::Common::Callout::IIC;
};

}

namespace xyz
{
namespace openbmc_project
{
namespace Common
{
namespace Callout
{
namespace _Inventory
{

struct CALLOUT_INVENTORY_PATH
{
    static constexpr auto str = "CALLOUT_INVENTORY_PATH=%s";
    static constexpr auto str_short = "CALLOUT_INVENTORY_PATH";
    using type = std::tuple<std::decay_t<decltype(str)>,const char*>;
    explicit constexpr CALLOUT_INVENTORY_PATH(const char* a) : _entry(entry(str, a)) {};
    type _entry;
};

}  // namespace _Inventory

struct Inventory
{
    static constexpr auto L = level::ERR;
    using CALLOUT_INVENTORY_PATH = _Inventory::CALLOUT_INVENTORY_PATH;
    using metadata_types = std::tuple<CALLOUT_INVENTORY_PATH>;

};

} // namespace Callout
} // namespace Common
} // namespace openbmc_project
} // namespace xyz


namespace details
{

template <>
struct map_exception_type<sdbusplus::xyz::openbmc_project::Common::Callout::Error::Inventory>
{
    using type = xyz::openbmc_project::Common::Callout::Inventory;
};

}

namespace xyz
{
namespace openbmc_project
{
namespace Common
{
namespace Callout
{
namespace _IPMISensor
{

struct CALLOUT_IPMI_SENSOR_NUM
{
    static constexpr auto str = "CALLOUT_IPMI_SENSOR_NUM=%u";
    static constexpr auto str_short = "CALLOUT_IPMI_SENSOR_NUM";
    using type = std::tuple<std::decay_t<decltype(str)>,uint32_t>;
    explicit constexpr CALLOUT_IPMI_SENSOR_NUM(uint32_t a) : _entry(entry(str, a)) {};
    type _entry;
};

}  // namespace _IPMISensor

struct IPMISensor
{
    static constexpr auto L = level::ERR;
    using CALLOUT_IPMI_SENSOR_NUM = _IPMISensor::CALLOUT_IPMI_SENSOR_NUM;
    using metadata_types = std::tuple<CALLOUT_IPMI_SENSOR_NUM>;

};

} // namespace Callout
} // namespace Common
} // namespace openbmc_project
} // namespace xyz


namespace details
{

template <>
struct map_exception_type<sdbusplus::xyz::openbmc_project::Common::Callout::Error::IPMISensor>
{
    using type = xyz::openbmc_project::Common::Callout::IPMISensor;
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
namespace _PowerSupplyUnderVoltageFault
{


}  // namespace _PowerSupplyUnderVoltageFault

struct PowerSupplyUnderVoltageFault
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
namespace Error
{
    struct PowerSequencerVoltageFault;
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
    struct Shutdown;
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

namespace xyz
{
namespace openbmc_project
{
namespace Power
{
namespace Fault
{
namespace _PowerSequencerVoltageFault
{

struct RAIL
{
    static constexpr auto str = "RAIL=%d";
    static constexpr auto str_short = "RAIL";
    using type = std::tuple<std::decay_t<decltype(str)>,uint16_t>;
    explicit constexpr RAIL(uint16_t a) : _entry(entry(str, a)) {};
    type _entry;
};
struct RAIL_NAME
{
    static constexpr auto str = "RAIL_NAME=%s";
    static constexpr auto str_short = "RAIL_NAME";
    using type = std::tuple<std::decay_t<decltype(str)>,const char*>;
    explicit constexpr RAIL_NAME(const char* a) : _entry(entry(str, a)) {};
    type _entry;
};
struct RAW_STATUS
{
    static constexpr auto str = "RAW_STATUS=%s";
    static constexpr auto str_short = "RAW_STATUS";
    using type = std::tuple<std::decay_t<decltype(str)>,const char*>;
    explicit constexpr RAW_STATUS(const char* a) : _entry(entry(str, a)) {};
    type _entry;
};

}  // namespace _PowerSequencerVoltageFault

struct PowerSequencerVoltageFault
{
    static constexpr auto L = level::ERR;
    using RAIL = _PowerSequencerVoltageFault::RAIL;
    using RAIL_NAME = _PowerSequencerVoltageFault::RAIL_NAME;
    using RAW_STATUS = _PowerSequencerVoltageFault::RAW_STATUS;
    using metadata_types = std::tuple<RAIL, RAIL_NAME, RAW_STATUS>;

};

} // namespace Fault
} // namespace Power
} // namespace openbmc_project
} // namespace xyz


namespace details
{

template <>
struct map_exception_type<sdbusplus::xyz::openbmc_project::Power::Fault::Error::PowerSequencerVoltageFault>
{
    using type = xyz::openbmc_project::Power::Fault::PowerSequencerVoltageFault;
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
namespace _PowerSequencerPGOODFault
{

struct INPUT_NUM
{
    static constexpr auto str = "INPUT_NUM=%d";
    static constexpr auto str_short = "INPUT_NUM";
    using type = std::tuple<std::decay_t<decltype(str)>,uint16_t>;
    explicit constexpr INPUT_NUM(uint16_t a) : _entry(entry(str, a)) {};
    type _entry;
};
struct INPUT_NAME
{
    static constexpr auto str = "INPUT_NAME=%s";
    static constexpr auto str_short = "INPUT_NAME";
    using type = std::tuple<std::decay_t<decltype(str)>,const char*>;
    explicit constexpr INPUT_NAME(const char* a) : _entry(entry(str, a)) {};
    type _entry;
};
struct RAW_STATUS
{
    static constexpr auto str = "RAW_STATUS=%s";
    static constexpr auto str_short = "RAW_STATUS";
    using type = std::tuple<std::decay_t<decltype(str)>,const char*>;
    explicit constexpr RAW_STATUS(const char* a) : _entry(entry(str, a)) {};
    type _entry;
};

}  // namespace _PowerSequencerPGOODFault

struct PowerSequencerPGOODFault
{
    static constexpr auto L = level::ERR;
    using INPUT_NUM = _PowerSequencerPGOODFault::INPUT_NUM;
    using INPUT_NAME = _PowerSequencerPGOODFault::INPUT_NAME;
    using RAW_STATUS = _PowerSequencerPGOODFault::RAW_STATUS;
    using metadata_types = std::tuple<INPUT_NUM, INPUT_NAME, RAW_STATUS>;

};

} // namespace Fault
} // namespace Power
} // namespace openbmc_project
} // namespace xyz


namespace details
{

template <>
struct map_exception_type<sdbusplus::xyz::openbmc_project::Power::Fault::Error::PowerSequencerPGOODFault>
{
    using type = xyz::openbmc_project::Power::Fault::PowerSequencerPGOODFault;
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
namespace _PowerSequencerFault
{

struct RAW_STATUS
{
    static constexpr auto str = "RAW_STATUS=%s";
    static constexpr auto str_short = "RAW_STATUS";
    using type = std::tuple<std::decay_t<decltype(str)>,const char*>;
    explicit constexpr RAW_STATUS(const char* a) : _entry(entry(str, a)) {};
    type _entry;
};

}  // namespace _PowerSequencerFault

struct PowerSequencerFault
{
    static constexpr auto L = level::ERR;
    using RAW_STATUS = _PowerSequencerFault::RAW_STATUS;
    using metadata_types = std::tuple<RAW_STATUS>;

};

} // namespace Fault
} // namespace Power
} // namespace openbmc_project
} // namespace xyz


namespace details
{

template <>
struct map_exception_type<sdbusplus::xyz::openbmc_project::Power::Fault::Error::PowerSequencerFault>
{
    using type = xyz::openbmc_project::Power::Fault::PowerSequencerFault;
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
namespace _GPUPowerFault
{

struct RAW_STATUS
{
    static constexpr auto str = "RAW_STATUS=%s";
    static constexpr auto str_short = "RAW_STATUS";
    using type = std::tuple<std::decay_t<decltype(str)>,const char*>;
    explicit constexpr RAW_STATUS(const char* a) : _entry(entry(str, a)) {};
    type _entry;
};
struct GPU
{
    static constexpr auto str = "GPU=%s";
    static constexpr auto str_short = "GPU";
    using type = std::tuple<std::decay_t<decltype(str)>,const char*>;
    explicit constexpr GPU(const char* a) : _entry(entry(str, a)) {};
    type _entry;
};

}  // namespace _GPUPowerFault

struct GPUPowerFault
{
    static constexpr auto L = level::ERR;
    using RAW_STATUS = _GPUPowerFault::RAW_STATUS;
    using GPU = _GPUPowerFault::GPU;
    using metadata_types = std::tuple<RAW_STATUS, GPU>;

};

} // namespace Fault
} // namespace Power
} // namespace openbmc_project
} // namespace xyz


namespace details
{

template <>
struct map_exception_type<sdbusplus::xyz::openbmc_project::Power::Fault::Error::GPUPowerFault>
{
    using type = xyz::openbmc_project::Power::Fault::GPUPowerFault;
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
namespace _GPUOverTemp
{

struct RAW_STATUS
{
    static constexpr auto str = "RAW_STATUS=%s";
    static constexpr auto str_short = "RAW_STATUS";
    using type = std::tuple<std::decay_t<decltype(str)>,const char*>;
    explicit constexpr RAW_STATUS(const char* a) : _entry(entry(str, a)) {};
    type _entry;
};
struct GPU
{
    static constexpr auto str = "GPU=%s";
    static constexpr auto str_short = "GPU";
    using type = std::tuple<std::decay_t<decltype(str)>,const char*>;
    explicit constexpr GPU(const char* a) : _entry(entry(str, a)) {};
    type _entry;
};

}  // namespace _GPUOverTemp

struct GPUOverTemp
{
    static constexpr auto L = level::ERR;
    using RAW_STATUS = _GPUOverTemp::RAW_STATUS;
    using GPU = _GPUOverTemp::GPU;
    using metadata_types = std::tuple<RAW_STATUS, GPU>;

};

} // namespace Fault
} // namespace Power
} // namespace openbmc_project
} // namespace xyz


namespace details
{

template <>
struct map_exception_type<sdbusplus::xyz::openbmc_project::Power::Fault::Error::GPUOverTemp>
{
    using type = xyz::openbmc_project::Power::Fault::GPUOverTemp;
};

}


} // namespace logging

} // namespace phosphor
