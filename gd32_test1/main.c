#include "./454software/454software.h"

// SystemCoreClock

int main(void)
{
    init_454();
    int32_t XX = -200000000;
    while (1)
    {
        gpio_bit_toggle(GPIOG, GPIO_PIN_7);
        ms_delay_454(1000);
        log_454("start!!");
        log_454(intToStr(XX));
    }
    return 0;
}
