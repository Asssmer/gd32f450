#include "./454software/454software.h"

// SystemCoreClock

int main(void)
{
        init_454();
        // 电机
        extern volatile MotorStatus motor_status;
        // ADC
        extern volatile uint16_t adc_values_454[ADC_CHANNEL_COUNT];
        extern volatile SensorData sensor_data;
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
        // LED1(ON);
        LED2(ON);
        // LED3(ON);

        P4_PWM_set(500);
        P5_PWM_set(500);
        P6_PWM_set(500);

        uint8_t data;
        uint16_t motor_control_data;
        printf("Start!\n");
        while (1)
        {
                // if (scanf("%hu", &motor_control_data) == 1)
                // {
                //         motor_control(motor_control_data);
                //         printf("Set motor speed:%hu\n",motor_control_data);
                //         gpio_bit_toggle(GPIOG, GPIO_PIN_6);
                // }
                // else
                // {
                // }
                // temperature_P7 = P7_get();
                // pressure_P10 = P10_get();
                // pressure_P11 = P11_get();
                // // pressure_P12 = P13_get();
                // flow_P13 = P13_get();
                // flow_P14 = P14_get();
                // // flow_P15 = P15_get();
                // gpio_bit_toggle(GPIOG, GPIO_PIN_6);
                delay_ms_454(1000);

                printf("ADC0:%f\n",adc_to_voltage(adc_values_454[0]));
                printf("ADC1:%f\n",adc_to_voltage(adc_values_454[1]));
                printf("ADC2:%f\n",adc_to_voltage(adc_values_454[2]));
                printf("ADC3:%f\n",adc_to_voltage(adc_values_454[3]));
                printf("ADC4:%f\n",adc_to_voltage(adc_values_454[4]));
                printf("ADC5:%f\n\n\n",adc_to_voltage(adc_values_454[5]));

        }
        return 0;
}