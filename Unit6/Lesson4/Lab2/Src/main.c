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
#define GPIOA13    (1UL << 13)

#define RCC_BASE 0x40021000
#define RCC_APB2ENR (*(volatile uint32_t *)(RCC_BASE + 0x18))
#define RCC_CFGR 	(*(volatile uint32_t *)(RCC_BASE + 0x04))
#define RCC_CR 		(*(volatile uint32_t *)(RCC_BASE + 0x00))
#define RCC_IOPAEN  (1 << 2)

#define EXTI_BASE 0x40010400
#define EXTI_IMR 	(*(volatile uint32_t *)(EXTI_BASE + 0x00))
#define EXTI_RTSR 	(*(volatile uint32_t *)(EXTI_BASE + 0x08))
#define EXTI_PR 	(*(volatile uint32_t *)(EXTI_BASE + 0x14))

#define AFIO_BASE 0x40010000
#define AFIO_EXTICR1 (*(volatile uint32_t *)(AFIO_BASE + 0x08))

#define NVIC_EXTIE0 (*(volatile uint32_t *)(0xE000E100 + 0x00))

void Clock_Init(){
	// Initialize clock for GPIOA
	RCC_APB2ENR |= RCC_IOPAEN;
	// Bit 0 AFIOEN: Alternate function I/O clock enable
	RCC_APB2ENR |= 1 << 0;
}

void GPIO_Init(){
	// Initialize GPIOA pin13 to be input
	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x00200000;
	// GPIOA Pin 0 input floating 01: Floating input (reset state)
	GPIOA_CRL |= 1 << 2;
}

int main(void)
{
	Clock_Init();
	GPIO_Init();
	// EXTI0 x configuration (x = 0) to PORTA pin 0
	AFIO_EXTICR1 = 0;
	// Configure Rising Trigger
	EXTI_RTSR |= 1 << 0;
	// Enable EXTI Line 0 (Mask 1)
	EXTI_IMR |= 1 << 0;
	// Enable NVIC IRQ6
	NVIC_EXTIE0 |= 1 << 6;

	while(1)
	{

	}
	return 0;
}

void EXTI0_IRQHandler(){
	// IRQ is happened EXTI0 >> PORTA Pin0 at rising edge
	// Toggle LED GPIOA pin13
	GPIOA_ODR ^= (1 << 13);
	// Clear Pending Request for line 0
	EXTI_PR |= 1 << 0;

}

