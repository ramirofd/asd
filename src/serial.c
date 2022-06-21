/*
 * serial.c
 *
 *  Created on: 10 jun. 2022
 *      Author: ramir
 */

#include "serial.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include <string.h>

#define RX_BUFF_SIZE 1
#define DATA_SIZE	 40
#define START 		'*'
#define END   		';'

extern void Error_Handler(void);


enum RX_STATE{WAIT_START, RECV_DATA};
enum DATA_STATE{NOT_AVAILABLE, AVAILABLE};

enum RX_STATE rx_state;
enum DATA_STATE data_state;

UART_HandleTypeDef huart2;
uint8_t UART_rxBuffer[RX_BUFF_SIZE] = {0};
uint8_t data[DATA_SIZE] = {0};
int data_ptr = 0;

void resetData() {
	data_state = NOT_AVAILABLE;
	for(int i=0; i<DATA_SIZE; i++)
		data[i] = 0;
	data_ptr = 0;
}

void SERIAL_Init(void)
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 9600;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_Handler();
	}
	rx_state = WAIT_START;
	resetData();
	HAL_UART_Receive_IT (&huart2, UART_rxBuffer, RX_BUFF_SIZE);
}

void SERIAL_Write(uint8_t *data,  uint16_t size) {
	HAL_UART_Transmit(&huart2, data, size, 10);
}

int SERIAL_Available(){
	return data_state==AVAILABLE;
}

uint8_t* SERIAL_GetData(){
	data_state=NOT_AVAILABLE;
	return data;
}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART2)
  {
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART2)
  {
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

    HAL_NVIC_DisableIRQ(USART2_IRQn);
  }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    switch(UART_rxBuffer[0]) {
		case START:
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
			rx_state = RECV_DATA;
			resetData();
			break;
		case END:
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
			rx_state = WAIT_START;
			data_state = AVAILABLE;
			break;
		default:
			if(rx_state==RECV_DATA){
				data[data_ptr] = UART_rxBuffer[0];
				data_ptr++;
			}
			break;
    }

    HAL_UART_Receive_IT(&huart2, UART_rxBuffer, RX_BUFF_SIZE);
}
