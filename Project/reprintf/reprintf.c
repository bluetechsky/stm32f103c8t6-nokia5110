/**
  ******************************************************************************
  * @file       reprintf.c
  * @author     linhkien69.vn
  * @version    V1.0.0
  * @date       28/02/2013
  ******************************************************************************
*/
#include <stdio.h>
#include "reprintf.h"
#include "nokia_5110.h"
#include "stm32f10x_usart.h"

extern int8_t target;

PUTCHAR_PROTOTYPE
{
   /* Place your implementation of fputc here */
     /* e.g. write a character to the LCD */
   if ( target )LCDCharacter((char) ch);    //lcd_Data_Write((u8)ch);
   else 
   {
   USART_SendData(USART1, (uint8_t) ch);

   /* Loop until the end of transmission */
   while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
   {}
   }
     return ch;
}

/************************* linhkien69.vn ************************END OF FILE****/
