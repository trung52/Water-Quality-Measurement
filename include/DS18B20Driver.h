/**
 * @file DS18B20Driver.h
 * @author Vu Thanh Trung
 * @brief Temperature sensor
 * @version 0.1
 * @date 2024-02-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DS18B20DRIVER_H
#define DS18B20DRIVER_H

#include <OneWire.h>
#include <DallasTemperature.h>
#include "configs.h"

#define ERROR_DS18B20_INIT_FAILED 0x01
#define ERROR_DS18B20_GETDATA_FAILED 0x02

#define DEVICE_DISCONNECTED_C -127 //Take this error code from DallasTemperature library

static OneWire oneWire(PIN_NUM_ONE_WIRE_BUS);

static DallasTemperature ds18b20(&oneWire);

/**
 * @brief Initialize DS18B20 sensor
 *  
 * @return ERROR_CODE 
 * @retval ERROR_NONE: if success
 * @retval ERROR_DS18B20_INIT_FAILED: if failed
 */
ERROR_CODE DS18B20_init();


/**
 * @brief Get data from DS18B20 sensor
 *  
 * @return ERROR_CODE 
 * @retval ERROR_NONE: if success
 * @retval ERROR_DS18B20_GETDATA_FAILED: if failed
 */
ERROR_CODE DS18B20_getData(float &_temp);

#endif