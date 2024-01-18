#include <Arduino.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <ArduinoJson.h>


// local headers
#include "configs.h"
// #include "globals.h"

// #include "DeviceManager.h"
#include "DataStructure.h"
#include "DS3231Driver.h"
//#include "GpsDriver.h"


/******************************************************************************
 * Global variables definition
 */

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

}

void loop() {
  // put your main code here, to run repeatedly:
}

