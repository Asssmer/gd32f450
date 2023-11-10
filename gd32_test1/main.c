#include "./454software/454software.h"

// SystemCoreClock

int main(void)
{
    init_454();

    float i2c0_fTemp = 0;
    float i2c0_fPress=0;

    float i2c1_fTemp = 0;
    float i2c1_fPress=0;

    float i2c2_fTemp = 0;
    float i2c2_fPress=0;

    while (1)
    {
        gpio_bit_toggle(GPIOG, GPIO_PIN_7);
        log_454("\n start!!\n");
        
        #ifdef BOARD_VER_2
        ZXP8_get_data_454(I2C0,&i2c0_fTemp,&i2c0_fPress);
        // ZXP8_get_data_454(I2C1,&i2c1_fTemp,&i2c1_fPress);
        // ZXP2_get_data_454(I2C2,&i2c2_fTemp,&i2c2_fPress);
        #endif

        #ifdef BOARD_VER_1
        ZXP8_get_data_454(I2C0,&i2c0_fTemp,&i2c0_fPress);
        ZXP2_get_data_454(I2C1,&i2c1_fTemp,&i2c1_fPress);
        ZXP8_get_data_454(I2C2,&i2c2_fTemp,&i2c2_fPress);
        #endif

        // log_454("\n fTemp:");
        // log_454(floatToStr(fTemp, 2));
        // log_454("\n fPress:");
        // log_454(floatToStr(fPress, 2));

        ms_delay_454(1000);
    }
    return 0;
}
