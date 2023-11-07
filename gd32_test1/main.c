#include "./454software/454software.h"

// SystemCoreClock

int main(void)
{

    uint8_t buff = 0x55;

    uint8_t P11ConStatus = 0;
    int32_t P11ResultP = 0;

    init_454();
    int32_t XX = -200000000;
    while (1)
    {
        gpio_bit_toggle(GPIOG, GPIO_PIN_7);
        log_454("start!!\n");

        //  i2c_master_send(I2C0, I2C1_OWN_ADDRESS7, 1, I2C1_OWN_ADDRESS7);

        P11_Initial();
        P11_StartP();
        P11ConStatus=P11_ConStatus();
        P11ResultP=P11_ResultP();
        log_454("\n P11ConStatus:");
        usart1_send_454(&P11ConStatus, sizeof(P11ConStatus));
        log_454("\n P11ConStatus:");
        usart1_send_454(&P11ConStatus, sizeof(P11ConStatus));

        ms_delay_454(500);

        // log_454(intToStr(XX));
    }
    return 0;
}
