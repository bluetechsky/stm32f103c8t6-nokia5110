/**
  ******************************************************************************
  * @file       main.h
  * @author     linhkien69.vn
  * @version    V1.0.0
  * @date       28/02/2013
  ******************************************************************************
*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
 extern "C" {
#endif 

#include "stm32f10x.h"

void RCC_Configuration(void);
void USART1_Configuration(void);
void Delay(__IO uint32_t num);
void Delay_ms(__IO uint32_t nTime);
void TimingDelay_Decrement(void);

#ifdef __GNUC__
	 
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/***
** @addtogroup STM32F10x_GEM3M_Examples.
  * @  Examples/Driver_Remap/main.h.
  * @  ARMPTIT NguyenVanThien Application. 
  * @  Header file for main.c module.
** @addtogroup STM32F10x_StdPeriph_Driver
***/

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */


/************************* linhkien69.vn ************************END OF FILE****/
