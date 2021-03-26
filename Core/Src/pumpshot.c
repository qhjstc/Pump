//
// Created by QHJSTC on 2021/3/9.
//
#include "pumpshot.h"
#define Minimal_Value 500
#define Maximum_Value 2500
u8 Working_State = 1;
ST Steer[2];

void Steer_Init(){
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
    Steer[Steer1].Value = 500;
    Steer[Steer2].Value = 500;
    __HAL_TIM_SET_COMPARE(&Steer[Steer1].Steer_htim, TIM_CHANNEL_1, Steer[Steer1].Value);
    __HAL_TIM_SET_COMPARE(&Steer[Steer2].Steer_htim, TIM_CHANNEL_1, Steer[Steer2].Value);
}

void Steer_Start(){
    HAL_TIM_Base_Start_IT(&htim3);
};

void Steer_Rotation(TIM_HandleTypeDef *htim, u16 value){
    __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, value);
}

void Uniform_Rotation(u8 number){
    // determine the direction
    if(Steer[number].Direction == Positive){
        Steer[number].Value += Steer[number].Speed;
    }
    else{
        Steer[number].Value -= Steer[number].Speed;
    }
    if(Steer[number].Value > Maximum_Value){
        Steer[number].Value = Maximum_Value;
        Steer[number].Ok_State = 1;
    }
    else if(Steer[number].Value < Minimal_Value) {
        Steer[number].Value = Minimal_Value;
    }
    Steer_Rotation(&Steer[number].Steer_htim, Steer[number].Value);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim == &htim3){
        if(!Steer[Steer1].Ok_State) {                                        // judge yaw is whether full
            Uniform_Rotation(Steer1);
        }
        else{                                                // if yaw has been full, judge pitch is whether full
            if(!Steer[Steer2].Ok_State){
                Uniform_Rotation(Steer2);
                Steer[Steer1].Ok_State = 0;
                Steer[Steer1].Value = Minimal_Value;
            }
            else{                                            // if yaw and pitch has been full, stop the tim.
                HAL_TIM_Base_Start_IT(&htim3);
            }
        }
	}
}


