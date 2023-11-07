#include "./454software/454software.h"

// SystemCoreClock

int main(void)
{
int32_t press;
int32_t temp=0;
float fTemp=0;
float fPress;




    uint8_t buff = 0x55;


    uint8_t P11ConStatus = 0;
    int32_t P11ResultP = 0;

    init_454();
    int32_t XX = -200000000;
    while (1)
    {
        gpio_bit_toggle(GPIOG, GPIO_PIN_7);
        log_454("\nstart!!\n");

        P11_Initial();
        P11_StartP();
        ms_delay_454(12);
        do
        {
            ms_delay_454(1);
        } while (P11_ConStatus());
        press = P11_ResultP();
        log_454(intToStr(press));
        P11_Caculate(press, temp, &fPress, &fTemp);

        log_454("\n fPress:");
        // usart1_send_454(&fPress, sizeof(fPress));
        log_454(intToStr(fPress));

        ms_delay_454(500);

    }
    return 0;
}
