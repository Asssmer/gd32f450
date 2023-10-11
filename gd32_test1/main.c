#include "gd32f4xx.h"

#define LED_PIN_BIT   (1 << 6)  // PG6

int main(void) {
    // ʹ��GPIOGʱ��
    RCU_AHB1EN |= RCU_AHB1EN_GPIOGEN;

    // ����PG6Ϊ�������ģʽ
    GPIOG_CTL &= ~GPIO_CTL_MD6;          // ���ģʽλ
    GPIOG_CTL |= (0x01 << GPIO_CTL_MD6_Pos); // ����Ϊ�������ģʽ

    // ����LED
    GPIOG_BOP = LED_PIN_BIT;

    while(1) {
        // ��ѭ��������LED����״̬��
    }

    return 0;
}
