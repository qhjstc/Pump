//
// Created by QHJSTC on 2021/1/16.
//
#include "Esp8266.h"
/****************************************************
 *
 * wifi ´®¿Úº¯Êý
 * ESP8266µ÷ÊÔ
 *
******************************************************/
#define TransmitDelay 20

u8 Rx_Buff[4] = {};
u8 Rx_data[50] = {};
u8 Wifi_DataSta = 0;         //1 is the data ok, 0 is preparing
u8 Wifi_Buff[Wifi_BuffSize] = {};
u8 Wifi_data[Wifi_Size] = {};
int Wifi_Index = 0;
struct Esp8266 Esp8266Wifi;

void Wifi_Init(){
    HAL_UART_Receive_DMA(&huart2, (u8*) Wifi_Buff, Wifi_BuffSize);
/************************************/
    Wifi_Send("AT\r\n");                                 //send the information to the wifi
    HAL_Delay(TransmitDelay);
    Wifi_Send("AT+GMR\r\n");
    HAL_Delay(TransmitDelay);
    Wifi_ClientConfigure();
}

void Wifi_Send(u8 *data){
    HAL_UART_Transmit(&huart2, (u8 *)data, strlen(data), 0xFFFF);
}

//Single connection client
void Wifi_ClientConfigure() {
    Wifi_Send("AT+CWMODE=1\r\n");
    HAL_Delay(TransmitDelay);
    Wifi_Send("AT+RST\r\n");
    HAL_Delay(4000);          //Wait 3 seconds RST to complete configuration
    Wifi_Send("AT+CWJAP=\"KC114\",\"kc114kc114\"\r\n");
    HAL_Delay(10000);
    Wifi_Send("AT+CIPMUX=0\r\n");
    HAL_Delay(TransmitDelay);
    Wifi_Send("AT+CIPMODE=1\r\n");
    HAL_Delay(TransmitDelay);
    Wifi_Send("AT\r\n");     //check whether the wifi modular is ok?
}

//Analyse the Wifi_data
void Wifi_DataAnalysis(){
    if(Wifi_DataSta == 1) {
        //printf("We have receive the wifi data\r\n");
        printf(Wifi_data);
        memset(Wifi_data, 0, Wifi_Size);         //wipe data;
        Wifi_Index = 0;
        Wifi_DataSta = 0;
    }
}

//set the wifi agreement
//the star: "00"  end: "10"
void Wifi_DataHandle(u8 *data){
    int start_sta = 0;
    for(int i = 0; i < strlen(data)-1; i++){
        if(start_sta == 0 && data[i] == '0' && data[i+1] == '0'){    //if the data is 11, indicates that data transmission begins
            start_sta++;
            printf("Data begin!\r\n");
        }
        else if(start_sta > 0 && data[i] == '1' && data[i+1] == '0'){
            start_sta = 0;
            Esp8266Wifi.Size++;
            printf("Data End!\r\n");

        }
        else if(start_sta == 1){                //the main part of data
            Esp8266Wifi.Message[Esp8266Wifi.Size][i] = Wifi_data[i];
        }
    }
    if(start_sta == 1){
        printf("Data error!\r\n");
    }
}

void Link_Serve(){
    Wifi_Send("AT+CIPSTART=\"TCP\",\"192.168.43.177\",8080\r\n");
}