/*
 * it.c
 *
 *  Created on: Mar 26, 2023
 *      Author: Nguyen Tran
 */


#include "main.h"
#include "it.h"



void EXTI0_IRQHandler(void)
{
	TurnOn_UserLed();
	UART_Send_Request_DMA();

	Clear_EXTI_Pending_Bit();
}


void DMA1_Stream3_IRQHandler(void)
{
	if(Half_Transfer())
	{
		DMA1->LIFCR |= (0x1U << 26); //clear flag
		DMA_HT_Complete_Callback();
	}else if(Full_Transfer())
	{
		DMA1->LIFCR |= (0x1U << 27); //clear flag
		DMA_FT_Complete_Callback();
	}else if(Transfer_Error())
	{
		DMA1->LIFCR |= (0x1U << 25); //clear flag
		DMA_TE_Error_Callback();
	}else if(FIFO_overrun_underrun())
	{
		DMA1->LIFCR |= (0x1U << 22); //clear flag
		DMA_FE_Error_Callback();
	}else if(Direct_mode_error())
	{
		DMA1->LIFCR |= (0x1U << 24); //clear flag
		DMA_DME_Error_Callback();
	}
}




void Clear_EXTI_Pending_Bit(void)
{
	if((EXTI->PR & (1 << 0)))
	{
		EXTI->PR |= (1 << 0);
	}
}


void TurnOn_UserLed(void)
{
	GPIOG -> ODR |= USER_LED;
}


void UART_Send_Request_DMA(void)
{
	USART3->CR3 |= DMA_ENABLE_TRANSMITTER;
}

void Clear_UART_Send_DMA_Request(void)
{
	USART3->CR3 &= ~(DMA_ENABLE_TRANSMITTER);
}
