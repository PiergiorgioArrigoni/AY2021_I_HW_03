/**
 * \file InterruptRoutine.c
 * \brief Source file for Timer Interrupt Routine
 * \author Piergiorgio Arrigoni
*/

#include "Timer_InterruptRoutine.h"

CY_ISR(Timer_ISR)
{
    flag_timer = 1;
}

/* [] END OF FILE */
