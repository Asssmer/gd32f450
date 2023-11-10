#include "./454software.h"

/*!
    initialize all 454
*/
char strOutput_454[MAX_STR_SIZE]; // 存储转换后的字符串

void init_454(void)
{
    RCU_init_454();
    NVIC_init_454();
    I2C_init_454();
    LED_init_454();
    TIMER_init_454();
    USART0_init_454();
    USART1_init_454();

    /* 配置PC9为CKOUT1 */
    // gpio_af_set(GPIOC, GPIO_AF_0, GPIO_PIN_9);
    // gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_9);
    // gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
    // rcu_ckout1_config(RCU_CKOUT1SRC_SYSTEMCLOCK, RCU_CKOUT1_DIV1);

    // 配置PE0,PE1,PE2
    // gpio_mode_set(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_0);
    // gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0);
    // gpio_mode_set(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_1);
    // gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_1);
    // gpio_mode_set(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_2);
    // gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);

    // gpio_bit_set(GPIOE, GPIO_PIN_0);
    // gpio_bit_set(GPIOE, GPIO_PIN_1);
    // gpio_bit_set(GPIOE, GPIO_PIN_2);

    // 配置PA6,PC6,PD12
    // gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_6);
    // gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6);

    // gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_6);
    // gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6);

    // gpio_mode_set(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_12);
    // gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12);

    // gpio_bit_set(GPIOA, GPIO_PIN_6);
    // gpio_bit_set(GPIOC, GPIO_PIN_6);
    // gpio_bit_set(GPIOD, GPIO_PIN_12);
}

void RCU_init_454(void)
{
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOD);
    rcu_periph_clock_enable(RCU_GPIOE);
    rcu_periph_clock_enable(RCU_GPIOF);
    rcu_periph_clock_enable(RCU_GPIOG);

    rcu_periph_clock_enable(RCU_TIMER6);
    rcu_periph_clock_enable(RCU_USART0);
    rcu_periph_clock_enable(RCU_USART1);
    rcu_periph_clock_enable(RCU_DMA0);
    rcu_periph_clock_enable(RCU_DMA1);
    rcu_periph_clock_enable(RCU_I2C0);
    rcu_periph_clock_enable(RCU_I2C1);
    rcu_periph_clock_enable(RCU_I2C2);

    rcu_ahb_clock_config(RCU_AHB_CKSYS_DIV1);
    rcu_apb1_clock_config(RCU_APB1_CKAHB_DIV1);
}

void NVIC_init_454(void)
{
    nvic_priority_group_set(NVIC_PRIGROUP_PRE1_SUB3);
    // 数字越小，优先级越高
    nvic_irq_enable(DMA0_Channel6_IRQn, 0, 7);
    nvic_irq_enable(DMA1_Channel7_IRQn, 0, 6);

    // nvic_irq_enable(I2C0_EV_IRQn, 0, 3);
    // nvic_irq_enable(I2C1_EV_IRQn, 0, 4);
    // nvic_irq_enable(I2C0_ER_IRQn, 0, 2);
    // nvic_irq_enable(I2C1_ER_IRQn, 0, 1);
}

void LED_init_454(void)
{
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
}

void TIMER_init_454(void)
{
    /* Configure TIMER6 */
    timer_deinit(RCU_TIMER6);
    timer_parameter_struct timer_initpara;
    timer_initpara.prescaler = 199;
    timer_initpara.alignedmode = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection = TIMER_COUNTER_UP;
    timer_initpara.period = 999; // 实现1ms的定时器
    timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
    timer_init(TIMER6, &timer_initpara);
    timer_enable(TIMER6);
}

