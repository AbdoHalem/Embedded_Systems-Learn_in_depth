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
typedef volatile unsigned int vuint32_t ;
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// Register Address
#define GPIOA_BASE 0x40010800
#define GPIOA_CRL *(volatile uint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_CRH *(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR *(volatile uint32_t *)(GPIOA_BASE + 0x0C)
#define GPIOA_IDR *(volatile uint32_t *)(GPIOA_BASE + 0x08)
#define GPIOA13    (1UL << 13)

#define GPIOB_BASE 0x40010C00
#define GPIOB_CRL *(volatile uint32_t *)(GPIOB_BASE + 0x00)
#define GPIOB_CRH *(volatile uint32_t *)(GPIOB_BASE + 0x04)
#define GPIOB_ODR *(volatile uint32_t *)(GPIOB_BASE + 0x0C)
#define GPIOB_IDR *(volatile uint32_t *)(GPIOB_BASE + 0x08)
#define GPIOB13    (1UL << 13)

#define RCC_BASE 0x40021000
#define RCC_APB2ENR (*(volatile uint32_t *)(RCC_BASE + 0x18))
#define RCC_CFGR 	(*(volatile uint32_t *)(RCC_BASE + 0x04))
#define RCC_CR 		(*(volatile uint32_t *)(RCC_BASE + 0x00))
#define RCC_IOPAEN  (1 << 2)


void Clock_Init(){
	// Initialize clock for GPIOA
	RCC_APB2ENR |= RCC_IOPAEN;
	// Bit 3 IOPBEN: I/O port B clock enable
	RCC_APB2ENR |= 1 << 3;
}

void GPIO_Init(){
	GPIOA_CRL = 0x0;
	GPIOB_CRL = 0x0;

	// PA1 input high impedance
	GPIOA_CRL |= 1 << 6;
	// PB1 output push-pull mode
	// CNF 00: General purpose output push-pull
	GPIOB_CRL &= ~(0b11 << 6);
	//01: Output mode, max speed 10 MHz
	GPIOB_CRL |= (0b01 << 4);

	// PA13 input high impedance
	GPIOA_CRH &= ~(0b11 << 20);
	GPIOA_CRH |= (0b01 << 22);
	// PB13 output push-pull mode
	GPIOB_CRH |= (0b01 << 20);
	GPIOB_CRH &= ~(0b11 << 22);
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
		// PA1 connected with external PUR
		if(((GPIOA_IDR & (1<<1)) >> 1) == 0){
			GPIOB_ODR ^= 1 << 1;
			while( ((GPIOA_IDR & (1<<1)) >> 1) == 0 ); // single press
		}
		// PA1 connected with external PDR
		if(((GPIOA_IDR & (1<<13)) >> 13) == 1){
			GPIOB_ODR ^= 1 << 13;
		}
		my_wait(1);
	}
	return 0;
}


