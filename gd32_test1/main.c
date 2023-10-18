#include "./454software/454software.h"

// SystemCoreClock

int main(void)
{
    init_454();

    while (1)
    {
        gpio_bit_toggle(GPIOG, GPIO_PIN_7);
        ms_delay_454(1000);
        usart1_send(0x55);
    }
    return 0;
}
