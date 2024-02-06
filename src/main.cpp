#include <Arduino.h>


// local headers
#include "configs.h"
#include "DataStructure.h"
#include "DS3231Driver.h"
#include "SDCardDriver.h"
#include "GpsDriver.h"
#include "DS18B20Driver.h"
#include "DOSensor.h"


/* **************************************** Global variables definition**************************************** */

const char *NAME = "SPARC&COMPASTEM";
const char *prompt = "WQM> ";

char dateTime_string[25];
char dataCalib_string[50];
char sensorDataString[64];
String messageData;

struct sensorData sensorData_st;
struct calibData calibData_st;
struct connectionStatus connectionStatus_st;


char espID[32];
char topic[32];

const char fileNameCalib[] = "calib.txt";			// file chua cac gia tri calib
char nameFileSaveData[12];							// ten file luu du lieu cua sensor theo tung ngay


RTC_DS3231 realTime;


void setup() {
  pinMode(PIN_NUM_5V_CTRL, OUTPUT);
  pinMode(PIN_NUM_12V_CTRL, OUTPUT);
  pinMode(PIN_NUM_DO_SENSOR, INPUT);
  pinMode(PIN_NUM_PRESSURE_SENSOR, INPUT);
  Serial.begin(115200);
  gps_init();
  DS3231_init(realTime, Wire);
  DS18B20_init();
  SDcard_init(PIN_NUM_CLK, PIN_NUM_MISO, PIN_NUM_MOSI, PIN_CS_SD_CARD, &connectionStatus_st);
  
}
/*
//For single-point calibration
uint32_t DO_raw;
uint32_t DO_cal1V;
float DO_cal1T;
*/

void loop() {
  /*
  //Single-point calibration for DO sensor
  DO_raw = analogRead(PIN_NUM_DO_SENSOR);
  DO_cal1V = DO_raw * VREF / ADC_RES;
  DS18B20_getData(DO_cal1T);
  Serial.println("CAL1V:\t" + String(DO_cal1V));
  Serial.println("CAL1T:\t" + String(DO_cal1T));
  delay(1000);*/


}

