#include "LoraSX1278.h"
ERROR_CODE LoraSX1278_Init(){
    //DIO0 is optional
    LoRa.setPins(PIN_CS_RF_MODULE, PIN_RST_RF_MODULE, PIN_DIO0_RF_MODULE);
    uint8_t initCount=0;
    Serial.println("Initializing LoRaSX1278...");
    while(!LoRa.begin(LORA_SX1278_FREQ) && initCount<10){
        Serial.print(".");
        delay(1000);
        initCount++;
    }
    if(initCount==10){
        log_e("LoRaSX1278 init failed!");
        return ERROR_LORA_SX1278_INIT_FAILED;
    }
    #ifdef MEASUREMENT_DEVICE
    //Measurement device need to be in receive mode to wait for request
    LoRa.onReceive(LoraSX1278_receiveRequest);
    LoRa.receive();
    #endif
    
    #ifdef BRIDGE_DEVICE
    //set callback function to be called when packet is received
    LoRa.onReceive(LoraSX1278_receiveData);
    #endif

    log_i("LoRaSXX1278 init successfully!");
    return ERROR_NONE;
    
}
void LoraSX1278_sendDataString(char *data, uint8_t dest_addr, uint8_t src_addr){
    LoRa.beginPacket();                   // start packet
    LoRa.write(dest_addr);              // add destination address
    LoRa.write(src_addr);             // add sender address
    LoRa.write(strlen(data));        // add payload length
    LoRa.print(data);                 // add payload
    LoRa.endPacket();                     // finish packet and send it
    log_i("Send packet completely!");
}

void LoraSX1278_requestData(uint8_t dest_addr, uint8_t src_addr, uint8_t request_byte_1, uint8_t request_byte_2){
    LoRa.beginPacket();                   // start packet
    LoRa.write(dest_addr);              // add destination address
    LoRa.write(src_addr);             // add sender address
    LoRa.write(request_byte_1);        // add REQUEST_BYTE_1
    LoRa.write(request_byte_2);        // add REQUEST_BYTE_2
    LoRa.endPacket();                     // finish packet and send it
    log_i("Send request completely!");
}

void LoraSX1278_receiveData(int packetSize){
    if (packetSize == 0) return;          // if there's no packet, return

    // read packet header bytes:
    uint8_t recipient = LoRa.read();          // recipient address
    uint8_t sender = LoRa.read();            // sender address
    uint8_t incomingDataLength = LoRa.read();    // incoming msg length

    String incomingData = "";                 // payload of packet

    while (LoRa.available()) {            // can't use readString() in callback, so
      incomingData += (char)LoRa.read();      // add bytes one by one
    }

    if (incomingDataLength != incomingData.length()) {   // check length for error
      log_e("Datalength does not match length.");
      return;
    }

    // if the recipient isn't this device or broadcast,
    if (recipient != BRIDGE_DEVICE_ADDR && recipient != 0xFF) {
      log_e("This message is not for this device.");
      return;
    }

    //split dataString
    char* token = strtok((char*)incomingData.c_str(), ",");
    int count = 0;
    while(token != NULL){
        dataSplited[count] = token;
        count++;
        token = strtok(NULL, ",");
    }
}   

void LoraSX1278_receiveRequest(int packetSize){
    if (packetSize == 0) return;
      uint8_t recipient = LoRa.read();          // recipient address
      uint8_t sender = LoRa.read();            // sender address
      uint8_t request_byte_1 = LoRa.read(); 
      uint8_t request_byte_2 = LoRa.read(); 

      String incomingData = "";                 // payload of packet
      while (LoRa.available()) {            // can't use readString() in callback, so
        incomingData += (char)LoRa.read();      // add bytes one by one
      }
      // float value_fl = incomingData.toFloat();
      // if( value_fl != 0.00 ){ can't compare float value in callback function because it cause core dump
      // densityWater = value_fl;
      // }
      densityWaterTemp = incomingData.toFloat();
      if(request_byte_1 == REQUEST_BYTE_1 && request_byte_2 == REQUEST_BYTE_2){
        RF_requestData = true;
        //log_i("Receive request successfully!"); //can't use log_i and log_e in callback funtion because it cause core dump
        return;
      }
      //log_e("Receive request failed");
      return;
}

// ERROR_CODE LoraSX1278_receiveRequest(){
//     int packetSize = LoRa.parsePacket();
//     if (packetSize == 0) return ERROR_LORA_SX1278_RECEIVE_FAILED;
//       // uint8_t recipient = LoRa.read();          // recipient address
//       // uint8_t sender = LoRa.read();            // sender address
//       // uint8_t request_byte_1 = LoRa.read(); 
//       // uint8_t request_byte_2 = LoRa.read(); 
//       // if(request_byte_1 == REQUEST_BYTE_1 && request_byte_2 == REQUEST_BYTE_2){
//       //   RF_requestData = true;
//       //   log_i("Receive request successfully!");
//       //   return;
//       // }
//       // log_e("Receive request failed");
//       // return;
//     String string = "";
//       if(LoRa.available()){
//          string = LoRa.readString();
//       }
//       if(string != ""){
//         RF_requestData = true;
//         log_i("Receive request successfully!");
//         return ERROR_NONE;
//       } else{
//         log_e("Receive request failed");
//         return ERROR_LORA_SX1278_RECEIVE_FAILED;
//       }
//     log_e("No request received!");
//     return ERROR_LORA_SX1278_RECEIVE_FAILED;
// }