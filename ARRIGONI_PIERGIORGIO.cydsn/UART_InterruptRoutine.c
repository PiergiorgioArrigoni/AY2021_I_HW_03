/**
 * \file InterruptRoutine.c
 * \brief Source file for UART Interrupt Routine
 * \author Piergiorgio Arrigoni
*/

#include "UART_InterruptRoutine.h"

extern uint8_t flag_uart;

CY_ISR(UART_ISR)
{
    if(UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
        flag_uart = 1;
}

/* [] END OF FILE */