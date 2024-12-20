
/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2021 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file			main.c
 * @author		Embedded Development Team
 * @version		V1.x.x
 * @date			2021-01-01 09:00:00
 * @brief			Main program body.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "gw1ns4c.h"
#include <stdio.h>
/* Declarations ------------------------------------------------------------------*/
void delay_ms(__IO uint32_t delay_ms);
void GPIOInit(void);
void UartInit(void);

/* Functions ------------------------------------------------------------------*/
int main(void)
{
    uint32_t num=0;
    
	SystemInit();	//Initializes system
	GPIOInit();		//Initializes GPIO
    UartInit();		//Initializes UART0
    
    printf("\nUart Initial finished\r\n");
	
    while(1)
    {
        GPIO_ResetBit(GPIO0,GPIO_Pin_0);	//LED1 on
        delay_ms(500);

        GPIO_SetBit(GPIO0,GPIO_Pin_0);		//LED1 off
        delay_ms(500);

        printf("\r\n");
        printf("%d ",num);  
        num++;

    }
}
//Initializes GPIO
void GPIOInit(void)
{
    GPIO_InitTypeDef GPIO_InitType;

    GPIO_InitType.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitType.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitType.GPIO_Int = GPIO_Int_Disable;

    GPIO_Init(GPIO0,&GPIO_InitType);

    GPIO_SetBit(GPIO0,GPIO_Pin_0);
}
//Initializes UART0
void UartInit(void)
{
    UART_InitTypeDef UART_InitStruct;

    UART_InitStruct.UART_Mode.UARTMode_Tx = ENABLE;
    UART_InitStruct.UART_Mode.UARTMode_Rx = ENABLE;
    UART_InitStruct.UART_Int.UARTInt_Tx = DISABLE;
    UART_InitStruct.UART_Int.UARTInt_Rx = DISABLE;
    UART_InitStruct.UART_Ovr.UARTOvr_Tx = DISABLE;
    UART_InitStruct.UART_Ovr.UARTOvr_Rx = DISABLE;
    UART_InitStruct.UART_Hstm = DISABLE;
    UART_InitStruct.UART_BaudRate = 9600;//Baud Rate

    UART_Init(UART0,&UART_InitStruct);
}
//delay ms
void delay_ms(__IO uint32_t delay_ms)
{
    for(delay_ms=(SystemCoreClock>>13)*delay_ms; delay_ms != 0; delay_ms--);
}
