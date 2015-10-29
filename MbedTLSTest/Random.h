
/*
       FileName:	      Random.h
	  Description:	   Using MCU;s ADC value as the seed to create 32 bit random number for SSL progress 
	  Aurthor:		  Angel
	  Date:		      2014/10/23	
	  Release:
*/

#ifndef __RANOM_H__
#define __RANOM_H__

#include "stm32f10x.h"
#include <stdlib.h>
/**************************** macro define *******************/

/**************************** data struct define ************/

/**************************** function define ***************/
void random_init(void);
int my_random(int MaxValue);

int my_drbg_random( void *p_rng,
                     unsigned char *output, int output_len );
int my_ctr_drbg_random( void *p_rng, unsigned char *output, size_t output_len );


/************************************************************/

#endif  /* #ifndef __RANOM_H__ */
