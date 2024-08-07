/*
 * stm32f103x6.h
 *
 *  Created on: Jul 23, 2024
 *      Author: Abdo Halem
 */

#ifndef STM32F103X6_H_
#define STM32F103X6_H_
//-----------------------------
//Includes
#include <stdlib.h>
#include <stdint.h>

//-----------------------------
//Base addresses for Memories
#define FLASH_MEMORY_BASE			0x08000000UL
#define SYSTEM_MEMORY_BASE			0x1FFFF000UL
#define SRAM_MEMORY_BASE			0x20000000UL
#define CORTEX_M3_PERIPHERALS_BASE  0xE0000000UL

//-----------------------------
//Base addresses for AHB Peripherals
#define RCC_BASE	0x40021000UL

//Base addresses for APB2 Peripherals
/* PORT A,B are fully included in LQFP48 */
#define GPIOA_BASE	0x40010800UL
#define GPIOB_BASE	0x40010C00UL
/* PORT C,D are partially fully included in LQFP48 */
#define GPIOC_BASE	0x40011000UL
#define GPIOD_BASE	0x40011400UL
/* PORT E is not included in LQFP48 */
#define GPIOE_BASE	0x40011800UL
/* EXTI Peripheral */
#define EXTI_BASE	0x40010400UL
/* AFIO Peripheral */
#define AFIO_BASE	0x40010000UL

//Base addresses for APB2 Peripherals


//-----------------------------
//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register: GPIO
typedef struct{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIO_t;

//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register: RCC
typedef struct{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t AHBSTR;
	volatile uint32_t CFGR2;
}RCC_t;

//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register: EXTI
typedef struct{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_t;

//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register: AFIO
typedef struct{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	volatile uint32_t RESERVED;		//Empty Region
	volatile uint32_t MAPR2;
}AFIO_t;

//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral Instants:
#define GPIOA			((GPIO_t *)GPIOA_BASE)
#define GPIOB			((GPIO_t *)GPIOB_BASE)
#define GPIOC			((GPIO_t *)GPIOC_BASE)
#define GPIOD			((GPIO_t *)GPIOD_BASE)
#define GPIOE			((GPIO_t *)GPIOE_BASE)

#define RCC				((RCC_t *)RCC_BASE)
#define EXTI			((EXTI_t *)EXTI_BASE)
#define AFIO			((AFIO_t *)AFIO_BASE)
//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
#define RCC_GPIOA_CLOCK_EN()	(RCC->APB2ENR |= 1<<2)
#define RCC_GPIOB_CLOCK_EN()	(RCC->APB2ENR |= 1<<3)
#define RCC_GPIOC_CLOCK_EN()	(RCC->APB2ENR |= 1<<4)
#define RCC_GPIOD_CLOCK_EN()	(RCC->APB2ENR |= 1<<5)
#define RCC_GPIOE_CLOCK_EN()	(RCC->APB2ENR |= 1<<6)

#define RCC_AFIO_CLOCK_EN()		(RCC->APB2ENR |= 1<<0)

//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:

//-*-*-*-*-*-*-*-*-*-*-*
#endif /* STM32F103X6_H_ */