void USART1_init_454(void)
{

    /* Configure USART1 */
    usart_deinit(USART1);
    usart_disable(USART1);
    usart_word_length_set(USART1, USART_WL_8BIT);
    usart_stop_bit_set(USART1, USART_STB_1BIT);
    usart_baudrate_set(USART1, 115200U);
    usart_parity_config(USART1, USART_PM_NONE);

    usart_hardware_flow_rts_config(USART1, USART_RTS_DISABLE);
    usart_hardware_flow_cts_config(USART1, USART_CTS_DISABLE);
    usart_receive_config(USART1, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART1, USART_TRANSMIT_ENABLE);
    usart_dma_receive_config(USART1, USART_DENR_ENABLE);
    usart_dma_transmit_config(USART1, USART_DENT_ENABLE);

    /* Configure USART1 DMA */
    dma_deinit(DMA0, DMA_CH6);
    dma_multi_data_parameter_struct dma_init_struct;
    dma_multi_data_para_struct_init(&dma_init_struct);
    dma_init_struct.periph_addr = (uint32_t)&USART_DATA(USART1);
    dma_init_struct.periph_width = DMA_PERIPH_WIDTH_8BIT;
    dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.memory_width = DMA_MEMORY_WIDTH_8BIT;
    dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_struct.direction = DMA_MEMORY_TO_PERIPH;
    dma_init_struct.priority = DMA_PRIORITY_LOW;
    dma_multi_data_mode_init(DMA0, DMA_CH6, &dma_init_struct);
    dma_channel_subperipheral_select(DMA0, DMA_CH6, DMA_SUBPERI4);
    dma_interrupt_enable(DMA0, DMA_CH6, DMA_CHXCTL_FTFIE);

    // Configure USART1 TX (PD5) as alternate function push-pull
    gpio_af_set(GPIOD, GPIO_AF_7, GPIO_PIN_5);
    gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_5);
    gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5);

    // Configure USART1 RX (PD6) as floating input
    gpio_af_set(GPIOD, GPIO_AF_7, GPIO_PIN_6);
    gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_6);
    gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6);

    usart_prescaler_config(USART1, 1U);
    usart_enable(USART1);
}

void USART0_init_454(void)
{
    /* Configure USART1 */
    usart_deinit(USART0);
    usart_disable(USART0);
    usart_word_length_set(USART0, USART_WL_8BIT);
    usart_stop_bit_set(USART0, USART_STB_1BIT);
    usart_baudrate_set(USART0, 115200U);
    usart_parity_config(USART0, USART_PM_NONE);

    usart_hardware_flow_rts_config(USART0, USART_RTS_DISABLE);
    usart_hardware_flow_cts_config(USART0, USART_CTS_DISABLE);
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
    usart_dma_receive_config(USART0, USART_DENR_ENABLE);
    usart_dma_transmit_config(USART0, USART_DENT_ENABLE);

    /* Configure USART1 TX DMA */
    dma_deinit(DMA1, DMA_CH7);
    dma_multi_data_parameter_struct dma_init_struct;
    dma_multi_data_para_struct_init(&dma_init_struct);
    dma_init_struct.periph_addr = (uint32_t)&USART_DATA(USART0);
    dma_init_struct.periph_width = DMA_PERIPH_WIDTH_8BIT;
    dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.memory_width = DMA_MEMORY_WIDTH_8BIT;
    dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_struct.direction = DMA_MEMORY_TO_PERIPH;
    dma_init_struct.priority = DMA_PRIORITY_LOW;
    dma_multi_data_mode_init(DMA1, DMA_CH7, &dma_init_struct);
    dma_channel_subperipheral_select(DMA1, DMA_CH7, DMA_SUBPERI4);
    dma_interrupt_enable(DMA1, DMA_CH7, DMA_CHXCTL_FTFIE);

    // Configure USART1 TX (PA9) as alternate function push-pull
    gpio_af_set(GPIOA, GPIO_AF_7, GPIO_PIN_9);
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_9);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);

    // Configure USART1 RX (PA10) as floating input
    gpio_af_set(GPIOA, GPIO_AF_7, GPIO_PIN_10);
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_10);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

    usart_prescaler_config(USART0, 1U);
    usart_enable(USART0);
}

