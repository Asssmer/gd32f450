#include "./454software/454software.h"

// SystemCoreClock

// 80 30 01 31
// 80 00 00 00
// 4000 80 a0 0f AF
// 6000 80 70 17 87
// 7000 80 58 1b
// 8000 80 40 1f 5f
int main(void)
{
        init_454();
        extern volatile uint8_t MOTOR_received_frame[MOTOR_FRAME_SIZE];
        extern volatile MotorStatus motor_status;
        send_motor_control_frame(0);
        // send_motor_control_frame(0);

        uint8_t data;
        uint16_t motor_control_data;
        char input_line[100];
        while (1)
        {
                if (scanf("%hu", &motor_control_data) == 1)
                {
                        send_motor_control_frame(motor_control_data);
                        gpio_bit_toggle(GPIOG, GPIO_PIN_6);
                }
                else
                {
                }
        }
        // ms_delay_454(1000);
        return 0;
}