#pragma once
#include <phosphor-logging/log.hpp>
#include <sdbusplus/bus.hpp>
#include <sdbusplus/server.hpp>
#include <sdeventplus/event.hpp>
#include "device.hpp"
#include "timer.hpp"

namespace witherspoon
{
namespace power
{

using namespace phosphor::logging;

/**
 * @class DeviceMonitor
 *
 * Monitors a power device for faults by calling Device::analyze()
 * on an interval.  Do the monitoring by calling run().
 * May be overridden to provide more functionality.
 */
class DeviceMonitor
{
    public:

        DeviceMonitor() = delete;
        ~DeviceMonitor() = default;
        DeviceMonitor(const DeviceMonitor&) = delete;
        DeviceMonitor& operator=(const DeviceMonitor&) = delete;
        DeviceMonitor(DeviceMonitor&&) = delete;
        DeviceMonitor& operator=(DeviceMonitor&&) = delete;

        /**
         * Constructor
         *
         * @param[in] d - device to monitor
         * @param[in] e - event object
         * @param[in] i - polling interval in ms
         */
        DeviceMonitor(std::unique_ptr<Device>&& d,
                      const sdeventplus::Event& e,
                      std::chrono::milliseconds i) :
            device(std::move(d)),
            event(e),
            interval(i),
            timer(e, [this]()
            {
                this->analyze();
            })
        {
        }

        /**
         * Starts the timer to monitor the device on an interval.
         */
        virtual int run()
        {
            timer.start(interval, Timer::TimerType::repeating);
            return event.loop();
        }

    protected:

        /**
         * Analyzes the device for faults
         *
         * Runs in the timer callback
         *
         * Override if desired
         */
        virtual void analyze()
        {
            device->analyze();
        }

        /**
         * The device to run the analysis on
         */
        std::unique_ptr<Device> device;

        /**
         * The event loop used by the timer
         */
        sdeventplus::Event event;

        /**
         * The polling interval in milliseconds
         */
        std::chrono::milliseconds interval;

        /**
         * The timer that runs fault check polls.
         */
        Timer timer;
};

}
}