void I2C_init_454(void)
{
#ifdef BOARD_VER_1
    /* Configure I2C0 P10 PB6 PB7*/
    gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_9); // I2C0_SDA
    gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_8); // I2C0_SCL

    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_8);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_8);

    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_9);

    i2c_deinit(I2C0);
    i2c_clock_config(I2C0, 400000, I2C_DTCY_2);
    i2c_mode_addr_config(I2C0, I2C_I2CMODE_ENABLE, I2C_ADDFORMAT_7BITS, I2C0_OWN_ADDRESS7);
    i2c_enable(I2C0);
    i2c_ack_config(I2C0, I2C_ACK_ENABLE);

    /* Configure I2C1 P11 PB10 PB11 */
    gpio_af_set(GPIOF, GPIO_AF_4, GPIO_PIN_0); // I2C1_SDA
    gpio_af_set(GPIOF, GPIO_AF_4, GPIO_PIN_1); // I2C1_SCL

    gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_0);
    gpio_output_options_set(GPIOF, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_0);

    gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_1);
    gpio_output_options_set(GPIOF, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_1);

    i2c_deinit(I2C1);
    i2c_clock_config(I2C1, 400000, I2C_DTCY_2);
    // i2c_interrupt_enable(I2C1,I2C_INT_EV);
    i2c_mode_addr_config(I2C1, I2C_I2CMODE_ENABLE, I2C_ADDFORMAT_7BITS, I2C1_OWN_ADDRESS7);
    i2c_enable(I2C1);
    i2c_ack_config(I2C1, I2C_ACK_ENABLE);

    /* Configure I2C2 PA8 PC9 */
    gpio_af_set(GPIOC, GPIO_AF_4, GPIO_PIN_9); // I2C1_SDA
    gpio_af_set(GPIOA, GPIO_AF_4, GPIO_PIN_8); // I2C1_SCL

    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_9);

    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_8);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_8);

    i2c_deinit(I2C2);
    i2c_clock_config(I2C2, 400000, I2C_DTCY_2);
    // i2c_interrupt_enable(I2C1,I2C_INT_EV);
    i2c_mode_addr_config(I2C2, I2C_I2CMODE_ENABLE, I2C_ADDFORMAT_7BITS, I2C1_OWN_ADDRESS7);
    i2c_enable(I2C2);
    i2c_ack_config(I2C2, I2C_ACK_ENABLE);
#endif

#ifdef BOARD_VER_2
    /* Configure I2C0 P10 PB6 PB7*/
    gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_7); // I2C0_SDA
    gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_6); // I2C0_SCL

    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_6);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_6);

    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_7);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_7);

    i2c_deinit(I2C0);
    i2c_clock_config(I2C0, 400000, I2C_DTCY_2);
    i2c_mode_addr_config(I2C0, I2C_I2CMODE_ENABLE, I2C_ADDFORMAT_7BITS, I2C0_OWN_ADDRESS7);
    i2c_enable(I2C0);
    i2c_ack_config(I2C0, I2C_ACK_ENABLE);

    /* Configure I2C1 P11 PB10 PB11 */
    gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_11); // I2C1_SDA
    gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_10); // I2C1_SCL

    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_11);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_11);

    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

    i2c_deinit(I2C1);
    i2c_clock_config(I2C1, 400000, I2C_DTCY_2);
    // i2c_interrupt_enable(I2C1,I2C_INT_EV);
    i2c_mode_addr_config(I2C1, I2C_I2CMODE_ENABLE, I2C_ADDFORMAT_7BITS, I2C1_OWN_ADDRESS7);
    i2c_enable(I2C1);
    i2c_ack_config(I2C1, I2C_ACK_ENABLE);

    /* Configure I2C2 PA8 PC9 */
    gpio_af_set(GPIOC, GPIO_AF_4, GPIO_PIN_9); // I2C1_SDA
    gpio_af_set(GPIOA, GPIO_AF_4, GPIO_PIN_8); // I2C1_SCL

    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_9);

    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_8);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_8);

    i2c_deinit(I2C2);
    i2c_clock_config(I2C2, 400000, I2C_DTCY_2);
    // i2c_interrupt_enable(I2C1,I2C_INT_EV);
    i2c_mode_addr_config(I2C2, I2C_I2CMODE_ENABLE, I2C_ADDFORMAT_7BITS, I2C1_OWN_ADDRESS7);
    i2c_enable(I2C2);
    i2c_ack_config(I2C2, I2C_ACK_ENABLE);
