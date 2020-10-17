/**
 * \file main.c
 * \brief Main source file for Homework 3
 * \author Piergiorgio Arrigoni
*/

#include "project.h"

int main(void)
{
    //initialize components
    Timer_Start();
    UART_Start();
    Red_PWM_Start();
    Green_PWM_Start();
    
    CyGlobalIntEnable;
    ISR_UART_StartEx(UART_ISR); //enable UART interrupt

    for(;;)
    {
    }
}

/* [] END OF FILE */
