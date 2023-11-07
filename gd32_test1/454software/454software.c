#include "./454software.h"
/*!
    \brief      initialize all 454
    \param[in]  none
    \param[out] none
    \retval     none
*/
char strOutput_454[MAX_STR_SIZE]; // �洢ת������ַ���

void init_454(void)
{
    RCU_init_454();
    NVIC_init_454();
    /* Configure GPIO */

    /* ����PC9ΪCKOUT1 */
    gpio_af_set(GPIOC, GPIO_AF_0, GPIO_PIN_9);
    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_9);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
    rcu_ckout1_config(RCU_CKOUT1SRC_SYSTEMCLOCK, RCU_CKOUT1_DIV1);

    // ����PG6,PG7,PG8
    gpio_mode_set(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_6);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6);
    gpio_mode_set(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_7);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7);
    gpio_mode_set(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_8);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_8);

    gpio_bit_set(GPIOG, GPIO_PIN_6);
    gpio_bit_set(GPIOG, GPIO_PIN_7);
    gpio_bit_set(GPIOG, GPIO_PIN_8);

    // ����PE0,PE1,PE2
    gpio_mode_set(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_0);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0);
    gpio_mode_set(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_1);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_1);
    gpio_mode_set(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_2);
    gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);

    gpio_bit_set(GPIOE, GPIO_PIN_0);
    gpio_bit_set(GPIOE, GPIO_PIN_1);
    gpio_bit_set(GPIOE, GPIO_PIN_2);

    // ����PA6,PC6,PD12
    gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_6);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6);

    gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_6);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6);

    gpio_mode_set(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_12);
    gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12);

    gpio_bit_set(GPIOA, GPIO_PIN_6);
    gpio_bit_set(GPIOC, GPIO_PIN_6);
    gpio_bit_set(GPIOD, GPIO_PIN_12);

    /* Configure TIMER6 */
    timer_deinit(RCU_TIMER6);
    timer_parameter_struct timer_initpara;
    timer_initpara.prescaler = 199;
    timer_initpara.alignedmode = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection = TIMER_COUNTER_UP;
    timer_initpara.period = 999; // ʵ��1ms�Ķ�ʱ��
    timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
    timer_init(TIMER6, &timer_initpara);
    timer_enable(TIMER6);

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
    usart_prescaler_config(USART1, 1U);
    usart_enable(USART1);

    /* Configure I2C0 P10 PB8 PB9*/
    gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_9); // I2C0_SDA
    gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_8); // I2C0_SCL

    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_8);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_8);

    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_9);

    i2c_deinit(I2C0);
    i2c_clock_config(I2C0, 100000, I2C_DTCY_2);
    i2c_mode_addr_config(I2C0, I2C_I2CMODE_ENABLE, I2C_ADDFORMAT_7BITS, I2C0_OWN_ADDRESS7);
    i2c_enable(I2C0);
    i2c_ack_config(I2C0, I2C_ACK_ENABLE);

    /* Configure I2C1 P11 PF0 PF1 */
    gpio_af_set(GPIOF, GPIO_AF_4, GPIO_PIN_0); // I2C1_SDA
    gpio_af_set(GPIOF, GPIO_AF_4, GPIO_PIN_1); // I2C1_SCL

    gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_0);
    gpio_output_options_set(GPIOF, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_0);

    gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_1);
    gpio_output_options_set(GPIOF, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_1);

    i2c_deinit(I2C1);
    i2c_clock_config(I2C1, 100000, I2C_DTCY_2);
    // i2c_interrupt_enable(I2C1,I2C_INT_EV);
    i2c_mode_addr_config(I2C1, I2C_I2CMODE_ENABLE, I2C_ADDFORMAT_7BITS, I2C1_OWN_ADDRESS7);
    i2c_enable(I2C1);
    i2c_ack_config(I2C1, I2C_ACK_ENABLE);
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
    rcu_periph_clock_enable(RCU_USART1);
    rcu_periph_clock_enable(RCU_DMA0);
    rcu_periph_clock_enable(RCU_I2C0);
    rcu_periph_clock_enable(RCU_I2C1);

    rcu_ahb_clock_config(RCU_AHB_CKSYS_DIV1);
    rcu_apb1_clock_config(RCU_APB1_CKAHB_DIV1);
}

