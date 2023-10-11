#include "gd32f4xx.h"

#define LED_PIN_BIT   (1 << 6)  // PG6

int main(void) {
    // 使能GPIOG时钟
    RCU_AHB1EN |= RCU_AHB1EN_GPIOGEN;

    // 设置PG6为推挽输出模式
    GPIOG_CTL &= ~GPIO_CTL_MD6;          // 清除模式位
    GPIOG_CTL |= (0x01 << GPIO_CTL_MD6_Pos); // 设置为推挽输出模式

    // 点亮LED
    GPIOG_BOP = LED_PIN_BIT;

    while(1) {
        // 主循环（保持LED点亮状态）
    }

    return 0;
}
