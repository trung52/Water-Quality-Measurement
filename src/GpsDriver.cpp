
#include"GpsDriver.h"

ERROR_CODE gps_init()
{        
    neoGPS.begin(9600, SERIAL_8N1, PIN_NUM_GPS_TX, PIN_NUM_GPS_RX);
    connectionStatus_st.gpsStatus = status_et::CONNECTED;
    return ERROR_NONE;
}

ERROR_CODE gps_getData(double  &_lat, double  &_lon)
{
    if(neoGPS.available() > 0){
        log_i("GPS starts getting data...");
        if(gps.encode(neoGPS.read())){
            if(gps.location.isValid()){
                _lat = gps.location.lat();
                _lon = gps.location.lng();
                log_i("GPS NEO-M8N gets data successfully ");
                return ERROR_NONE;
            }
            else{
                log_e("gps location invalid");
                return ERROR_GPS_LOCATION_INVALID;
            }
        }
    }
    if (millis() > 5000 && gps.charsProcessed() < 10){
        log_e("No GPS data received: check wiring");
        return ERROR_GPS_GET_DATA_FAILED;
    }

}
