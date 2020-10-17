/**
 * \file InterruptRoutine.h
 * \brief Header file for Timer Interrupt Routine
 * \author Piergiorgio Arrigoni
*/

#ifndef __TIMER_ROUTINE_H__
    #define __TIMER_ROUTINE_H__
    
    #include "project.h"
    
    extern uint8_t flag_timer;
    
    CY_ISR_PROTO(Timer_ISR);
#endif

/* [] END OF FILE */
