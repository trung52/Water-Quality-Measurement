#include "DOSensor.h"
ERROR_CODE averageSensorVoltage(uint8_t _pin, uint32_t &voltage_mv){
  int numReadings = 10;  // Number of times to read
  int sensorVoltage[numReadings];  // Array to store values
  int total = 0;
  
  // Read ADC voltage and store in array
  for (int i = 0; i < numReadings; i++) {
    sensorVoltage[i] = analogRead(_pin);
    total += sensorVoltage[i];
    delay(200);  // Delay to get stable values
  }
  
  // Calculate average voltage
  float average = total / (float)numReadings;
  average = (uint32_t)VREF * average / ADC_RES;
  voltage_mv = (uint32_t)average;
  return ERROR_NONE;
}

ERROR_CODE DO_getData(uint32_t voltage_mv, uint8_t temperature_c, uint16_t &_DO_value){
#if TWO_POINT_CALIBRATION == 0
  uint16_t V_saturation = (uint32_t)CAL1_V + (uint32_t)35 * temperature_c - (uint32_t)CAL1_T * 35;
  _DO_value = (voltage_mv * DO_Table[temperature_c] / V_saturation)*doSensorCalib;
#else
  uint16_t V_saturation = (int16_t)((int8_t)temperature_c - CAL2_T) * ((uint16_t)CAL1_V - CAL2_V) / ((uint8_t)CAL1_T - CAL2_T) + CAL2_V;
  _DO_value = (voltage_mv * DO_Table[temperature_c] / V_saturation);
#endif
return ERROR_NONE;
}