#endif
}

/*!
    \brief      ms_delay
    \param[in]  ms: 16 bit
    \param[out] none
    \retval     none
*/
void ms_delay_454(uint32_t ms)
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

#ifdef BOARD_VER_2
int log_454(uint8_t *string)
{
    uint8_t *start = string;
    uint16_t count_size = 0;
    while (*start++)
    {
        count_size++;
        if (count_size > 1024)
        {
            log_454("string is too long!");
            return -1;
        }
    }
    usart0_send_454(string, count_size);

    return 0;
}
#endif

#ifdef BOARD_VER_1
int log_454(uint8_t *string)
{
    uint8_t *start = string;
    uint16_t count_size = 0;
    while (*start++)
    {
        count_size++;
        if (count_size > 1024)
        {
            log_454("string is too long!");
            return -1;
        }
    }
    usart1_send_454(string, count_size);

    return 0;
}
#endif

uint8_t usart0_send_454(uint8_t *string, uint16_t count_size)
{
    while (DMA_CHCTL(DMA1, DMA_CH7) & DMA_CHXCTL_CHEN)
    {
    }
    while (RESET == usart_flag_get(USART0, USART_FLAG_TC))
    {
    }
    dma_memory_address_config(DMA1, DMA_CH7, DMA_MEMORY_0, string);
    dma_transfer_number_config(DMA1, DMA_CH7, count_size);
    dma_channel_enable(DMA1, DMA_CH7);
    return 0;
}
uint8_t usart0_receive_454(void)
{
    while (usart_flag_get(USART1, USART_FLAG_RBNE) == RESET)
        ;
    return usart_data_receive(USART1);
}

uint8_t usart1_send_454(uint8_t *string, uint16_t count_size)
{
    while (DMA_CHCTL(DMA0, DMA_CH6) & DMA_CHXCTL_CHEN)
    {
    }
    while (RESET == usart_flag_get(USART1, USART_FLAG_TC))
    {
    }
    dma_memory_address_config(DMA0, DMA_CH6, DMA_MEMORY_0, string);
    dma_transfer_number_config(DMA0, DMA_CH6, count_size);
    dma_channel_enable(DMA0, DMA_CH6);
    return 0;
}
uint8_t usart1_receive_454(void)
{
    while (usart_flag_get(USART1, USART_FLAG_RBNE) == RESET)
        ;
    return usart_data_receive(USART1);
}

char *intToStr(int num)
{
    char *start = strOutput_454;
    char *end = strOutput_454;
    uint16_t remaining = MAX_STR_SIZE;

    if (num < 0)
    {
        if (remaining <= 1)
        {
            *strOutput_454 = '\0';
            return NULL;
        }
        *end++ = '-';
        remaining--;
        num = -num;
    }

    // Convert number to string (in reverse)
    do
    {
        if (remaining == 0)
        {
            *start = '\0';
            return NULL;
        }
        *end++ = '0' + (num % 10);
        num /= 10;
        remaining--;
    } while (num > 0);

    *end = '\0'; // Null-terminate

    // Reverse the string
    char *revStart = start + (*start == '-' ? 1 : 0); // Skip the negative sign if it exists
    char *revEnd = end - 1;                           // Set the end pointer just before the null terminator
    char temp;
    while (revStart < revEnd)
    {
        temp = *revStart;
        *revStart++ = *revEnd;
        *revEnd-- = temp;
    }

    return start;
}

