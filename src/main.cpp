#include <Arduino.h>


// local headers
#include "configs.h"
#include "DataStructure.h"
#include "DS3231Driver.h"
#include "SDCardDriver.h"
#include "GpsDriver.h"
#include "DS18B20Driver.h"
#include "DOSensor.h"
#include "SubmersiblePressure.h"
#include "LoraSX1278.h"


/* **************************************** Global variables definition**************************************** */

const char *NAME = "SPARC&COMPASTEM";
const char *prompt = "WQM> ";

char dateTime_string[25];
char dataCalib_string[50];
char sensorDataString[64];

struct sensorData sensorData_st;
struct calibData calibData_st;
struct connectionStatus connectionStatus_st;


char espID[32];
char topic[32];

const char fileNameCalib[] = "calib.txt";			// file chua cac gia tri calib
char nameFileSaveData[12];							// ten file luu du lieu cua sensor theo tung ngay

RTC_DS3231 realTime;
TinyGPSPlus gps;

bool RF_requestData;

float densityWaterTemp = 1.0;
float densityWater = 1.0;
void device_getData(){
  //Get Latitude & Longitude
  if(connectionStatus_st.gpsStatus == status_et::CONNECTED)
    gps_getData(sensorData_st.lat_f, sensorData_st.lon_f);
  //Get temperature
  DS18B20_getData(sensorData_st.temperature);
  //Get DO value
  averageSensorVoltage(PIN_NUM_DO_SENSOR, sensorData_st.DO_voltage);
  DO_getData(sensorData_st.DO_voltage, sensorData_st.temperature, sensorData_st.DO_value);
  //Get depth
  averageSensorVoltage(PIN_NUM_PRESSURE_SENSOR, sensorData_st.pressVoltage);
  submersiblePressure_getDepth(sensorData_st.pressVoltage, sensorData_st.pressCurrent, sensorData_st.depth, densityWater);
  log_i("Get data successfully!");

}

void device_dataManagement(){
  DS3231_getStringDateTime(realTime, DateTime::TIMESTAMP_FULL , dateTime_string);
  createSensorDataString(sensorDataString, NAME_DEVICE, dateTime_string, sensorData_st);
  DS3231_getStringDateTime(realTime, DateTime::TIMESTAMP_DATE, nameFileSaveData);
  LoraSX1278_sendDataString(sensorDataString, BRIDGE_DEVICE_ADDR, MEASUREMENT_DEVICE_ADDR);
  SDcard_saveStringDataToFile(nameFileSaveData,&connectionStatus_st, sensorDataString);
  LoRa.receive();
}

void setup() {

  pinMode(PIN_NUM_WARM_UP_LED, OUTPUT);
  pinMode(PIN_NUM_5V_CTRL, OUTPUT);
  pinMode(PIN_NUM_12V_CTRL, OUTPUT);
  pinMode(PIN_NUM_DO_SENSOR, INPUT);
  pinMode(PIN_NUM_PRESSURE_SENSOR, INPUT);

  digitalWrite(PIN_NUM_WARM_UP_LED, LOW);

  digitalWrite(PIN_NUM_5V_CTRL, LOW);
  digitalWrite(PIN_NUM_12V_CTRL, LOW);

  RF_requestData = false;

  Serial.begin(9600);
  gps_init();
  DS3231_init(realTime, Wire);
  DS18B20_init();
  SDcard_init(PIN_NUM_CLK, PIN_NUM_MISO, PIN_NUM_MOSI, PIN_CS_SD_CARD, &connectionStatus_st);
  LoraSX1278_Init();
  log_i("Warm up submersible pressure sensor and GPS module in 3 minutes...");
  delay(3*60*1000);
  //delay(10000);
  digitalWrite(PIN_NUM_WARM_UP_LED, HIGH);
  log_i("Init all successfully");
}

//For single-point calibration
// uint32_t DO_raw;
// uint32_t DO_cal1V;
// float DO_cal1T;


void loop() {
  /* ****************************************Single-point calibration for DO sensor**************************************** */
  
  // DO_raw = analogRead(PIN_NUM_DO_SENSOR);
  // DO_cal1V = DO_raw * VREF / ADC_RES;
  // DS18B20_getData(DO_cal1T);
  // Serial.println("CAL1V:\t" + String(DO_cal1V));
  // Serial.println("CAL1T:\t" + String(DO_cal1T));
  // delay(1000); 
  
  /* ****************************************Test submersible pressure sensor**************************************** */
  // averageSensorVoltage(PIN_NUM_PRESSURE_SENSOR, sensorData_st.pressVoltage);
  // Serial.println(sensorData_st.pressVoltage);
  // submersiblePressure_getDepth(sensorData_st.pressVoltage, sensorData_st.pressCurrent, sensorData_st.depth);
  // Serial.println(sensorData_st.pressCurrent);
  // Serial.println(sensorData_st.depth);
  // delay(2000);

  /* ****************************************Main code**************************************** */
  
  if(RF_requestData == true){
    log_i("Receive request successfully!");
    while(Serial2.available() > 0){
        gps.encode(Serial2.read());      
    }
    if(densityWaterTemp != 0.00f){
      densityWater = densityWaterTemp;
    }
    Serial.println(densityWater);
    digitalWrite(PIN_NUM_5V_CTRL, HIGH);
    digitalWrite(PIN_NUM_12V_CTRL, HIGH);
    device_getData();
    device_dataManagement();
    digitalWrite(PIN_NUM_5V_CTRL, LOW);
    digitalWrite(PIN_NUM_12V_CTRL, LOW);
    RF_requestData = false;
  } 

  // if(LoraSX1278_receiveRequest() == ERROR_NONE){
  //   digitalWrite(PIN_NUM_5V_CTRL, HIGH);
  //   digitalWrite(PIN_NUM_12V_CTRL, HIGH);
  //   device_getData();
  //   device_dataManagement();
  //   digitalWrite(PIN_NUM_5V_CTRL, LOW);
  //   digitalWrite(PIN_NUM_12V_CTRL, LOW);
  // }

}

