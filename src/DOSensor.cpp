#include "DOSensor.h"
uint32_t averageSensorVoltage(uint8_t _pin){
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
  return (uint32_t)average;
}

int16_t DO_getData(uint32_t voltage_mv, uint8_t temperature_c){
#if TWO_POINT_CALIBRATION == 0
  uint16_t V_saturation = (uint32_t)CAL1_V + (uint32_t)35 * temperature_c - (uint32_t)CAL1_T * 35;
  return (voltage_mv * DO_Table[temperature_c] / V_saturation);
#else
  uint16_t V_saturation = (int16_t)((int8_t)temperature_c - CAL2_T) * ((uint16_t)CAL1_V - CAL2_V) / ((uint8_t)CAL1_T - CAL2_T) + CAL2_V;
  return (voltage_mv * DO_Table[temperature_c] / V_saturation);
#endif
}