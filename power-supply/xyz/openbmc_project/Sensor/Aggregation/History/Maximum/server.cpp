#include <algorithm>
#include <sdbusplus/server.hpp>
#include <sdbusplus/exception.hpp>
#include <xyz/openbmc_project/Sensor/Aggregation/History/Maximum/server.hpp>

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

Maximum::Maximum(bus::bus& bus, const char* path)
        : _xyz_openbmc_project_Sensor_Aggregation_History_Maximum_interface(
                bus, path, _interface, _vtable, this)
{
}

Maximum::Maximum(bus::bus& bus, const char* path,
                           const std::map<std::string, PropertiesVariant>& vals)
        : Maximum(bus, path)
{
    for (const auto& v : vals)
    {
        setPropertyByName(v.first, v.second);
    }
}



auto Maximum::scale() const ->
        int64_t
{
    return _scale;
}

int Maximum::_callback_get_Scale(
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

        auto o = static_cast<Maximum*>(context);
        m.append(convertForMessage(o->scale()));
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        sd_bus_error_set_const(error, e.name(), e.description());
        return -EINVAL;
    }

    return true;
}

auto Maximum::scale(int64_t value) ->
        int64_t
{
    if (_scale != value)
    {
        _scale = value;
        _xyz_openbmc_project_Sensor_Aggregation_History_Maximum_interface.property_changed("Scale");
    }

    return _scale;
}

int Maximum::_callback_set_Scale(
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

        auto o = static_cast<Maximum*>(context);

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
namespace Maximum
{
static const auto _property_Scale =
    utility::tuple_to_array(message::types::type_id<
            int64_t>());
}
}
auto Maximum::unit() const ->
        Unit
{
    return _unit;
}

int Maximum::_callback_get_Unit(
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

        auto o = static_cast<Maximum*>(context);
        m.append(convertForMessage(o->unit()));
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        sd_bus_error_set_const(error, e.name(), e.description());
        return -EINVAL;
    }

    return true;
}

auto Maximum::unit(Unit value) ->
        Unit
{
    if (_unit != value)
    {
        _unit = value;
        _xyz_openbmc_project_Sensor_Aggregation_History_Maximum_interface.property_changed("Unit");
    }

    return _unit;
}

int Maximum::_callback_set_Unit(
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

        auto o = static_cast<Maximum*>(context);

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
namespace Maximum
{
static const auto _property_Unit =
    utility::tuple_to_array(message::types::type_id<
            std::string>());
}
}
auto Maximum::values() const ->
        std::vector<std::tuple<uint64_t, int64_t>>
{
    return _values;
}

int Maximum::_callback_get_Values(
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

        auto o = static_cast<Maximum*>(context);
        m.append(convertForMessage(o->values()));
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        sd_bus_error_set_const(error, e.name(), e.description());
        return -EINVAL;
    }

    return true;
}

auto Maximum::values(std::vector<std::tuple<uint64_t, int64_t>> value) ->
        std::vector<std::tuple<uint64_t, int64_t>>
{
    if (_values != value)
    {
        _values = value;
        _xyz_openbmc_project_Sensor_Aggregation_History_Maximum_interface.property_changed("Values");
    }

    return _values;
}

int Maximum::_callback_set_Values(
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

        auto o = static_cast<Maximum*>(context);

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
namespace Maximum
{
static const auto _property_Values =
    utility::tuple_to_array(message::types::type_id<
            std::vector<std::tuple<uint64_t, int64_t>>>());
}
}

void Maximum::setPropertyByName(const std::string& name,
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

auto Maximum::getPropertyByName(const std::string& name) ->
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
/** String to enum mapping for Maximum::Unit */
static const std::tuple<const char*, Maximum::Unit> mappingMaximumUnit[] =
        {
            std::make_tuple( "xyz.openbmc_project.Sensor.Aggregation.History.Maximum.Unit.DegreesC",                 Maximum::Unit::DegreesC ),
            std::make_tuple( "xyz.openbmc_project.Sensor.Aggregation.History.Maximum.Unit.RPMS",                 Maximum::Unit::RPMS ),
            std::make_tuple( "xyz.openbmc_project.Sensor.Aggregation.History.Maximum.Unit.Volts",                 Maximum::Unit::Volts ),
            std::make_tuple( "xyz.openbmc_project.Sensor.Aggregation.History.Maximum.Unit.Meters",                 Maximum::Unit::Meters ),
            std::make_tuple( "xyz.openbmc_project.Sensor.Aggregation.History.Maximum.Unit.Amperes",                 Maximum::Unit::Amperes ),
            std::make_tuple( "xyz.openbmc_project.Sensor.Aggregation.History.Maximum.Unit.Watts",                 Maximum::Unit::Watts ),
            std::make_tuple( "xyz.openbmc_project.Sensor.Aggregation.History.Maximum.Unit.Joules",                 Maximum::Unit::Joules ),
        };

} // anonymous namespace

auto Maximum::convertUnitFromString(const std::string& s) ->
        Unit
{
    auto i = std::find_if(
            std::begin(mappingMaximumUnit),
            std::end(mappingMaximumUnit),
            [&s](auto& e){ return 0 == strcmp(s.c_str(), std::get<0>(e)); } );
    if (std::end(mappingMaximumUnit) == i)
    {
        throw sdbusplus::exception::InvalidEnumString();
    }
    else
    {
        return std::get<1>(*i);
    }
}

std::string convertForMessage(Maximum::Unit v)
{
    auto i = std::find_if(
            std::begin(mappingMaximumUnit),
            std::end(mappingMaximumUnit),
            [v](auto& e){ return v == std::get<1>(e); });
    return std::get<0>(*i);
}

const vtable::vtable_t Maximum::_vtable[] = {
    vtable::start(),
    vtable::property("Scale",
                     details::Maximum::_property_Scale
                        .data(),
                     _callback_get_Scale,
                     _callback_set_Scale,
                     vtable::property_::emits_change),
    vtable::property("Unit",
                     details::Maximum::_property_Unit
                        .data(),
                     _callback_get_Unit,
                     _callback_set_Unit,
                     vtable::property_::emits_change),
    vtable::property("Values",
                     details::Maximum::_property_Values
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