char *floatToStr(float num, int afterpoint)
{
    // Check buffer size
    if (afterpoint >= MAX_STR_SIZE - 1)
    {
        strOutput_454[0] = '\0'; // Not enough space for the number
        return NULL;
    }

    char *start = strOutput_454;
    char *end = strOutput_454;
    int isNegative = 0;

    if (num < 0)
    {
        isNegative = 1;
        num = -num;
        *end++ = '-';
    }

    // Handle integer part
    int intPart = (int)num;
    float floatPart = num - (float)intPart;

    // Convert integer part to string
    do
    {
        *end++ = '0' + (intPart % 10);
        intPart /= 10;
    } while (intPart > 0);

    // Reverse integer part string (excluding negative sign, if any)
    char *revStart = isNegative ? start + 1 : start;
    char *revEnd = end - 1;
    char temp;
    while (revStart < revEnd)
    {
        temp = *revStart;
        *revStart = *revEnd;
        *revEnd = temp;
        revStart++;
        revEnd--;
    }

    // Handle decimal part
    if (afterpoint > 0)
    {
        *end++ = '.'; // add decimal point

        // Convert decimal part to string
        while (afterpoint-- > 0)
        {
            floatPart *= 10;
            int digit = (int)floatPart;
            *end++ = '0' + digit;
            floatPart -= (float)digit;
        }
    }

    *end = '\0'; // Null-terminate

    return start;
}

void mark________________(int LINE)
{
    log_454("\n");
    log_454(intToStr(LINE));
    log_454("\n");
}

void send_register_value(uintptr_t reg_address, uint8_t reg_size)
{
    switch (reg_size)
    {
    case 8:
    {
        uint8_t reg_value = *((volatile uint8_t *)reg_address);
        usart1_send_454(&reg_value, sizeof(reg_value));
        break;
    }
    case 16:
    {
        uint16_t reg_value = *((volatile uint16_t *)reg_address);
        usart1_send_454((uint8_t *)&reg_value, sizeof(reg_value));
        break;
    }
    case 32:
    {
        uint32_t reg_value = *((volatile uint32_t *)reg_address);
        usart1_send_454((uint8_t *)&reg_value, sizeof(reg_value));
        break;
    }
    default:
        break;
    }
}

uint32_t i2c_flag_check_timeout(uint32_t i2c_periph, i2c_flag_enum flag, FlagStatus expected_Status)
{
    uint32_t timeout = 0xFFFF;
    while (i2c_flag_get(i2c_periph, flag) != expected_Status)
    {
        if (timeout == 0)
        {
            return 1; // Timeout
        }
        timeout--;
    }
    return 0; // Success
}

