/*
 * @file DataStructure.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-11
 * 
 * @copyright Copyright (c) 2022
 * 
*/

#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <Arduino.h>
#include <string>
#include "esp_log.h"
#include "configs.h"
#include <ArduinoJson.h>
#include <NTPClient.h>

#define ERROR_DATA_CREATE_STRINGDATA_FAILED 0x91




struct calibData {
    uint32_t temperature_calibInt_u32;
    uint32_t depth_calibInt_u32;
    uint32_t DO_value_calibInt_u32;


    calibData() {     // initialation function for struct (C++ style)
        this->temperature_calibInt_u32      = 0;
        this->depth_calibInt_u32              = 0;
        this->DO_value_calibInt_u32             = 0;
    }
};



/**
 * @brief Create a string from sensor data for storing in the SD card
 * 
 * @param[out] _calibDataString: pointer char*, use to store string
 * @param[in]  _calibData: struct calibdata
 * @return ERROR_CODE 
 */
ERROR_CODE creatCalibDataString(char *_calibDataString, struct calibData _calibData);

struct sensorData {
    float temperature; 
    float depth; // Get depth through pressure sensor
    uint16_t DO_value;

    sensorData() 
    {
        this->temperature = 0;
        this->depth		  = 0;
        this->DO_value    = 0;
        
    };

    sensorData operator=(const sensorData _sensorData_temp)
    {
        this->temperature	 = _sensorData_temp.temperature;
        this->depth		 = _sensorData_temp.depth;
        this->DO_value	 = _sensorData_temp.DO_value;
        
        return _sensorData_temp;
    }
};


/**
 * @brief Create a string
 * 
 * @param[out] _senorDataString: Pointer char*, use to store DataString
 * @param[in]  _nameDevice: Device's name
 * @param[in] _dateTimeString: Pointer char*, use to store DateTime
 * @param[in] _sensorData_st: struct sensor data
 * @return ERROR_CODE 
 */
ERROR_CODE createSensorDataString(char *_sensorDataString,
                                  const char *_nameDevice,
                                  const char *_dateTimeString,
                                  struct sensorData _sensorData_st);



#endif