/**
 * @file SubmersiblePressure.h
 * @author Vu Thanh Trung
 * @brief Submersible pressure sensor
 * @brief Model: SKU:KIT0139
 * @details See <https://wiki.dfrobot.com/Throw-in_Type_Liquid_Level_Transmitter_SKU_KIT0139>
 * @version 0.1
 * @date 2024-02-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef SUBMERSIBLEPRESSURE_H
#define SUBMERSIBLEPRESSURE_H

#include "configs.h"


#define DEPTH_RANGE 5000 //Depth measuring range 5000mm (for water)
#define CURRENT_INIT 4.00 // Current @ 0mm (uint: mA)
#define DENSITY_WATER 1  // Pure water density normalized to 1 Kg/L or (Kg/dm3)
// If measuring in another place as lake, river, etc you need to sample water and calculate density water of these places
#define DENSITY_GASOLINE 0.74  // Gasoline density (Kg/L)

/**
 * @brief Get depth value from submersible pressure sensor
 * @param[in] voltage_mv: sensor voltage (get from ADC)
 * @param[out] _pressCurrent: converted from voltage
 * @param[out] _depth: depth value
 * @return ERROR_CODE
*/
ERROR_CODE submersiblePressure_getDepth(float _voltage_mv, float &_pressCurrent, float &_depth){
    _pressCurrent = _voltage_mv / 120; //Sense Resistor:120ohm
    _depth = (_pressCurrent - CURRENT_INIT) * (DEPTH_RANGE/ DENSITY_WATER/ 16.0); // Calculate depth from current readings
    if(_depth < 0){
        _depth = 0.0;
    }
    return ERROR_NONE;
}

#endif