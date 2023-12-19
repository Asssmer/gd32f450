#include "./454software/454software.h"

// SystemCoreClock

int main(void)
{
        init_454();
        // 电机
        extern volatile MotorStatus motor_status;
        // ADC
        extern volatile uint16_t adc_values_454[ADC_CHANNEL_COUNT];
        // 温度
        int16_t temperature_P7;
        int16_t temperature_P9;
        // 压力
        float pressure_P10;
        float pressure_P11;
        float pressure_P12;
        // 流量
        float flow_P13;
        float flow_P14;
        float flow_P15;

        // motor_control(0);
        LED1(ON);
        LED2(ON);
        LED3(ON);

        uint8_t data;
        uint16_t motor_control_data;
        printf("Start!/n");
        while (1)
        {
                // if (scanf("%hu", &motor_control_data) == 1)
                // {
                //         motor_control(motor_control_data);
                //         gpio_bit_toggle(GPIOG, GPIO_PIN_6);
                // }
                // else
                // {
                // }
                temperature_P7 = P7_get();
                pressure_P10 = P10_get();
                pressure_P11 = P11_get();
                // pressure_P12 = P13_get();
                flow_P13 = P13_get();
                flow_P14 = P14_get();
                // flow_P15 = P15_get();
                gpio_bit_toggle(GPIOG, GPIO_PIN_6);
                delay_ms_454(1000);
        }
        return 0;
}