void NVIC_init_454(void)
{
    nvic_priority_group_set(NVIC_PRIGROUP_PRE1_SUB3);
    // ����ԽС�����ȼ�Խ��
    nvic_irq_enable(DMA0_Channel6_IRQn, 0, 7);

    // nvic_irq_enable(I2C0_EV_IRQn, 0, 3);
    // nvic_irq_enable(I2C1_EV_IRQn, 0, 4);
    // nvic_irq_enable(I2C0_ER_IRQn, 0, 2);
    // nvic_irq_enable(I2C1_ER_IRQn, 0, 1);
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

    // Reverse the string (excluding negative sign, if any)
    char *revStart = (start == end - 1) ? start : start + 1;
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

    return start;
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

uint32_t i2c_flag_check_timeout(uint32_t i2c_periph, uint32_t flag, FlagStatus expected_Status)
{
    uint32_t timeout = 0xFFFF;
    while (i2c_flag_get(i2c_periph, flag) != expected_Status)
    {
        if (timeout == 0)
        {
            return 0; // Timeout
        }
        timeout--;
    }
    return 1; // Success
}

void i2c_master_receive(uint32_t i2c_periph, uint8_t *data, uint16_t length, uint16_t address)
{
    if (length == 2)
    {
        // ���Ӧ����START��1֮ǰ��POAP��1
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
        return;
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
        return;
    }
    else if (length > 2)
    {
        i2c_flag_clear(i2c_periph, I2C_FLAG_ADDSEND);
        // ����N-3�ֽ�
        while (length > 3)
        {
            while (!i2c_flag_get(i2c_periph, I2C_FLAG_RBNE))
                ;
            *data++ = i2c_data_receive(i2c_periph);
            length--;
        }
        // ����ʣ��3�ֽ�ʱ��׼�����յ��������ֽ�
        // �ȴ����������ֽڽ��յ���λ�Ĵ���
        while (!i2c_flag_get(i2c_periph, I2C_FLAG_BTC))
            ;
        // ���ACKENλ��׼������NACK
        i2c_ack_config(i2c_periph, I2C_ACK_DISABLE);
        // ��ȡ�����������ֽ�
        *data++ = i2c_data_receive(i2c_periph);
        length--;
        // ����ֹͣ�ź�
        i2c_stop_on_bus(i2c_periph);
        // ��ȡ�����ڶ����ֽ�
        while (!i2c_flag_get(i2c_periph, I2C_FLAG_RBNE))
            ;
        *data++ = i2c_data_receive(i2c_periph);

        length--;
        // ��ȡ���һ���ֽ�
        while (!i2c_flag_get(i2c_periph, I2C_FLAG_RBNE))
            ;
        *data = i2c_data_receive(i2c_periph);

        while (I2C_CTL0(i2c_periph) & I2C_CTL0_STOP)
            ;
        i2c_ack_config(i2c_periph, I2C_ACK_ENABLE);

        return;
    }
    else
    {
        return;
    }
}

void i2c_master_send(uint32_t i2c_periph, uint8_t *data, uint16_t length, uint16_t address)
{
    while (i2c_flag_get(i2c_periph, I2C_FLAG_I2CBSY))
        ;
    i2c_start_on_bus(i2c_periph);
    while (!i2c_flag_get(i2c_periph, I2C_FLAG_SBSEND))
        ;
    i2c_master_addressing(i2c_periph, address, I2C_TRANSMITTER);
    while (!i2c_flag_get(i2c_periph, I2C_FLAG_ADDSEND))
        ;
    i2c_flag_clear(i2c_periph, I2C_FLAG_ADDSEND);
    while (length--)
    {
        while (!i2c_flag_get(I2C0, I2C_FLAG_TBE))
            ;
        i2c_data_transmit(i2c_periph, *data++);
    }
    i2c_stop_on_bus(i2c_periph);
    while (I2C_CTL0(i2c_periph) & I2C_CTL0_STOP)
        ;
}

uint8_t P11_Initial(void)
{
    i2c_master_send(I2C0, ZXP3010D_Address, 1, ZXP3010D_Address);
}

void P11_StartP(void)
{
    uint8_t buf[4];

    buf[0] = 0xA5;
    // buf[1] = 0x13;���ԭʼADCֵ
    buf[1] = 0x11; // ���У׼����

    i2c_master_send(I2C0, buf, 2, ZXP3010D_Address);

    buf[0] = 0x30;
    buf[1] = 0x09;
    i2c_master_send(I2C0, buf, 2, ZXP3010D_Address);
}

uint8_t P11_ConStatus(void)
{
    uint8_t status;
    uint8_t buf[4] = {0};

    buf[0] = ZXP3010D_CMD;
    i2c_master_send(I2C0, buf, 1, ZXP3010D_Address);

    i2c_master_receive(I2C0, buf, 1, ZXP3010D_Address);
    status = (buf[0] >> 3) & 0x01;
    return status;
}

int32_t P11_ResultP(void)
{

    int32_t ltemp;
    uint8_t buf[4];
    buf[0] = 0x06;
    i2c_master_send(I2C0, buf, 1, ZXP3010D_Address);
    i2c_master_receive(I2C0, buf, 3, ZXP3010D_Address);

    ltemp = buf[0] << 8;
    ltemp |= buf[1];
    ltemp <<= 8;
    ltemp |= buf[2];
    return (ltemp);
}

void P11_Caculate(int32_t up, int32_t ut, float *rp, float *rt)
{
	float fp, ft, ftemp;
	
///////////////////////////////////////////////////  �¶�ֵ�����ж�       
        ft = ut ;
        if(ft >= pow(2.0, 15.0))
	
           ft =ft - pow(2.0, 16.0);
              
 ///////////////////////////////////////////////////       
       
 /////////////////////////////////////////////////    ѹ��ֵ�����ж�   
         ftemp = up;
         if(ftemp >= pow(2.0, 23.0))
	
           ftemp =ftemp - pow(2.0, 24.0);
 //////////////////////////////////////////////////    
     ftemp= ftemp/pow(2.0, 12.0); //n=13  1Kpa// n=14  500pa//12 2kpa  //11 4kpa; // 9 10kpa //  6  100kpa            
        
        ft =  ft / 256.0;
        fp = ftemp;                                    
	*rp = fp;
	*rt = ft;
}












// �жϺ���
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