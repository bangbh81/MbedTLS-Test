/*
       FileName:	      Random.c
	  Description:	  Using MCU;s ADC value as the seed to create 32 bit random number for SSL progress 
	  Aurthor:		  Angel
	  Date:		      2014/10/23	
	  Release:	    
*/

#include "Random.h"
#include "stdlib.h"

/**************************** macro define *******************/

/**************************** data struct define ************/

/**************************** function define ***************/
static my_random_GPIO_Config(void);
static my_random_ADC_Init(void);

/************************************************************/
void random_init(void)
{
	  my_random_GPIO_Config();
	  my_random_ADC_Init();
}

/*
      Function£º
	          Get 32 bit random number 
	    Parameter£º
	          Get the 32 bit random number range 
	    Return Value£º
	          32 bit random number
*/
int my_random(int MaxValue)
{
      int seed;

	  ADC_SoftwareStartConvCmd(ADC1, ENABLE);	      //Start ADC change

	  while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) != SET); //Wait for the changing progress has completed 

	  seed = ADC_GetConversionValue(ADC1); //Get the ADC value
	  srand(seed);						   //Call the random nuber seed 

	  return (rand() % MaxValue);
}

/*
	Function£º
			Create a Pseudo-random number value 
	Parameters£º
	      
	Return Value£º
		0 -- Success
		1 -- Fail

*/
int my_drbg_random( void *p_rng, unsigned char *output, int output_len )
{
    int i;

	if(output_len <= 0)
	{
         return (1);
	}
    for(i = 0;i < output_len;i++)
    {
       *output++ = my_random(100);
	}
	
	return (0);
}


/*
     Function£º
	          Set the random number by using the ADC pin headers 	            
	  Parameters£º
	            Nothing
	  Return Value:
	            Nothing
*/
static my_random_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;  

	//SET GPIO pin 0 into PA0                      
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA| RCC_APB2Periph_ADC1, ENABLE);
}

/*
      Function £º
			  Initialize ADC function 
	    Parameters£º

	    Return values£º

*/
static my_random_ADC_Init(void)
{
 	ADC_InitTypeDef ADC_InitStructure;
 
    //The following are ADC1's registers settings 
  	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//AD module will select as independent mode 
  	ADC_InitStructure.ADC_ScanConvMode = ENABLE;//auto scan mode has been enable 
  	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//Continuous convertion mode is enable 
  	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//Not external trigger interrupt function  
  	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//data align to right 
  	ADC_InitStructure.ADC_NbrOfChannel = 1;//initialize ADC channel into 1 
  	ADC_Init(ADC1, &ADC_InitStructure);//Build ADC1 settings 
  	//PA0 & ADC1 related channel is 0
  	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	  //USE ADC1
  	ADC_Cmd(ADC1, ENABLE);
  	//Reset ADC1's regiters  
  	ADC_ResetCalibration(ADC1);
    //Wait until the reset has been done  	
  	while(ADC_GetResetCalibrationStatus(ADC1));
  	//Start the calibration for ADC1 
  	ADC_StartCalibration(ADC1);
  	//Wait until ADC1 calibration has been done  	
  	while(ADC_GetCalibrationStatus(ADC1));
    //Convert to use ADC1 
  	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

int my_ctr_drbg_random( void *p_rng, unsigned char *output, size_t output_len )
{
    int i;

	if(output_len <= 0)
	{
         return (1);
	}
    for(i = 0;i < output_len;i++)
    {
       *output++ = my_random(100);
	}

	return (0);
}
