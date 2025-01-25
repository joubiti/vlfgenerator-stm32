#include "clock.h"
#include <cstdint>
#include "stm32g0xx.h"
#include <stdbool.h>

void clock_initialize(void){
    // enable HSI clock 
    RCC->CR |= (RCC_CR_HSION);
    while(!(RCC->CR & RCC_CR_HSIRDY));

    // enable power clock
    RCC->APBENR1 |= (RCC_APBENR1_PWREN);
    // voltage scale 1
    PWR->CR1 |= PWR_CR1_VOS_0;
    // Enable CPU instruction cache and prefetch
    FLASH->ACR |= FLASH_ACR_PRFTEN;
    FLASH->ACR |= FLASH_ACR_ICEN;
    // 2 wait states for Flash latency
    FLASH->ACR |= FLASH_ACR_LATENCY_1;

    // disable PLL
    RCC->CR &= ~RCC_CR_PLLON;
    // block while PLL is locked
    while(RCC->CR & RCC_CR_PLLRDY);

    // configure PLL input clock and multiplication factor
    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLSRC);
    RCC->PLLCFGR |= (RCC_PLLCFGR_PLLSRC_HSI);
    // PLLM = x1
    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLM);
    // PLLN = x8
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;
    RCC->PLLCFGR |= (8 << RCC_PLLCFGR_PLLN_Pos);
    // PLLR = x2
    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLR);
    RCC->PLLCFGR |= (RCC_PLLCFGR_PLLR_0);
    // enable PLLRCLK output
    RCC->PLLCFGR |= (RCC_PLLCFGR_PLLREN);

    // AHB prescaler (1)
    RCC->CFGR &= ~(RCC_CFGR_HPRE);
    // APB prescaler (1)
    RCC->CFGR &= ~(RCC_CFGR_PPRE);

    // enable PLL
    RCC->CR |= (RCC_CR_PLLON);
    // block until PLL is ready
    while(!(RCC->CR & RCC_CR_PLLRDY));

    // system clock switch to PLLRCLK
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= 2 << RCC_CFGR_SW_Pos;
    while(!(RCC->CFGR & (2 << RCC_CFGR_SWS_Pos)));
}
