
#include"GpsDriver.h"

ERROR_CODE gps_init()
{        
neoGPS.begin(9600, SERIAL_8N1, PIN_NUM_GPS_RX, PIN_NUM_GPS_TX);

    return ERROR_NONE;
}

ERROR_CODE gps_getdata(double  &_lat, double  &_lon)
{
    if(neoGPS.available() > 0){
        if(gps.encode(neoGPS.read())){
            if(gps.location.isValid()){
                _lat = gps.location.lat();
                _lon = gps.location.lng();
                return ERROR_NONE;
            }
            else{
                log_e("gps location invalid");
                return ERROR_GPS_LOCATION_INVALID;
            }
        }
        else{
            log_e("gps encode failed");
            return ERROR_GPS_ENCODED_FAILED;
        }
    }
    if (millis() > 5000 && gps.charsProcessed() < 10){
        log_e("No GPS data received: check wiring");
        return ERROR_GPS_GET_DATA_FAILED;
    }
    
}
