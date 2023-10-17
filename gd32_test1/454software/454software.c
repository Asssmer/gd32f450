#include "./454software.h"
/*!
    \brief      initialize all 454
    \param[in]  none
    \param[out] none
    \retval     none
*/

void init_454(void)
{
    /* 使能时钟 */
    rcu_periph_clock_enable(RCU_TIMER6);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOG);

    rcu_ahb_clock_config(RCU_AHB_CKSYS_DIV1);
    rcu_apb1_clock_config(RCU_APB1_CKAHB_DIV1);

    /* 配置PC9为CKOUT1 */
    gpio_af_set(GPIOC, GPIO_AF_0, GPIO_PIN_9);
    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_9);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
    rcu_ckout1_config(RCU_CKOUT1SRC_SYSTEMCLOCK, RCU_CKOUT1_DIV1);

    // 配置PG6,PG7,PG8
    gpio_mode_set(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_6);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6);
    gpio_mode_set(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_7);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7);
    gpio_mode_set(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_8);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_8);

    gpio_bit_set(GPIOG, GPIO_PIN_6);
    gpio_bit_set(GPIOG, GPIO_PIN_7);
    gpio_bit_set(GPIOG, GPIO_PIN_8);

    // 配置定时器6

    /* 复位TIM6 */
    timer_deinit(RCU_TIMER6);
    /* 初始化TIM6 */
    timer_parameter_struct timer_initpara;
    timer_initpara.prescaler = 199;
    timer_initpara.alignedmode = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection = TIMER_COUNTER_UP;
    timer_initpara.period = 999; // 实现1ms的定时器
    timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
    timer_init(TIMER6, &timer_initpara);
    timer_enable(TIMER6);
}
/*!
    \brief      ms_delay
    \param[in]  ms: 16 bit,max:65535
    \param[out] none
    \retval     none
*/
void ms_delay_454(uint16_t ms)
{
    while (ms > 0)
    {
        uint32_t ticks = (SystemCoreClock / 1000 / (199 + 1)) * ms;
        if (ticks > 65535)
        {
            ticks = 65535; // Set to max possible value to avoid overflow
            ms -= 65535 / (SystemCoreClock / 1000 / (199 + 1));
        }
        else
        {
            ms = 0;
        }
        timer_autoreload_value_config(TIMER6, ticks - 1);
        timer_counter_value_config(TIMER6, 0);   // Reset counter

        timer_flag_clear(TIMER6, TIMER_FLAG_UP); // Clear any existing overflow flag
        while (RESET == timer_flag_get(TIMER6, TIMER_FLAG_UP))
            ;
        timer_flag_clear(TIMER6, TIMER_FLAG_UP); // Clear overflow flag for next iteration
    }
}

void s_delay_454(uint32_t seconds)
{
    for (uint32_t i = 0; i < seconds; i++)
    {
        ms_delay_454(1000);
    }
}
