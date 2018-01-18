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
    if (name == "Values")
    {
        return values();
    }

    return PropertiesVariant();
}


const vtable::vtable_t Average::_vtable[] = {
    vtable::start(),
    vtable::property("Scale",
                     details::Average::_property_Scale
                        .data(),
                     _callback_get_Scale,
                     _callback_set_Scale,
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

