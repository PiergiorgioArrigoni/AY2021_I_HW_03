/**
 * \file InterruptRoutine.c
 * \brief Source file for UART Interrupt Routine
 * \author Piergiorgio Arrigoni
*/

#include "InterruptRoutine.h"

uint8_t flag;

CY_ISR(UART_ISR)
{
    if(UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
        flag = 1;
}

/* [] END OF FILE */
