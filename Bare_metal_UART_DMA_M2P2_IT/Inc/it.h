/*
 * it.h
 *
 *  Created on: Mar 26, 2023
 *      Author: Nguyen Tran
 */

#ifndef IT_H_
#define IT_H_

#define DMA_ENABLE_TRANSMITTER	(0x1U << 7)

#define Half_Transfer()				(DMA1->LISR & (0x1U << 26))
#define Full_Transfer()				(DMA1->LISR & (0x1U << 27))
#define Transfer_Error()			(DMA1->LISR & (0x1U << 25))
#define FIFO_overrun_underrun()		(DMA1->LISR & (0x1U << 22))
#define Direct_mode_error()			(DMA1->LISR & (0x1U << 24))


void TurnOn_UserLed(void);

void Clear_EXTI_Pending_Bit(void);
void UART_Send_Request_DMA(void);
void Clear_UART_Send_DMA_Request(void);

#endif /* IT_H_ */
