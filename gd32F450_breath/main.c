#include "./454software/454software.h"

// SystemCoreClock


int main(void)
{
        init_454();
        extern volatile uint8_t MOTOR_received_frame[MOTOR_FRAME_SIZE];
        extern volatile MotorStatus motor_status;
        motor_control(0);

        uint8_t data;
        uint16_t motor_control_data;
        char input_line[100];
        while (1)
        {
                if (scanf("%hu", &motor_control_data) == 1)
                {
                        motor_control(motor_control_data);
                        gpio_bit_toggle(GPIOG, GPIO_PIN_6);
                }
                else
                {
                }
        }
        // delay_ms_454(1000);
        return 0;
}