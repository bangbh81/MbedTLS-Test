/*
* FunctionName: delay.h
* Author:       Angel
* Version:      V0.0
* Date  :       2011/11/22 
* Description:  use systick to make accurate delay  
               eg:DelayNms(1000)// delay 1s
**/

#ifndef __DELAY_H
#define __DELAY_H

/********************* macro define *********************/
#define SystemFrequency 72000000

/********************* define data struct *********************/

/********************* define function *********************/
void SysTick_Init(void);
void DelayNms(unsigned int nTime);
void DelayNus(unsigned int nTime);
void TimingDelay_Decrement(void);


#endif /* */


