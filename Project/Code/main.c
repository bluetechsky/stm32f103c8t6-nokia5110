/**
  ******************************************************************************
  * @file       main.c
  * @author     linhkien69.vn
  * @version    V1.0.0
  * @date       28/02/2013
  ******************************************************************************
*/
#include <stdio.h>
#include "nokia_5110.h"
#include "hinh_anh.h"
#include "main.h"


int8_t target=0;
unsigned char Data[16];
  
GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;
static __IO uint32_t TimingDelay;


void RCC_Configuration(void)
{	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 
}

void USART1_Configuration(void)
{
	/* Configure PA9 for USART Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure PA10 for USART Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	/* USARTx configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  	*/
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	

	/* USART configuration */
	USART_Init(USART1, &USART_InitStructure);

	/* Enable USART */
	USART_Cmd(USART1, ENABLE);	
}

void Delay(__IO uint32_t num)
{
	__IO uint32_t index = 0;
	for(index = (720000 * num); index != 0; index--){}
}

void Delay_ms(__IO uint32_t nTime)
{ 
	TimingDelay = nTime;
	while(TimingDelay != 0){}
}

void TimingDelay_Decrement(void)
{	
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}

uint32_t clk_freq;
void get_clock()
{
	RCC_ClocksTypeDef RCC_Config;
	RCC_GetClocksFreq(&RCC_Config);
	clk_freq = RCC_Config.PCLK2_Frequency;
}

int main(void)
{ 
	/* Configure the system clocks */
	RCC_Configuration();
	USART1_Configuration();
	get_clock();
	
  LCDInit(0x30, 0, 1);
	Delay(10);
	
	/* Disable the Serial Wire Jtag Debug Port SWJ-DP */
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, DISABLE);	 //Hung change from ENABLE

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	if (SysTick_Config(SystemCoreClock / 1000))
	{ 		
		/* Capture error */ 
		while (1){}
	}
	while (1)	
	{
		printf("SYSCLK %3u\n\r",clk_freq);
		
		LCDClear();
		gotoXY(0, 0);
		LCDString("linhkien69");
		gotoXY(64, 1);
		LCDString(".vn");
		gotoXY(0, 3);
		LCDString("Noki5110-LCD");
		Delay(15);
		loop();
		LCDWrite(LCD_CMD, 0x0D);
		Delay(15);
		LCDWrite(LCD_CMD, 0x0C);
		Delay_ms(4000);
	}
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif

/************************* linhkien69.vn ************************END OF FILE****/

