#ifndef SYSTICK_H
#define SYSTICK_H

#include "Systick_Register.h"

typedef struct
{
    unsigned int fSystick;                      /*!< F clock source(Hz)                          */
    unsigned int period;                        /*!< Period of timer(ms)                         */
    unsigned char isInterruptEnabled;           /*!< Enable SysTick exception request            */
} Systick_ConfigType;

void Systick_Init(const Systick_ConfigType* ConfigPtr);

void Systick_Start(void);

void Systick_Stop(void);

unsigned int Systick_GetCounter(void);

void Delay(unsigned int ms);

#endif