int i2c_master_receive(uint32_t i2c_periph, uint8_t *data, uint16_t length, uint16_t address)
{
    if (length == 2)
    {
        // 软件应该在START置1之前将POAP置1
        i2c_ackpos_config(i2c_periph, I2C_ACKPOS_NEXT);
    }
    while (i2c_flag_get(i2c_periph, I2C_FLAG_I2CBSY))
        ;
    i2c_start_on_bus(i2c_periph);
    while (!i2c_flag_get(i2c_periph, I2C_FLAG_SBSEND))
        ;
    i2c_master_addressing(i2c_periph, address, I2C_RECEIVER);
    while (!i2c_flag_get(i2c_periph, I2C_FLAG_ADDSEND))
        ;

    if (length == 1)
    {
        i2c_ack_config(i2c_periph, I2C_ACK_DISABLE);
        i2c_flag_clear(i2c_periph, I2C_FLAG_ADDSEND);
        i2c_stop_on_bus(i2c_periph);
        while (!i2c_flag_get(i2c_periph, I2C_FLAG_RBNE))
            ;
        *data = i2c_data_receive(i2c_periph);
        while (I2C_CTL0(i2c_periph) & I2C_CTL0_STOP)
            ;
        i2c_ack_config(i2c_periph, I2C_ACK_ENABLE);
        return 0;
    }
    else if (length == 2)
    {
        i2c_ack_config(i2c_periph, I2C_ACK_DISABLE);
        i2c_flag_clear(i2c_periph, I2C_FLAG_ADDSEND);

        while (!i2c_flag_get(i2c_periph, I2C_FLAG_BTC))
            ;
        while (!i2c_flag_get(i2c_periph, I2C_FLAG_RBNE))
            ;
        *data++ = i2c_data_receive(i2c_periph);
        while (!i2c_flag_get(i2c_periph, I2C_FLAG_RBNE))
            ;
        *data = i2c_data_receive(i2c_periph);
        i2c_stop_on_bus(i2c_periph);
        while (I2C_CTL0(i2c_periph) & I2C_CTL0_STOP)
            ;
        i2c_ackpos_config(i2c_periph, I2C_ACKPOS_CURRENT);
        i2c_ack_config(i2c_periph, I2C_ACK_ENABLE);
        return 0;
    }
    else if (length > 2)
    {
        i2c_flag_clear(i2c_periph, I2C_FLAG_ADDSEND);
        // 接收N-3字节
        while (length > 3)
        {
            while (!i2c_flag_get(i2c_periph, I2C_FLAG_RBNE))
                ;
            *data++ = i2c_data_receive(i2c_periph);
            length--;
        }
        // 当还剩下3字节时，准备接收倒数第三字节
        // 等待倒数第三字节接收到移位寄存器
        while (!i2c_flag_get(i2c_periph, I2C_FLAG_BTC))
            ;
        // 清除ACKEN位，准备发送NACK
        i2c_ack_config(i2c_periph, I2C_ACK_DISABLE);
        // 读取倒数第三个字节
        *data++ = i2c_data_receive(i2c_periph);
        length--;
        // 发送停止信号
        i2c_stop_on_bus(i2c_periph);
        // 读取倒数第二个字节
        while (!i2c_flag_get(i2c_periph, I2C_FLAG_RBNE))
            ;
        *data++ = i2c_data_receive(i2c_periph);

        length--;
        // 读取最后一个字节
        while (!i2c_flag_get(i2c_periph, I2C_FLAG_RBNE))
            ;
        *data = i2c_data_receive(i2c_periph);

        while (I2C_CTL0(i2c_periph) & I2C_CTL0_STOP)
            ;
        i2c_ack_config(i2c_periph, I2C_ACK_ENABLE);

        return 0;
    }
    else
    {
        return 0;
    }
}

int i2c_master_send(uint32_t i2c_periph, uint8_t *data, uint16_t length, uint16_t address)
{
    while (i2c_flag_get(i2c_periph, I2C_FLAG_I2CBSY))
        ;
    i2c_start_on_bus(i2c_periph);
    while (!i2c_flag_get(i2c_periph, I2C_FLAG_SBSEND))
        ;
    i2c_master_addressing(i2c_periph, address, I2C_TRANSMITTER);

    if (i2c_flag_check_timeout(i2c_periph, I2C_FLAG_ADDSEND, SET))
    {
        i2c_stop_on_bus(i2c_periph);
        while (I2C_CTL0(i2c_periph) & I2C_CTL0_STOP)
            ;
        return 1;
    }

    // while (!i2c_flag_get(i2c_periph, I2C_FLAG_ADDSEND))
    //     ;
    i2c_flag_clear(i2c_periph, I2C_FLAG_ADDSEND);
    while (length--)
    {
        while (!i2c_flag_get(i2c_periph, I2C_FLAG_TBE))
            ;
        i2c_data_transmit(i2c_periph, *data++);
    }
    i2c_stop_on_bus(i2c_periph);
    while (I2C_CTL0(i2c_periph) & I2C_CTL0_STOP)
        ;
    return 0;
}

void I2C_Scan(uint32_t i2c_periph)
{
    log_454("Scanning for I2C devices...\r\n");
    uint8_t address;

    for (address = 1; address < 127; address++)
    {
        if (i2c_master_send(i2c_periph, NULL, 0, address))
        {
            continue;
        }
        else
        {
            log_454(intToStr(address));
        }
    }

    log_454("I2C scan completed.\r\n");
}

