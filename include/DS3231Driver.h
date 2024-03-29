/**
 * @file DS3231Driver.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#ifndef DS3231DRIVER_H
#define DS3231DRIVER_H

#include "RTClib.h"
#include "configs.h"
#include <ESP32Ping.h>
#include "esp_log.h"
#include <NTPClient.h>



#define ERROR_RTC_INIT_FAILED 0x71
#define ERROR_RTC_GET_STRING_DATETIME_FAILED 0x72

/**
 * @brief Initialize RTC module
 * 
 * @param[in]  _realTime: RTC_DS3231 object
 * @param[in]  _wire: Wire I2c
 * @return ERROR_CODE
 */
ERROR_CODE DS3231_init(RTC_DS3231& _realTime, TwoWire &_wire);



/**
 * @brief	Get string datetime
 *
 * @param[in]  _realTime: RTC_DS3231 object
 * @param[in]  _format: format of string datetime. Example "hh:mm DD-MMM-YY"
 * @param[out] _dateTime_string: string datetime return
 * @return ERROR_CODE
 */
ERROR_CODE DS3231_getStringDateTime(RTC_DS3231 &_realTime,   DateTime::timestampOpt _opt, char *_dateTime_string);

#endif