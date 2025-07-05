/*
    Порты с GPIO_Pin_11 по GPIO_Pin_0 это выходной сигнал манчестера
    Порт GPIO_Pin_12 - сигнал front
    Порт GPIO_Pin_13 - сигнал not_work
*/
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

#define FRONT GPIO_Pin_12 
#define NOT_WORK GPIO_Pin_13 

/* Includes ------------------------------------------------------------------*/
#include "gw1ns4c.h"
#include <stdio.h>
/* Declarations ------------------------------------------------------------------*/
void delay_ms(__IO uint32_t delay_ms);
void GPIOInit(void);
void UartInit(void);
uint8_t crc8(uint8_t *pblock, uint8_t len);

uint8_t send_data[4] = {0x2A, 0, 0, 0};

/* Functions ------------------------------------------------------------------*/
int main(void)
{
    uint8_t flag = 0;   
    uint16_t data = 0;
    uint16_t inp_data = 0;
    uint16_t flags = 0;
    
	SystemInit();	//Initializes system
	GPIOInit();		//Initializes GPIO
    UartInit();		//Initializes UART0
    
    GPIO0->DATAOUT |= GPIO_Pin_15;
    delay_ms(5);
    //printf("\nKSOI_Single_ch_Receiver\r\n");
    
    while(1)
    {
        inp_data = GPIO_ReadBits(GPIO0); //читаем порт
//        flags = (0x3000 & inp_data);//выделим сигналы front и not_work (13 и 14 бит)
        flags = (0x1000 & inp_data);//выделим сигнал front(13 бит)
        if(flags)
        {
            
            uint16_t temp_value;
			temp_value = inp_data & 0x0FFF;
            send_data[2] = (uint8_t) temp_value;
			send_data[1] = (uint8_t) (temp_value >> 8);
			send_data[3] = crc8(send_data, 3);
			inp_data = 0x111;
            
            UART_SendChar(UART0, send_data[0]);
            UART_SendChar(UART0, send_data[1]);
            UART_SendChar(UART0, send_data[2]);
            UART_SendChar(UART0, send_data[3]);
            
            //GPIO0->DATAOUT &= ~GPIO_Pin_15;
        }

        for(data = 0; data <= 3; data++)
        {
            __NOP();
        }

    }
}
//Initializes GPIO
void GPIOInit(void)
{
    GPIO_InitTypeDef GPIO_InitType;

    GPIO_InitType.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
    GPIO_InitType.GPIO_Mode = GPIO_Mode_IN;
    GPIO_Init(GPIO0,&GPIO_InitType);
    
    GPIO_InitType.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitType.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(GPIO0,&GPIO_InitType);
    GPIO_SetBit(GPIO0,GPIO_Pin_15);
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
    UART_InitStruct.UART_BaudRate = 115200;//Baud Rate

    UART_Init(UART0,&UART_InitStruct);
}
//delay ms
void delay_ms(__IO uint32_t delay_ms)
{
    for(delay_ms=(SystemCoreClock>>13)*delay_ms; delay_ms != 0; delay_ms--);
}
//CRC8 
uint8_t crc8(uint8_t *pblock, uint8_t len)
{
    uint8_t crc = 255;
    uint8_t i;
 
    while (len--)
    {
        crc ^= *pblock++;
 
        for (i = 0; i < 8; i++)
            crc = crc & 0x80 ? (crc << 1) ^ 0x07 : crc << 1;
    }
 
    return crc;
}
