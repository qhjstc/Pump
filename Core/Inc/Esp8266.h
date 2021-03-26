//
// Created by QHJSTC on 2021/1/16.
//

#ifndef TESTWIFI_ESP8266_H
#define TESTWIFI_ESP8266_H

#include "main.h"
#include "usart.h"
#include "string.h"

/*****外接设备********/

#define Wifi_Size 255
#define Wifi_BuffSize 1
#define Message_Size 20

struct Esp8266{
    u8 Message[Message_Size][Wifi_Size];
    u8 Size;
};


extern u8 Rx_Buff[4];
extern u8 Rx_data[50];
extern u8 Wifi_DataSta;
extern u8 Wifi_Buff[Wifi_BuffSize];
extern u8 Wifi_data[Wifi_Size];
extern int Wifi_Index;

void Wifi_Init();
void Wifi_Send(u8 *data);
void Wifi_ClientConfigure();
void Wifi_DataAnalysis();
void Wifi_DataHandle(u8 *data);
void Link_Serve();

#endif //TESTWIFI_ESP8266_H
