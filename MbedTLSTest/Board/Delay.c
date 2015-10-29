/*
* FunctionName: delay.c
* Author:       Angel
* Versio:       V0.0
* Data  :       2011/11/22 
* Description:  use systick to make accurate delay  
               eg:DelayNms(1000)// delay 1s
  Release:     
               1. add DelayNus()                 angel     2014/8/26
               2. ���systick��ѯ��ʽʵ����ʱ    angel     2014/8/29
*/

#include "delay.h"
#include "stm32f10x.h"

/*************************************** macro define **********************/
//#define __SYSTICK_HANDLER__  //ʹ���жϷ�ʽʵ����ʱ����Ҫ�޸�SysTick_Handler()

/*************************************** data struct define ****************/
static unsigned char    fac_us=0;//us��ʱ������
static unsigned short   fac_ms=0;//ms��ʱ������

/************************************** function define ********************/


static unsigned int TimingDelay;

/**
 * @brief  Setup SysTick Timer for 1 msec interrupts
 * @param  void
 * @retval void
*/

void SysTick_Init(void)
{
#ifdef __SYSTICK_HANDLER__

	SysTick_Config(SystemFrequency / 1000);
       fac_us =72/8;
#else

       SysTick->CTRL&=0xFFFFFFFb;
       fac_us =72/8;
	fac_ms=(unsigned short)fac_us*1000;
		
#endif
}

/**
 * @brief  delay ms if nTime =1000 ,delay time = 1000*1(ms)  
 * @param  void
 * @retval void
*/
void DelayNms(unsigned int nTime)
{ 
#ifdef __SYSTICK_HANDLER__

 TimingDelay = nTime;

  while(TimingDelay != 0);
  
#else
       unsigned int temp;

	SysTick->LOAD=(unsigned int)nTime*fac_ms;//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;           //��ռ�����
	SysTick->CTRL=0x01 ;          //��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	  	 

#endif
}

/**
 * @brief add this funciton to stm32f10x_it.c SysTick_Handler(){}  
 * @param  void
 * @retval void
*/
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

/*
  ��ʱnus
*/
void DelayNus(unsigned int nTime)
{		
	u32 temp;	    	 
	SysTick->LOAD=nTime*fac_us; //ʱ�����	  		 
	SysTick->VAL=0x00;                 //��ռ�����
	SysTick->CTRL=0x01 ;              //��ʼ���� 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	 
}