uint8_t ZXP_Initial(uint32_t i2c_periph)
{
    i2c_master_send(i2c_periph, ZXP3010D_Address, 1, ZXP3010D_Address);

    // 获取全部寄存器的值
    // uint8_t reg_cmd[4] = {0};
    // uint8_t reg[4] = {0};
    // reg_cmd[0] = 0x30; // 0x01
    // reg_cmd[1] = 0x6c; // 0x02
    // reg_cmd[2] = 0xa5; // 0x11

    // i2c_master_send(i2c_periph, &reg_cmd[0], 1, ZXP3010D_Address);
    // i2c_master_receive(i2c_periph, &reg[0], 1, ZXP3010D_Address);
    // i2c_master_send(i2c_periph, &reg_cmd[1], 1, ZXP3010D_Address);
    // i2c_master_receive(i2c_periph, &reg[1], 1, ZXP3010D_Address);
    // i2c_master_send(i2c_periph, &reg_cmd[2], 1, ZXP3010D_Address);
    // i2c_master_receive(i2c_periph, &reg[2], 1, ZXP3010D_Address);
}

void ZXP_StartP(uint32_t i2c_periph)
{

    uint8_t buf[4] = {0};
    buf[0] = 0xA5;
    // buf[1] = 0x13;输出原始ADC值
    buf[1] = 0x11; // 输出校准数据

    i2c_master_send(i2c_periph, buf, 2, ZXP3010D_Address);

    buf[0] = 0x30;
    buf[1] = 0x09;
    i2c_master_send(i2c_periph, buf, 2, ZXP3010D_Address);
}

void ZXP_StartT(uint32_t i2c_periph)
{
    uint8_t buf[4];

    buf[0] = 0xA5;
    buf[1] = 0x01;
    i2c_master_send(i2c_periph, buf, 2, ZXP3010D_Address);

    buf[0] = 0x30;
    buf[1] = 0x08;
    i2c_master_send(i2c_periph, buf, 2, ZXP3010D_Address);
}

uint8_t ZXP_ConStatus(uint32_t i2c_periph)
{
    uint8_t status;
    uint8_t buf[4] = {0};

    buf[0] = ZXP3010D_CMD;
    i2c_master_send(i2c_periph, buf, 1, ZXP3010D_Address);
    i2c_master_receive(i2c_periph, buf, 1, ZXP3010D_Address);
    status = (buf[0] >> 3) & 0x01;
    return status;
}

int32_t ZXP_ResultP(uint32_t i2c_periph)
{

    int32_t ltemp;
    uint8_t buf[4];
    buf[0] = 0x06;
    i2c_master_send(i2c_periph, buf, 1, ZXP3010D_Address);
    i2c_master_receive(i2c_periph, buf, 3, ZXP3010D_Address);

    ltemp = buf[0] << 8;
    ltemp |= buf[1];
    ltemp <<= 8;
    ltemp |= buf[2];
    return (ltemp);
}

int32_t ZXP_ResultT(uint32_t i2c_periph)
{
    int32_t ltemp;
    uint8_t cmd[2] = {0};
    uint8_t buf[2] = {0};

    cmd[0] = 0x09;
    cmd[1] = 0x0a;
    i2c_master_send(i2c_periph, &cmd[0], 1, ZXP3010D_Address);
    i2c_master_receive(i2c_periph, &buf[0], 2, ZXP3010D_Address);

    ltemp = buf[0] << 8;
    ltemp |= buf[1];

    return (ltemp);
}

void ZXP8_Caculate(int32_t up, int32_t ut, float *rp, float *rt)
{
    float fp, ft, ftemp;

    // 温度值正负判断
    ft = ut;
    if (ft >= pow(2.0, 15.0))
        ft = ft - pow(2.0, 16.0);
    // 压力值正负判断
    ftemp = up;
    if (ftemp >= pow(2.0, 23.0))
        ftemp = ftemp - pow(2.0, 24.0);
    ftemp = ftemp / pow(2.0, 9.0); // n=13  1Kpa// n=14  500pa//12 2kpa  //11 4kpa; // 9 10kpa //  6  100kpa

    ft = ft / 256.0;
    fp = ftemp;
    *rp = fp;
    *rt = ft;
}

