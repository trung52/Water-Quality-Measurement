#include "DS18B20Driver.h"

ERROR_CODE DS18B20_init(){
    ds18b20.begin();

    return ERROR_NONE;
}

ERROR_CODE DS18B20_getData(float &_temp){
    ds18b20.requestTemperatures();
    _temp = ds18b20.getTempCByIndex(0);
    
    if(_temp == DEVICE_DISCONNECTED_C)
        return ERROR_DS18B20_GETDATA_FAILED;
    
    return ERROR_NONE;
}