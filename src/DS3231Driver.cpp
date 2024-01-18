#include "DS3231Driver.h"

ERROR_CODE DS3231_init(RTC_DS3231& _realTime, TwoWire &_wire)
{
	if (_realTime.begin(&_wire))			// khoi dong module RTC
	{
		log_i("RTC module initialized successfully!");        		
		connectionStatus_st.ds3231Module = status_et::CONNECTED;
		//_realTime.adjust(DateTime(F(__DATE__), F(__TIME__)));
		return ERROR_NONE;

	} else {
		log_e("RTC module initialized failed!");		
		connectionStatus_st.ds3231Module = status_et::DISCONNECTED;
		return ERROR_RTC_INIT_FAILED;
	}
}

ERROR_CODE DS3231_getStringDateTime(RTC_DS3231& _realTime, DateTime::timestampOpt _opt, char *_dateTime_string)
{
	if (connectionStatus_st.ds3231Module ==  status_et::CONNECTED)		// Check RTC DS3231's status
	{
		strcpy(_dateTime_string, (_realTime.now().timestamp(_opt).c_str()));		// Copy timestamp to string datetime return

		log_i("Get DateTime successfully!");
		return ERROR_NONE;
	} else {
		log_e("Get DateTime failed.");
		return ERROR_RTC_GET_STRING_DATETIME_FAILED;
	}
}


