
#include"GpsDriver.h"

extern TinyGPSPlus gps;


ERROR_CODE gps_init()
{        
    Serial2.begin(9600);
    Serial2.setRxBufferSize(1024);
    Serial2.flush();
    connectionStatus_st.gpsStatus = status_et::CONNECTED;
    return ERROR_NONE;
}

extern ERROR_CODE gps_getData(double  &_lat, double  &_lon)
{
    _lat = gps.location.lat();
    _lon = gps.location.lng();
    
    log_i("GPS NEO-M8N gets data successfully ");
    return ERROR_NONE;
    
}
