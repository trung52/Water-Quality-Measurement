/**
 * @file DS18B20Driver.h
 * @author Vu Thanh Trung
 * @brief Temperature sensor
 * @version 0.1
 * @date 2024-02-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef DOSENSOR_H
#define DOSENSOR_H

#include "configs.h"

#define TWO_POINT_CALIBRATION 0

//Single point calibration needs to be filled CAL1_V and CAL1_T
#define CAL1_V (1300) //mv
#define CAL1_T (21.2)   //℃
//Two-point calibration needs to be filled CAL2_V and CAL2_T
//CAL1 High temperature point, CAL2 Low temperature point
#define CAL2_V (1300) //mv
#define CAL2_T (15)   //℃

static float doSensorCalib = 2.1;

const uint16_t DO_Table[41] = {
    14460, 14220, 13820, 13440, 13090, 12740, 12420, 12110, 11810, 11530,
    11260, 11010, 10770, 10530, 10300, 10080, 9860, 9660, 9460, 9270,
    9080, 8900, 8730, 8570, 8410, 8250, 8110, 7960, 7820, 7690,
    7560, 7430, 7300, 7180, 7070, 6950, 6840, 6730, 6630, 6530, 6410};

/**
 * @brief Get average sensor voltage
 * @param[in] _pin: ADC pin
 * @param[out] voltage_mv: DO voltage
 * @return ERROR_CODE
*/
ERROR_CODE averageSensorVoltage(uint8_t _pin, uint32_t &voltage_mv);

/**
 * @brief Get DO value 
 * @param[in] voltage_mv: sensor voltage (get from ADC)
 * @param[in] temperature_c: measured environment temperature in Celsius (get from DS18B20)
 * @param[out] _DO_value: DO value (ug/L)
 * @return ERROR_CODE
*/
ERROR_CODE DO_getData(uint32_t voltage_mv, uint8_t temperature_c, uint16_t &_DO_value);

#endif