
#include "sound.h"

#define C   261 //Do
#define C_  277 //Do#
#define D   293 //Re
#define D_  311 //Re#
#define E   239 //Mi
#define F   349 //Fa
#define F_  370 //Fa#
#define G   392 //Sol
#define G_  415 //Sol#
#define A   440 //La
#define A_  466 //La#
#define H   494 //Si

#define t1      2000
#define t2      1000
#define t4      500
#define t8      250
#define t16     125

typedef struct
{
    uint16_t freq;
    uint16_t time;
}SoundTypeDef;

#define MUSICSIZE 48

const SoundTypeDef Music[MUSICSIZE] ={
    {C*2, t4},
    {G, t4},
    {A_, t8},
    {F, t8},
    {D_, t8},
    {F, t8},
    {G, t4},
    {C, t2},
    {C*2, t4},
    {G, t4},
    {A_, t8},
    {F, t8},
    {D_, t8},
    {F, t8},
    {G, t4},
    {C*2, t4},
    {0, t8},
    {D_, t8},
    {D_, t8},
    {D_, t8},
    {G, t8},
    {A_, t4},
    {D_*2, t8},
    {C_*2, t8},
    {C*2, t8},
    {C*2, t8},
    {C*2, t8},
    {C*2, t8},
    {A_, t8},
    {F, t8},
    {D_, t8},
    {F, t8},
    {G, t4},
    {C*2, t2},
    {C*2, t2},
    {A_, t8},
    {G_, t8},
    {G, t8},
    {G_, t8},
    {A_, t2},
    {A_, t4},
    {C*2, t4},
    {A_, t8},
    {F, t8},
    {D_, t8},
    {F, t8},
    {G, t4},
    {C*2, t2}
};

__IO int MusicStep = 0;
__IO char PlayMusic = 0;
__IO int sound_time;
__IO int sound_counter;

void sound(int freq, int time_ms) {
    if (freq > 0) {
    	__HAL_TIM_SET_AUTORELOAD(&htim1, HAL_RCC_GetHCLKFreq() / (htim1.Init.Prescaler+1) / freq);
    	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, __HAL_TIM_GET_AUTORELOAD(&htim1) / 2);
    }
    else {
    	__HAL_TIM_SET_AUTORELOAD(&htim1, 2000);
    	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
    }

    __HAL_TIM_SET_COUNTER(&htim1, 0);

    sound_time = ((HAL_RCC_GetHCLKFreq() / (htim1.Init.Prescaler+1) / __HAL_TIM_GET_AUTORELOAD(&htim1)) * time_ms ) / 1000;
    sound_counter = 0;
//    __HAL_TIM_ENABLE(&htim1);
}


void StartMusic(void) {
    MusicStep = 0;
    PlayMusic = 1;
    sound(Music[MusicStep].freq, Music[MusicStep].time);
}

// обработка для таймера звука
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance==TIM1) {  //check if the interrupt comes from TIM1
        sound_counter++;
        if (sound_counter > sound_time) {
            if (PlayMusic == 0) {
//            	__HAL_TIM_DISABLE(&htim1);
            	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
            }
            else {
                if (MusicStep < MUSICSIZE-1) {
                	if (__HAL_TIM_GET_COMPARE(&htim1, TIM_CHANNEL_1) == 0) {
                        MusicStep++;
                        sound(Music[MusicStep].freq, Music[MusicStep].time);
                    }
                    else {
                        sound(0, 30);
                    }
                }
                else {
                    PlayMusic = 0;
//                	__HAL_TIM_DISABLE(&htim1);
                	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
                }
            }
        }
    }
}

/*
void TIM4_IRQHandler(void){

    if (TIM_GetITStatus(TIM4, TIM_IT_CC4) != RESET)
      {
        / * Reset flag * /
        TIM_ClearITPendingBit(TIM4, TIM_IT_CC4);

        sound_counter++;
        if (sound_counter > sound_time) {
            if (PlayMusic == 0) {
                TIM_Cmd(TIM4, DISABLE);
            }
            else {
                if (MusicStep < MUSICSIZE-1) { if (TIM4->CCR1 == 0){
                        MusicStep++;
                        sound(Music[MusicStep].freq, Music[MusicStep].time);
                    }
                    else{
                        sound(0, 30);
                    }
                }
                else {
                    PlayMusic = 0;
                    TIM_Cmd(TIM4, DISABLE);
                }
            }
        }

        / * over-capture * /
        if (TIM_GetFlagStatus(TIM4, TIM_FLAG_CC4OF) != RESET)
        {
          TIM_ClearFlag(TIM4, TIM_FLAG_CC4OF);
          // ...
        }
      }
}
*/
/*
int main(void)
{
    SetSysClockTo72();
    sound_init();

    //sound (440, 1000);
    StartMusic();

    while(1)
    {

    }

}
*/
