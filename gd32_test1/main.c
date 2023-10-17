#include "./454software/454software.h"

// SystemCoreClock

int main(void)
{
    init_454();

    while (1)
    {
        gpio_bit_toggle(GPIOG, GPIO_PIN_6);
        ms_delay_454(1);
    }
    return 0;
}
