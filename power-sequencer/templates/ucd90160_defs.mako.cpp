<%!
def indent(str, depth):
    return ''.join(4*' '*depth+line for line in str.splitlines(True))
%>\
/* This is a generated file. */

#include "ucd90160.hpp"

namespace witherspoon
{
namespace power
{

using namespace ucd90160;
using namespace std::string_literals;

const DeviceMap UCD90160::deviceMap{
%for ucd_data in ucd90160s:
    {${ucd_data['index']},
     DeviceDefinition{
       "${ucd_data['path']}",

        RailNames{
        %for rail in ucd_data['RailNames']:
            "${rail}"s,
        %endfor
        },

        GPIConfigs{
        %for gpi_config in ucd_data['GPIConfigs']:
        <%
            secondary = str(gpi_config['secondary']).lower()
        %>\
            GPIConfig{${gpi_config['gpi']}, ${gpi_config['gpio_select']}, "${gpi_config['name']}"s, ${secondary}, extraAnalysisType::${gpi_config['analysis']}},
        %endfor
        },

         GPIOAnalysis{
             {extraAnalysisType::gpuPGOOD,
              GPIOGroup{
                  "/sys/devices/platform/ahb/ahb:apb/ahb:apb:bus@"
                  "1e78a000/1e78a400.i2c-bus/i2c-11/11-0060",
                  gpio::Value::low,
                  [](auto& ucd, const auto& callout) {
                      ucd.gpuPGOODError(callout);
                  },
                  optionFlags::none,
                  GPIODefinitions{
                      GPIODefinition{8,
                                     "/system/chassis/motherboard/gv100card0"s},
                      GPIODefinition{9,
                                     "/system/chassis/motherboard/gv100card1"s},
                      GPIODefinition{10,
                                     "/system/chassis/motherboard/gv100card2"s},
                      GPIODefinition{11,
                                     "/system/chassis/motherboard/gv100card3"s},
                      GPIODefinition{12,
                                     "/system/chassis/motherboard/gv100card4"s},
                      GPIODefinition{
                          13, "/system/chassis/motherboard/gv100card5"s}}}},

             {extraAnalysisType::gpuOverTemp,
              GPIOGroup{
                  "/sys/devices/platform/ahb/ahb:apb/ahb:apb:bus@"
                  "1e78a000/1e78a400.i2c-bus/i2c-11/11-0060",
                  gpio::Value::low,
                  [](auto& ucd,
                     const auto& callout) { ucd.gpuOverTempError(callout); },
                  optionFlags::shutdownOnFault,
                  GPIODefinitions{
                      GPIODefinition{2,
                                     "/system/chassis/motherboard/gv100card0"s},
                      GPIODefinition{3,
                                     "/system/chassis/motherboard/gv100card1"s},
                      GPIODefinition{4,
                                     "/system/chassis/motherboard/gv100card2"s},
                      GPIODefinition{5,
                                     "/system/chassis/motherboard/gv100card3"s},
                      GPIODefinition{6,
                                     "/system/chassis/motherboard/gv100card4"s},
                      GPIODefinition{
                          7, "/system/chassis/motherboard/gv100card5"s}}}}}}
    }
%endfor
};

} // namespace power
} // namespace witherspoon
