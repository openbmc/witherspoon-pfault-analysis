#pragma once
#include <tuple>
#include <systemd/sd-bus.h>
#include <sdbusplus/server.hpp>

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

class Average
{
    public:
        /* Define all of the basic class operations:
         *     Not allowed:
         *         - Default constructor to avoid nullptrs.
         *         - Copy operations due to internal unique_ptr.
         *         - Move operations due to 'this' being registered as the
         *           'context' with sdbus.
         *     Allowed:
         *         - Destructor.
         */
        Average() = delete;
        Average(const Average&) = delete;
        Average& operator=(const Average&) = delete;
        Average(Average&&) = delete;
        Average& operator=(Average&&) = delete;
        virtual ~Average() = default;

        /** @brief Constructor to put object onto bus at a dbus path.
         *  @param[in] bus - Bus to attach to.
         *  @param[in] path - Path to attach at.
         */
        Average(bus::bus& bus, const char* path);


        using PropertiesVariant = sdbusplus::message::variant<
                std::vector<std::tuple<uint64_t, int64_t>>,
                int64_t>;

        /** @brief Constructor to initialize the object from a map of
         *         properties.
         *
         *  @param[in] bus - Bus to attach to.
         *  @param[in] path - Path to attach at.
         *  @param[in] vals - Map of property name to value for initialization.
         */
        Average(bus::bus& bus, const char* path,
                     const std::map<std::string, PropertiesVariant>& vals);



        /** Get value of Scale */
        virtual int64_t scale() const;
        /** Set value of Scale */
        virtual int64_t scale(int64_t value);
        /** Get value of Values */
        virtual std::vector<std::tuple<uint64_t, int64_t>> values() const;
        /** Set value of Values */
        virtual std::vector<std::tuple<uint64_t, int64_t>> values(std::vector<std::tuple<uint64_t, int64_t>> value);

        /** @brief Sets a property by name.
         *  @param[in] name - A string representation of the property name.
         *  @param[in] val - A variant containing the value to set.
         */
        void setPropertyByName(const std::string& name,
                               const PropertiesVariant& val);

        /** @brief Gets a property by name.
         *  @param[in] name - A string representation of the property name.
         *  @return - A variant containing the value of the property.
         */
        PropertiesVariant getPropertyByName(const std::string& name);


    private:

        /** @brief sd-bus callback for get-property 'Scale' */
        static int _callback_get_Scale(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);
        /** @brief sd-bus callback for set-property 'Scale' */
        static int _callback_set_Scale(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);

        /** @brief sd-bus callback for get-property 'Values' */
        static int _callback_get_Values(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);
        /** @brief sd-bus callback for set-property 'Values' */
        static int _callback_set_Values(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);


        static constexpr auto _interface = "xyz.openbmc_project.Sensor.Aggregation.History.Average";
        static const vtable::vtable_t _vtable[];
        sdbusplus::server::interface::interface
                _xyz_openbmc_project_Sensor_Aggregation_History_Average_interface;

        int64_t _scale{};
        std::vector<std::tuple<uint64_t, int64_t>> _values{};

};


} // namespace server
} // namespace History
} // namespace Aggregation
} // namespace Sensor
} // namespace openbmc_project
} // namespace xyz
} // namespace sdbusplus

