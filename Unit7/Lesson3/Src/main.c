/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

//Learn-in-depth
//Keroles Shenouda
//Mastering_Embedded System online diploma

#include "stm32f103x6.h"
#include "GPIO.h"

void Clock_Init(){
	// Initialize clock for GPIOA
	RCC_GPIOA_CLOCK_EN();
	// Bit 3 IOPBEN: I/O port B clock enable
	RCC_GPIOB_CLOCK_EN();
}

void GPIO_Init(){
	GPIO_PinConfig_t PinCfg;
	// PA1 input high impedance floating input (Reset State)
	PinCfg.GPIO_PinNumber = GPIO_PIN_1;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(GPIOA, &PinCfg);

	// PB1 output push-pull mode
	// CNF 00: General purpose output push-pull
	// 01: Output mode, max speed 10 MHz
	PinCfg.GPIO_PinNumber = GPIO_PIN_1;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PUSH_PULL;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &PinCfg);

	// PA13 input high impedance floating input (Reset State)
	PinCfg.GPIO_PinNumber = GPIO_PIN_13;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(GPIOA, &PinCfg);

	// PB13 output push-pull mode
	PinCfg.GPIO_PinNumber = GPIO_PIN_13;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PUSH_PULL;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &PinCfg);
}

void my_wait(int x){
	unsigned int i , j;
	for(i = 0; i < x; i++){
		for(j = 0; j < 255; j++);
	}
}

int main(void)
{
	Clock_Init();
	GPIO_Init();

	while(1)
	{
		// PA1 connected with external Pull Up Resistance
		if(MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 0){
			MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
			while( MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 0 ); // single press
		}
		// PA13 connected with external Pull Down Resistance
		if(MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13) == 1){
			MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
		}
		my_wait(1);
	}
	return 0;
}
