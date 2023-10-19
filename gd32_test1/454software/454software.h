#define GD32F450

#include <stdint.h>
#include <stdio.h>
#include "gd32f4xx.h"
#include "gd32f4xx_rcu.h"
#include "gd32f4xx_gpio.h"
#include "gd32f4xx_timer.h"
#include "gd32f4xx_misc.h"
#include "gd32f4xx_usart.h"


void init_454(void);
void ms_delay_454(uint32_t ms);
void s_delay_454(uint32_t seconds);
int log(uint8_t *string);
void usart1_send(uint8_t data);
uint8_t usart1_receive(void);