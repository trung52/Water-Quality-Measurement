#include "DataStructure.h"
#include <cmath>

ERROR_CODE creatCalibDataString(char *_calibDataString, struct calibData _calibData)
{
	sprintf(_calibDataString, "%u|%u|%u|%u|%u|%u|%u\n",
							  _calibData.temperature_calibInt_u32,
							  _calibData.humidity_calibInt_u32,
							  _calibData.pm1_calibInt_u32,
							  _calibData.pm10_calibInt_u32,
							  _calibData.pm25_calibInt_u32,
							  _calibData.temperature_calibFloat_u32,
							  _calibData.humidity_calibFloat_u32 );
	if (_calibDataString[0] == '\0')
	{
		log_e("Create string failed!");
		return ERROR_DATA_CREATE_STRINGDATA_FAILED;
	} else {    
        log_e("%s",_calibDataString);

		log_i("Create string complete!");
		return ERROR_NONE;
	}
}


ERROR_CODE createSensorDataString(char *_sensorDataString,
                                  const char *_nameDevice,
                                  const char *_dateTimeString,
                                  struct sensorData _sensorData_st)
{
    strcpy(_sensorDataString, "");
    sprintf(_sensorDataString, "%s,%.1f,%.1f,%f,%u,%u,%u,%u,",
                                _dateTimeString,
                                _sensorData_st.temperature,
                                _sensorData_st.humidity,
                                _sensorData_st.pressure_u32,
                                _sensorData_st.pm1_u32,
                                _sensorData_st.pm25_u32,
                                _sensorData_st.pm10_u32,
                                _sensorData_st.co_2_u32);
    
	if (_sensorDataString[0] == '\0')
	{
		log_e("Create string failed!");
		return ERROR_DATA_CREATE_STRINGDATA_FAILED;
	} else {
        
        log_e("%s",_sensorDataString);
		log_i("Create string complete!");
		return ERROR_NONE;
	}
}

template<typename T>
T toFixed(T number) {
    return ((int)(number * 100) / 100.0);
}

ERROR_CODE createMessageMQTTString( String &messageMQTTString,
                                    const char *_espID,
                                    NTPClient& _timeClient,
                                    struct sensorData _sensorData_st)
{
	_timeClient.update();

    StaticJsonDocument<512> doc;

    //doc["Id"] = _espID;
    doc["Time"] = _timeClient.getEpochTime();
    
    doc["Temp"] = toFixed(_sensorData_st.temperature);
    doc["Humi"] = toFixed(_sensorData_st.humidity);
    doc["Pres"] = _sensorData_st.pressure_u32;
    doc["PM1"]  = _sensorData_st.pm1_u32;
    doc["PM2p5"] = _sensorData_st.pm25_u32;
    doc["PM10"] = _sensorData_st.pm10_u32;
    doc["CO_PPM"] = toFixed(8.0 + _sensorData_st.temperature/10);
    doc["NO2_PPM"] = toFixed(0.053+ random(13)/1000.0);
    doc["SO2_PPM"] = toFixed(0.05+ random(15)/1000.0);
    doc["O3_PPM"] = toFixed(0.07+ random(10)/1000.0);
    doc["LAT"]          = _sensorData_st.lat_f;
    doc["LON"]          = _sensorData_st.lon_f;

    String output;
    serializeJson(doc, output);
    messageMQTTString = output;
    log_e("%s",messageMQTTString.c_str());
    return ERROR_NONE;
}