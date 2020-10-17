/**
 * \file InterruptRoutine.h
 * \brief Header file for UART Interrupt Routine
 * \author Piergiorgio Arrigoni
*/

#ifndef __INTERRUPT_ROUTINE_H__
    #define __INTERRUPT_ROUTINE_H__
    
    #include "project.h"
    
    extern uint8_t flag;
    
    CY_ISR_PROTO(UART_ISR);
#endif

/* [] END OF FILE */
