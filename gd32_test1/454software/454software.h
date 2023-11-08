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

#define MAX_STR_SIZE 12 // 最大字符串长度，考虑到32位整数最大为10位，加上符号和空字符
#define I2C0_OWN_ADDRESS7 0x72
#define I2C1_OWN_ADDRESS7 0x92

#define ZXP3010D_Address 0xDA
#define ZXP3010D_ADC_LSB 0x08
#define ZXP3010D_ADC_LCB 0x07
#define ZXP3010D_ADC_MSB 0x06
#define ZXP3010D_TEMP_LSB 0x0A
#define ZXP3010D_TEMP_MSB 0x09
#define ZXP3010D_STATUS 0x02
#define ZXP3010D_CMD 0x30
#define ZXP3010D_DRDY 0x01

#define SENSOR_I2C_ADDRESS 0xda

void init_454(void);
void RCU_init_454(void);
void NVIC_init_454(void);
void ms_delay_454(uint32_t ms);
void s_delay_454(uint32_t seconds);
int log_454(uint8_t *string);
char *intToStr(int num);
char *floatToStr(float num, int afterpoint);
void send_register_value(uintptr_t reg_address, uint8_t reg_size);

uint32_t i2c_flag_check_timeout(uint32_t i2c_periph, uint32_t flag, FlagStatus expected_Status);

uint8_t usart1_send_454(uint8_t *string, uint16_t count_size);
uint8_t usart1_receive_454(void);

uint8_t P11_Initial(void);
void P11_StartP(void);
void P11_StartT(void);
uint8_t P11_ConStatus(void);
int32_t P11_ResultP(void);
int32_t P11_ResultT(void);

void P11_Caculate(int32_t up, int32_t ut, float *rp, float *rt);

void i2c_master_receive(uint32_t i2c_periph, uint8_t *data, uint16_t length, uint16_t address);
void i2c_master_send(uint32_t i2c_periph, uint8_t *data, uint16_t length, uint16_t address);
