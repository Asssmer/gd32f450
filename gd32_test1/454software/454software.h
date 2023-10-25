#define GD32F450

#include <stdint.h>
#include <stdio.h>
#include "gd32f4xx.h"
#include "gd32f4xx_rcu.h"
#include "gd32f4xx_gpio.h"
#include "gd32f4xx_timer.h"
#include "gd32f4xx_misc.h"
#include "gd32f4xx_dma.h"
#include "gd32f4xx_usart.h"
#include "gd32f4xx_i2c.h"
#include "gd32f4xx_exti.h"

#define MAX_STR_SIZE 12  // 最大字符串长度，考虑到32位整数最大为10位，加上符号和空字符
#define SENSOR_I2C_ADDRESS   0x76  // Replace with your sensor's I2C address



void init_454(void);
void ms_delay_454(uint32_t ms);
void s_delay_454(uint32_t seconds);
int log_454(uint8_t *string);
char *intToStr(int num);
uint8_t usart1_send(uint8_t *string, uint16_t count_size);
uint8_t usart1_receive(void);

uint8_t read_pressure_P10_454(uint8_t register_address);
