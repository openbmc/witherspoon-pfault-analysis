#pragma once
#include "device.hpp"

namespace phosphor
{
namespace power
{
namespace psu
{

/**
 * @class PowerSupply
 * Represents a PMBus power supply device.
 */
class PowerSupply : public Device
{
    public:
        PowerSupply() = delete;
        PowerSupply(const PowerSupply&) = delete;
        PowerSupply(PowerSupply&&) = default;
        PowerSupply& operator=(const PowerSupply&) = delete;
        PowerSupply& operator=(PowerSupply&&) = delete;
        ~PowerSupply() = default;

        /**
         * Constructor
         *
         * @param name - the device name
         * @param inst - the device instance
         * @param objpath - the path to monitor
         * @param invpath - the inventory path to use
         */
        PowerSupply(const std::string& name, size_t inst,
                    const std::string& objpath, const std::string& invpath)
            : Device(name, inst), monitorPath(objpath), inventoryPath(invpath)
        {
        }

        /**
         * Power supply specific function to analyze for faults/errors.
         *
         * Various PMBus status bits will be checked for fault conditions.
         * If a certain fault bits are on, the appropriate error will be 
         * committed.
         */
        void analyze();

        /**
         * Write PMBus CLEAR_FAULTS
         *
         * This function will be called in various situations in order to clear
         * any fault status bits that may have been set, in order to start over
         * with a clean state. Presence changes and power state changes will
         * want to clear any faults logged.
         */
        void clearFaults();

    private:
        /**
         * The path to use for reading various PMBus bits/words.
         */
        std::string monitorPath;

        /**
         * The D-Bus path to use for this power supplies inventory status.
         */
        std::string inventoryPath;
};

}
}
}
