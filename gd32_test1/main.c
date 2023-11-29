#include "./454software/454software.h"

// SystemCoreClock

int main(void)
{
        init_454();
        char buff[256] = {0};
        buff[0] = 0x55;

        float i2c0_fTemp = 0;
        float i2c0_fPress = 0;

        float i2c0_flow = 0;

        int16_t P7_temp = 0;

        float i2c1_fTemp = 0;
        float i2c1_fPress = 0;

        float i2c2_fTemp = 0;
        float i2c2_fPress = 0;

        uint16_t PSE540_value = 0;

        P4_PWM_set(600);
        P5_PWM_set(800);
        P6_PWM_set(800);
        YDP_control(SET);

        extern volatile uint16_t adc_values_454[ADC_CHANNEL_COUNT];
        extern volatile uint8_t MOTOR_received_frame[MOTOR_FRAME_SIZE];
        extern volatile MotorStatus motor_status;
        extern volatile pwm_capture_data_t pwm_values;


        log_454("\n start!!\n");
        // gpio_bit_toggle(GPIOG, GPIO_PIN_7);
        // send_motor_control_frame(20000);
        while (1)
        {
                // log_454(floatToStr(pwm_values.duty_cycle0, 2));



                // for (int channel = 0; channel < 6; ++channel)
                // {
                //         // adc_values[channel] = adc_regular_data_read(ADC2);
                //         log_454(floatToStr(adc_to_voltage(adc_values_454[channel]), 2));
                //         log_454("\n");
                //         ms_delay_454(500);
                // }

                // P7_temp = MAX31865_TempGet_454(SPI_P7);
                // log_454("\n P7::!!\n");
                // log_454(intToStr(P7_temp));

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

                // PWM_EN_enable(GPIO_PIN_1);

                // timer_channel_capture_value_register_read(TIMER4, TIMER_CH_1);
                // YDP_control(SET);
                // YDP_control(RESET);
                // PWM_EN_disable(GPIO_PIN_1);
                // ms_delay_454(1000);
                // break;
                gpio_bit_toggle(GPIOG, GPIO_PIN_6);
                ms_delay_454(1000);
                log_454("\n end!!\n");
        }
        return 0;
}
