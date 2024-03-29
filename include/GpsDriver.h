/**
 * @file GpsDriver.h
 * @author Vu Thanh Trung
 * @brief GPS module 
 * @version 0.1
 * @date 2024-02-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef GPSDRIVER_H
#define GPSDRIVER_H 

//#include "types.h"
#include "TinyGPS++.h"
#include "HardwareSerial.h"
#include "configs.h"


//static HardwareSerial neoGPS(2);


#define ERROR_GPS_INIT_FAILED                0xA2
#define ERROR_GPS_GET_DATA_FAILED            0xA3
#define ERROR_GPS_LOCATION_INVALID           0xA4
#define ERROR_GPS_ENCODED_FAILED             0xA5

/**
 * @brief Initialize module GPS NEO M8N
 *  
 * @return ERROR_CODE 
 * @retval ERROR_NONE: if success
 * @retval ERROR_GPS_INIT_FAILED: if failed
 */
ERROR_CODE gps_init();

/**
 * @brief Get new data from GPS module
 * 
 * 
 * @return ERROR_CODE 
 * @retval ERROR_NONE: if success
 * @retval ERROR_GPS_GET_DATA_FAILED: if failed
 */
ERROR_CODE gps_getData(double  &_lat, double  &_lon);


#endif