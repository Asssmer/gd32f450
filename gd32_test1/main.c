#include "./454software/454software.h"

// SystemCoreClock

#define SPI_P7 GPIO_PIN_15
#define SPI_P9 GPIO_PIN_12

int main(void)
{
        init_454();

        float i2c0_fTemp = 0;
        float i2c0_fPress = 0;

        float i2c0_flow = 0;

        int16_t P7_temp = 0;

        float i2c1_fTemp = 0;
        float i2c1_fPress = 0;

        float i2c2_fTemp = 0;
        float i2c2_fPress = 0;

        uint16_t PSE540_value = 0;

        while (1)
        {
                gpio_bit_toggle(GPIOG, GPIO_PIN_7);
                log_454("\n start!!\n");

                uint16_t PSE540_value = PSE540_value_read();
                log_454("\n PSE540_value::");
                log_454(floatToStr(adc_to_voltage(PSE540_value), 2));

                P7_temp = MAX31865_TempGet_454(SPI_P7);
                log_454("\n P7::!!\n");
                log_454(intToStr(P7_temp));

                // P7_temp = MAX31865_TempGet(SPI_P9);
                // log_454("\n P9::");
                // log_454(intToStr(P7_temp));
                // I2C_Scan(I2C0);

#ifdef BOARD_VER_2
                ZXP8_get_data_454(I2C0, &i2c0_fTemp, &i2c0_fPress);
                ZXP8_get_data_454(I2C1, &i2c1_fTemp, &i2c1_fPress);
                ZXP2_get_data_454(I2C2, &i2c2_fTemp, &i2c2_fPress);
                // FS4301_get_data_454(I2C0, &i2c0_flow);
#endif

#ifdef BOARD_VER_1
                ZXP8_get_data_454(I2C0, &i2c0_fTemp, &i2c0_fPress);
                ZXP2_get_data_454(I2C1, &i2c1_fTemp, &i2c1_fPress);
                ZXP8_get_data_454(I2C2, &i2c2_fTemp, &i2c2_fPress);
#endif

                ms_delay_454(1000);
        }
        return 0;
}
