#pragma once
#include <functional>
#include <xyz/openbmc_project/Sensor/Aggregation/History/Average/server.hpp>

namespace witherspoon
{
namespace power
{
namespace history
{

template <typename T>
using ServerObject = typename sdbusplus::server::object::object<T>;

using AverageInterface = sdbusplus::xyz::openbmc_project::
        Sensor::Aggregation::History::server::Average;

/**
 * @class Average
 *
 * Implements Sensor.Aggregation.History.Average
 *
 * This includes a property that is an array of timestamp/average tuples
 * and a property to specify the scale.
 */
class Average : public ServerObject<AverageInterface>
{
    public:

        static constexpr auto name = "average";

        Average() = delete;
        Average(const Average&) = delete;
        Average& operator=(const Average&) = delete;
        Average(Average&&) = delete;
        Average& operator=(Average&&) = delete;
        ~Average() = default;

        /**
         * @brief Constructor
         *
         * @param[in] bus - D-Bus object
         * @param[in] objectPath - the D-Bus object path
         */
        Average(sdbusplus::bus::bus& bus,
                const std::string& objectPath) :
                ServerObject<AverageInterface>(bus, objectPath.c_str())
        {
            scale(0); //The value is Watts, so scale = 0
        }
};


}
}
}