void ZXP2_Caculate(int32_t up, int32_t ut, float *rp, float *rt)
{
    float fp, ft, ftemp;

    // 温度值正负判断
    ft = ut;
    if (ft >= pow(2.0, 15.0))
        ft = ft - pow(2.0, 16.0);
    // 压力值正负判断
    ftemp = up;
    if (ftemp >= pow(2.0, 23.0))
        ftemp = ftemp - pow(2.0, 24.0);
    ftemp = ftemp / pow(2.0, 6.0); // n6  100kpa

    ft = ft / 256.0;
    fp = ftemp;
    *rp = fp;
    *rt = ft;
}

void ZXP8_get_data_454(uint32_t i2c_periph, float *fTemp, float *fPress)
{
    int32_t press;
    int32_t temp = 0;
    ZXP_Initial(i2c_periph);

    ZXP_StartT(i2c_periph);
    ms_delay_454(4);
    do
    {
        ms_delay_454(1);
    } while (ZXP_ConStatus(i2c_periph));
    temp = ZXP_ResultT(i2c_periph);

    ZXP_StartP(i2c_periph);
    ms_delay_454(12);
    do
    {
        ms_delay_454(1);
    } while (ZXP_ConStatus(i2c_periph));
    press = ZXP_ResultP(i2c_periph);

    ZXP8_Caculate(press, temp, fPress, fTemp);
}

void ZXP2_get_data_454(uint32_t i2c_periph, float *fTemp, float *fPress)
{
    int32_t press;
    int32_t temp = 0;
    ZXP_Initial(i2c_periph);
    ZXP_StartT(i2c_periph);
    ms_delay_454(4);
    do
    {
        ms_delay_454(1);
    } while (ZXP_ConStatus(i2c_periph));
    temp = ZXP_ResultT(i2c_periph);
    ZXP_StartP(i2c_periph);
    ms_delay_454(12);
    do
    {
        ms_delay_454(1);
    } while (ZXP_ConStatus(i2c_periph));
    press = ZXP_ResultP(i2c_periph);

    ZXP2_Caculate(press, temp, fPress, fTemp);
}

void FS4301_get_data_454(uint32_t i2c_periph, float *flow_data)
{
    uint8_t buf[2];
    i2c_master_send(i2c_periph, FS4301_CMD, 1, FS4301_Address);
    i2c_master_receive(i2c_periph, buf, 2, FS4301_Address);
    uint16_t raw_flow = (uint16_t)buf[0] << 8 | buf[1];
    float actual_flow = (float)raw_flow / 100.00;
    *flow_data = (float)actual_flow;
}

// 中断函数
void I2C1_EV_IRQHandler(void)
{
    log_454("interrupt...");
    // if (i2c_interrupt_flag_get(I2C1, I2C_INT_FLAG_ADDSEND))
    // {
    //     /* clear the ADDSEND bit */
    //     // i2c_interrupt_flag_clear(I2C1, I2C_INT_FLAG_ADDSEND);
    // }
}

void DMA0_Channel6_IRQHandler(void)
{
    if (dma_interrupt_flag_get(DMA0, DMA_CH6, DMA_INT_FLAG_FTF) != RESET)
    {
        dma_interrupt_flag_clear(DMA0, DMA_CH6, DMA_INT_FLAG_FTF);
        dma_channel_disable(DMA0, DMA_CH6);
    }
}

void DMA1_Channel7_IRQHandler(void)
{
    if (dma_interrupt_flag_get(DMA1, DMA_CH7, DMA_INT_FLAG_FTF) != RESET)
    {
        dma_interrupt_flag_clear(DMA1, DMA_CH7, DMA_INT_FLAG_FTF);
        dma_channel_disable(DMA1, DMA_CH7);
    }
}