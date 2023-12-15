#include "./454software/454software.h"

// SystemCoreClock
#define FRAME_START 0x90

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
        // send_motor_control_frame(300);
        send_motor_control_frame(0);

        uint8_t data;
        uint16_t motor_control_data;
        uint8_t data_count = 0;
        log_454("\n start!!\n");

        while (1)
        {
                if (usart_flag_get(USART0, USART_FLAG_RBNE))
                {
                        // ��ȡһ���ֽ�
                        data = usart_data_receive(USART0);

                        // �������ֽ���ϳ�һ�� 16 λ��
                        if (data_count == 0)
                        {
                                motor_control_data = (uint16_t)data; // ��λ
                                data_count = 1;
                        }
                        else
                        {
                                motor_control_data |= (uint16_t)data << 8;    // ��λ
                                send_motor_control_frame(motor_control_data); // ���Ϳ��Ƶ����һ֡
                                data_count = 0;
                        }
                }
                gpio_bit_toggle(GPIOG, GPIO_PIN_6);

                ms_delay_454(1000);
        }

        // log_454("\n start!!\n");
        // while (1)
        // {

        //         // FS4301_get_data_454(I2C0, &i2c0_flow);
        //         // log_454("\n");

        //         // log_454(floatToStr(i2c0_flow, 2));

        //         // printf("a usart transmit test example!");
        //         gpio_bit_toggle(GPIOG, GPIO_PIN_6);

        //         ms_delay_454(1000);
        // }
        log_454("\n end!!\n");
        return 0;
}