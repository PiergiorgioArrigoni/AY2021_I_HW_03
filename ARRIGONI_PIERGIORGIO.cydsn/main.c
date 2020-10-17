/**
 * \file main.c
 * \brief Main source file for Homework 3
 * \author Piergiorgio Arrigoni
*/

#include "project.h"
#include "UART_InterruptRoutine.h"
#include "Timer_InterruptRoutine.h"

#define PERIOD 250 //period of the timer (cooresponding to 5 seconds)

uint8_t flag_uart = 0; //flag of the UART interrupt (goes to 1 if one byte of data is received)
uint8_t flag_timer = 0; //flag of the timer interrupt (goes to 1 if timer completes a 5 seconds cycle)

int main(void)
{
    //initialize components
    UART_Start();
    Timer_Start();
    Red_PWM_Start();
    Green_PWM_Start();
    Blue_PWM_Start();

    CyGlobalIntEnable;
    ISR_UART_StartEx(UART_ISR); //enable UART interrupt
    
    uint8_t flag_complete = 0; //flag signaling the conslusion of the packet transmission
    uint8_t flag_error = 0; //flag signaling a error in transmission (wrong tyle byte)
    uint8_t received;
    uint8_t rgb[3]; //vector storing the duty cycles of the PWMs
    
    UART_PutString("IDLE state.\n"); //system starts in idle state

    for(;;)
    {
        if(flag_uart)
        {   
            flag_uart = 0; //same flag is then reused 
            received = UART_ReadRxData();
            if(received == 0xA0) //header byte
            {
                ISR_Timer_StartEx(Timer_ISR); //enable timer interrupt
                flag_timer = 0;
                Timer_Stop();
                Timer_WriteCounter(PERIOD); //reset timer counter
                Timer_Enable();
                UART_PutString("\nHeader byte received.\nWaiting for red value.\n");
                
                for(;;)
                {
                    if(flag_timer || flag_complete) //for cycles are broken by the timer interrupt or by the conclusion of the transmission
                        break;
                    if(flag_uart)
                    {
                        flag_uart = 0;
                        rgb[0] = UART_ReadRxData(); //red value
                        Timer_Stop();
                        Timer_WriteCounter(PERIOD);
                        Timer_Enable();
                        UART_PutString("Waiting for green value.\n");
                        
                        for(;;)
                        {
                            if(flag_timer || flag_complete)
                                break;
                            if(flag_uart)
                            {
                                flag_uart = 0;
                                rgb[1] = UART_ReadRxData(); //green value
                                Timer_Stop();
                                Timer_WriteCounter(PERIOD);
                                Timer_Enable();
                                UART_PutString("Waiting for blue value.\n");
                                
                                for(;;)
                                {
                                    if(flag_timer || flag_complete)
                                        break;
                                    if(flag_uart)
                                    {
                                        flag_uart = 0;
                                        rgb[2] = UART_ReadRxData(); //blue value
                                        Timer_Stop();
                                        Timer_WriteCounter(PERIOD);
                                        Timer_Enable();
                                        UART_PutString("Waiting for tail byte.\n");
                                        
                                        for(;;)
                                        {
                                            if(flag_timer)
                                                break;
                                            if(flag_uart)
                                            {
                                                flag_uart = 0;
                                                received = UART_ReadRxData();
                                                if(!(received == 0xC0)) //not tail byte
                                                    flag_error = 1;
                                                flag_complete = 1; //conclusion of the transmission
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                
                ISR_Timer_Stop(); //disable timer interrupt
                if(flag_timer)
                {
                    flag_timer = 0;
                    UART_PutString("\nTimeout.\nReturning to IDLE state.\n");
                }   
                else if(flag_error)
                {
                    flag_error = 0;
                    flag_complete = 0;
                    UART_PutString("\nAn error occured in the transmission: wrong tail byte.\nReturning to IDLE state.\n");
                }
                else //transmission was successful
                {   
                    flag_complete = 0;
                    Red_PWM_WriteCompare(rgb[0]);
                    Green_PWM_WriteCompare(rgb[1]);
                    Blue_PWM_WriteCompare(rgb[2]);
                    UART_PutString("\nTransmission complete.\nDisplaying color.\nReturning to IDLE state.\n");
                }        
            }
            else if(received == 'v')
                UART_PutString("RGB LED Program $$$"); //connection command          
        }
    }
}

/* [] END OF FILE */
