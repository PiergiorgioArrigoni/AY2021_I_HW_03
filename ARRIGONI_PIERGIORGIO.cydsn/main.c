/**
 * \file main.c
 * \brief Main source file for Homework 3
 * \author Piergiorgio Arrigoni
*/

#include "project.h"
#include "UART_InterruptRoutine.h"
#include "Timer_InterruptRoutine.h"

uint8_t flag_uart = 0;
uint8_t flag_timer = 0;

int main(void)
{
    //initialize components
    UART_Start();
    Timer_Start();
    Red_PWM_Start();
    Green_PWM_Start();
    
    //enable UART interrupt
    CyGlobalIntEnable;
    ISR_UART_StartEx(UART_ISR);
    
    uint8_t flag_complete;
    uint8_t received;
    uint8_t rgb[3];

    for(;;)
    {
        if(flag_uart)
        {   
            flag_uart = 0;
            received = UART_ReadRxData();
            if(received == 0xA0){
                //timer reset
                for(;;)
                {
                    if(flag_timer || flag_complete)
                        break;
                    if(flag_uart)
                    {
                        flag_uart = 0;
                        rgb[0] = UART_ReadRxData(); //red value
                        //timer reset
                        for(;;)
                        {
                            if(flag_timer || flag_complete)
                                break;
                            if(flag_uart)
                            {
                                flag_uart = 0;
                                rgb[1] = UART_ReadRxData(); //green value
                                //timer reset
                                for(;;)
                                {
                                    if(flag_timer || flag_complete)
                                        break;
                                    if(flag_uart)
                                    {
                                        flag_uart = 0;
                                        rgb[2] = UART_ReadRxData(); //blue value
                                        //timer reset
                                        for(;;)
                                        {
                                            if(flag_timer)
                                                break;
                                            if(flag_uart)
                                            {
                                                flag_uart = 0;
                                                received = UART_ReadRxData();
                                                if(received == 0xC0){
                                                    flag_complete = 1;
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                
                flag_timer = 0;
                if(flag_complete)
                {   
                    flag_complete = 0;
                    //pwm
                }        
            }
            else if(received == 'v')
                UART_PutString("RGB LED Program $$$");               
        }
    }
}

/* [] END OF FILE */
