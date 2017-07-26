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
        PowerSupply& operator=(PowerSupply&&) = default;
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
            : Device(name, inst)
        {
            monitorPath = objpath;
            inventoryPath = invpath;
        }

        void analyze();

        void clearFaults();

    private:
        std::string monitorPath;
        std::string inventoryPath;
};

}
}
}
// vim: tabstop=8 expandtab shiftwidth=4 softtabstop=4
