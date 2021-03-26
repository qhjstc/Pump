//
// Created by QHJSTC on 2021/3/9.
//

#ifndef PUMP_PUMPSHOT_H
#define PUMP_PUMPSHOT_H

#include "main.h"
#include "tim.h"

#define Positive 100
#define Reverse  101
#define Rotation_Speed 100
#define Steer1 0
#define Steer2 1
extern u8 Working_State;

typedef struct{
    TIM_HandleTypeDef Steer_htim;
    u16 Value;
    u16 Speed;
    u8  Ok_State;
    u8  Direction;
}ST;

void Steer_Init();
void Steer_Start();
void Steer_Rotation(TIM_HandleTypeDef *htim, u16 value);
void Uniform_Rotation(u8 number);

#endif //PUMP_PUMPSHOT_H



