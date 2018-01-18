#include <algorithm>
#include <sdbusplus/server.hpp>
#include <sdbusplus/exception.hpp>
#include <xyz/openbmc_project/Sensor/Aggregation/History/Average/server.hpp>

namespace sdbusplus
{
namespace xyz
{
namespace openbmc_project
{
namespace Sensor
{
namespace Aggregation
{
namespace History
{
namespace server
{

Average::Average(bus::bus& bus, const char* path)
        : _xyz_openbmc_project_Sensor_Aggregation_History_Average_interface(
                bus, path, _interface, _vtable, this)
{
}

Average::Average(bus::bus& bus, const char* path,
                           const std::map<std::string, PropertiesVariant>& vals)
        : Average(bus, path)
{
    for (const auto& v : vals)
    {
        setPropertyByName(v.first, v.second);
    }
}



auto Average::scale() const ->
        int64_t
{
    return _scale;
}

int Average::_callback_get_Scale(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* reply, void* context,
        sd_bus_error* error)
{
    using sdbusplus::server::binding::details::convertForMessage;

    try
    {
        auto m = message::message(reply);
#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        auto o = static_cast<Average*>(context);
        m.append(convertForMessage(o->scale()));
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        sd_bus_error_set_const(error, e.name(), e.description());
        return -EINVAL;
    }

    return true;
}

auto Average::scale(int64_t value) ->
        int64_t
{
    if (_scale != value)
    {
        _scale = value;
        _xyz_openbmc_project_Sensor_Aggregation_History_Average_interface.property_changed("Scale");
    }

    return _scale;
}

int Average::_callback_set_Scale(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* value, void* context,
        sd_bus_error* error)
{
    try
    {
        auto m = message::message(value);
#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        auto o = static_cast<Average*>(context);

        int64_t v{};
        m.read(v);
        o->scale(v);
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        sd_bus_error_set_const(error, e.name(), e.description());
        return -EINVAL;
    }

    return true;
}

namespace details
{
namespace Average
{
static const auto _property_Scale =
    utility::tuple_to_array(message::types::type_id<
            int64_t>());
}
}
auto Average::unit() const ->
        Unit
{
    return _unit;
}

int Average::_callback_get_Unit(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* reply, void* context,
        sd_bus_error* error)
{
    using sdbusplus::server::binding::details::convertForMessage;

    try
    {
        auto m = message::message(reply);
#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        auto o = static_cast<Average*>(context);
        m.append(convertForMessage(o->unit()));
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        sd_bus_error_set_const(error, e.name(), e.description());
        return -EINVAL;
    }

    return true;
}

auto Average::unit(Unit value) ->
        Unit
{
    if (_unit != value)
    {
        _unit = value;
        _xyz_openbmc_project_Sensor_Aggregation_History_Average_interface.property_changed("Unit");
    }

    return _unit;
}

int Average::_callback_set_Unit(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* value, void* context,
        sd_bus_error* error)
{
    try
    {
        auto m = message::message(value);
#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        auto o = static_cast<Average*>(context);

        std::string v{};
        m.read(v);
        o->unit(convertUnitFromString(v));
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        sd_bus_error_set_const(error, e.name(), e.description());
        return -EINVAL;
    }

    return true;
}

namespace details
{
namespace Average
{
static const auto _property_Unit =
    utility::tuple_to_array(message::types::type_id<
            std::string>());
}
}
auto Average::values() const ->
        std::vector<std::tuple<uint64_t, int64_t>>
{
    return _values;
}

int Average::_callback_get_Values(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* reply, void* context,
        sd_bus_error* error)
{
    using sdbusplus::server::binding::details::convertForMessage;

    try
    {
        auto m = message::message(reply);
#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        auto o = static_cast<Average*>(context);
        m.append(convertForMessage(o->values()));
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        sd_bus_error_set_const(error, e.name(), e.description());
        return -EINVAL;
    }

    return true;
}

auto Average::values(std::vector<std::tuple<uint64_t, int64_t>> value) ->
        std::vector<std::tuple<uint64_t, int64_t>>
{
    if (_values != value)
    {
        _values = value;
        _xyz_openbmc_project_Sensor_Aggregation_History_Average_interface.property_changed("Values");
    }

    return _values;
}

int Average::_callback_set_Values(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* value, void* context,
        sd_bus_error* error)
{
    try
    {
        auto m = message::message(value);
#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        auto o = static_cast<Average*>(context);

        std::vector<std::tuple<uint64_t, int64_t>> v{};
        m.read(v);
        o->values(v);
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        sd_bus_error_set_const(error, e.name(), e.description());
        return -EINVAL;
    }

    return true;
}

namespace details
{
namespace Average
{
static const auto _property_Values =
    utility::tuple_to_array(message::types::type_id<
            std::vector<std::tuple<uint64_t, int64_t>>>());
}
}

void Average::setPropertyByName(const std::string& name,
                                     const PropertiesVariant& val)
{
    if (name == "Scale")
    {
        auto& v = message::variant_ns::get<int64_t>(val);
        scale(v);
        return;
    }
    if (name == "Unit")
    {
        auto& v = message::variant_ns::get<Unit>(val);
        unit(v);
        return;
    }
    if (name == "Values")
    {
        auto& v = message::variant_ns::get<std::vector<std::tuple<uint64_t, int64_t>>>(val);
        values(v);
        return;
    }
}

auto Average::getPropertyByName(const std::string& name) ->
        PropertiesVariant
{
    if (name == "Scale")
    {
        return scale();
    }
    if (name == "Unit")
    {
        return unit();
    }
    if (name == "Values")
    {
        return values();
    }

    return PropertiesVariant();
}


namespace
{
/** String to enum mapping for Average::Unit */
static const std::tuple<const char*, Average::Unit> mappingAverageUnit[] =
        {
            std::make_tuple( "xyz.openbmc_project.Sensor.Aggregation.History.Average.Unit.DegreesC",                 Average::Unit::DegreesC ),
            std::make_tuple( "xyz.openbmc_project.Sensor.Aggregation.History.Average.Unit.RPMS",                 Average::Unit::RPMS ),
            std::make_tuple( "xyz.openbmc_project.Sensor.Aggregation.History.Average.Unit.Volts",                 Average::Unit::Volts ),
            std::make_tuple( "xyz.openbmc_project.Sensor.Aggregation.History.Average.Unit.Meters",                 Average::Unit::Meters ),
            std::make_tuple( "xyz.openbmc_project.Sensor.Aggregation.History.Average.Unit.Amperes",                 Average::Unit::Amperes ),
            std::make_tuple( "xyz.openbmc_project.Sensor.Aggregation.History.Average.Unit.Watts",                 Average::Unit::Watts ),
            std::make_tuple( "xyz.openbmc_project.Sensor.Aggregation.History.Average.Unit.Joules",                 Average::Unit::Joules ),
        };

} // anonymous namespace

auto Average::convertUnitFromString(const std::string& s) ->
        Unit
{
    auto i = std::find_if(
            std::begin(mappingAverageUnit),
            std::end(mappingAverageUnit),
            [&s](auto& e){ return 0 == strcmp(s.c_str(), std::get<0>(e)); } );
    if (std::end(mappingAverageUnit) == i)
    {
        throw sdbusplus::exception::InvalidEnumString();
    }
    else
    {
        return std::get<1>(*i);
    }
}

std::string convertForMessage(Average::Unit v)
{
    auto i = std::find_if(
            std::begin(mappingAverageUnit),
            std::end(mappingAverageUnit),
            [v](auto& e){ return v == std::get<1>(e); });
    return std::get<0>(*i);
}

const vtable::vtable_t Average::_vtable[] = {
    vtable::start(),
    vtable::property("Scale",
                     details::Average::_property_Scale
                        .data(),
                     _callback_get_Scale,
                     _callback_set_Scale,
                     vtable::property_::emits_change),
    vtable::property("Unit",
                     details::Average::_property_Unit
                        .data(),
                     _callback_get_Unit,
                     _callback_set_Unit,
                     vtable::property_::emits_change),
    vtable::property("Values",
                     details::Average::_property_Values
                        .data(),
                     _callback_get_Values,
                     _callback_set_Values,
                     vtable::property_::emits_change),
    vtable::end()
};

} // namespace server
} // namespace History
} // namespace Aggregation
} // namespace Sensor
} // namespace openbmc_project
} // namespace xyz
} // namespace sdbusplus

