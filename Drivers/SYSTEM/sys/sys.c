/**
 ****************************************************************************************************
 * @file        sys.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2021-10-14
 * @brief       ϵͳ��ʼ������(����ʱ������/�жϹ���/GPIO���õ�)
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32F407������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 * �޸�˵��
 * V1.0 20211014
 * ��һ�η���
 ****************************************************************************************************
 */

#include "./SYSTEM/sys/sys.h"


/**
 * @brief       �����ж�������ƫ�Ƶ�ַ
 * @param       baseaddr: ��ַ
 * @param       offset: ƫ����
 * @retval      ��
 */
void sys_nvic_set_vector_table(uint32_t baseaddr, uint32_t offset)
{
    /* ����NVIC��������ƫ�ƼĴ���,VTOR��9λ����,��[8:0]���� */
    SCB->VTOR = baseaddr | (offset & (uint32_t)0xFFFFFE00);
}

/**
 * @brief       ִ��: WFIָ��(ִ�����ָ�����͹���״̬, �ȴ��жϻ���)
 * @param       ��
 * @retval      ��
 */
void sys_wfi_set(void)
{
    __ASM volatile("wfi");
}

/**
 * @brief       �ر������ж�(���ǲ�����fault��NMI�ж�)
 * @param       ��
 * @retval      ��
 */
void sys_intx_disable(void)
{
    __ASM volatile("cpsid i");
}

/**
 * @brief       ���������ж�
 * @param       ��
 * @retval      ��
 */
void sys_intx_enable(void)
{
    __ASM volatile("cpsie i");
}

/**
 * @brief       ����ջ����ַ
 * @note        ��������ֺ�X, ����MDK��, ʵ����û�����
 * @param       addr: ջ����ַ
 * @retval      ��
 */
void sys_msr_msp(uint32_t addr)
{
    __set_MSP(addr);    /* ����ջ����ַ */
}

/**
 * @brief       �������ģʽ
 * @param       ��
 * @retval      ��
 */
void sys_standby(void)
{
    __HAL_RCC_PWR_CLK_ENABLE();    /* ʹ�ܵ�Դʱ�� */
    SET_BIT(PWR->CR, PWR_CR_PDDS); /* �������ģʽ */
}

/**
 * @brief       ϵͳ��λ
 * @param       ��
 * @retval      ��
 */
void sys_soft_reset(void)
{
    NVIC_SystemReset();
}

/**
 * @brief       ʱ�����ú���
 * @param       plln: PLL1��Ƶϵ��(PLL��Ƶ), ȡֵ��Χ: 64~432.
 * @param       pllm: PLL1Ԥ��Ƶϵ��(��PLL֮ǰ�ķ�Ƶ), ȡֵ��Χ: 2~63.
 * @param       pllp: PLL1��p��Ƶϵ��(PLL֮��ķ�Ƶ), ��Ƶ����Ϊϵͳʱ��, ȡֵ��Χ: 2,4,6,8.(������4��ֵ!)
 * @param       pllq: PLL1��q��Ƶϵ��(PLL֮��ķ�Ƶ), ȡֵ��Χ: 2~15.
 * @note
 *
 *              Fvco: VCOƵ��
 *              Fsys: ϵͳʱ��Ƶ��, Ҳ��PLL1��p��Ƶ���ʱ��Ƶ��
 *              Fq:   PLL1��q��Ƶ���ʱ��Ƶ��
 *              Fs:   PLL����ʱ��Ƶ��, ������HSI, CSI, HSE��.
 *              Fvco = Fs * (plln / pllm);
 *              Fsys = Fvco / pllp = Fs * (plln / (pllm * pllp));
 *              Fq   = Fvco / pllq = Fs * (plln / (pllm * pllq));
 *
 *              �ⲿ����Ϊ25M��ʱ��, �Ƽ�ֵ: plln = 336, pllm = 8, pllp = 2, pllq = 7.
 *              �õ�:Fvco = 8 * (336 / 8) = 336Mhz
 *                   Fsys = pll1_p_ck = 336 / 2 = 168Mhz
 *                   Fq   = pll1_q_ck = 336 / 7 = 48
 *
 * @retval      �������: 0, �ɹ�; 1, ����;
 */
uint8_t sys_stm32_clock_init(uint32_t plln, uint32_t pllm, uint32_t pllp, uint32_t pllq)
{
    HAL_StatusTypeDef ret = HAL_OK;
    RCC_ClkInitTypeDef rcc_clk_init_handle;
    RCC_OscInitTypeDef rcc_osc_init_handle;
    
    __HAL_RCC_PWR_CLK_ENABLE();                                         /* ʹ��PWRʱ�� */
    
    /* ������������������õ�ѹ�������ѹ�����Ա�������δ�����Ƶ�ʹ���ʱʹ�����빦��ʵ��ƽ�� */

    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);      /* VOS = 1, Scale1, 1.2V�ں˵�ѹ,FLASH���ʿ��Եõ�������� */

    /* ʹ��HSE����ѡ��HSE��ΪPLLʱ��Դ������PLL1������USBʱ�� */
    rcc_osc_init_handle.OscillatorType = RCC_OSCILLATORTYPE_HSE;        /* ʱ��ԴΪHSE */
    rcc_osc_init_handle.HSEState = RCC_HSE_ON;                          /* ��HSE */
    rcc_osc_init_handle.PLL.PLLState = RCC_PLL_ON;                      /* ��PLL */
    rcc_osc_init_handle.PLL.PLLSource = RCC_PLLSOURCE_HSE;              /* PLLʱ��Դѡ��HSE */
    rcc_osc_init_handle.PLL.PLLN = plln;
    rcc_osc_init_handle.PLL.PLLM = pllm;
    rcc_osc_init_handle.PLL.PLLP = pllp;
    rcc_osc_init_handle.PLL.PLLQ = pllq;

    ret=HAL_RCC_OscConfig(&rcc_osc_init_handle);                        /* ��ʼ��RCC */
    if(ret != HAL_OK)
    {
        return 1;                                                       /* ʱ�ӳ�ʼ��ʧ�ܣ���������������Լ��Ĵ��� */
    }

    /* ѡ��PLL��Ϊϵͳʱ��Դ��������HCLK,PCLK1��PCLK2*/
    rcc_clk_init_handle.ClockType = ( RCC_CLOCKTYPE_SYSCLK \
                                    | RCC_CLOCKTYPE_HCLK \
                                    | RCC_CLOCKTYPE_PCLK1 \
                                    | RCC_CLOCKTYPE_PCLK2);

    rcc_clk_init_handle.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;         /* ����ϵͳʱ��ʱ��ԴΪPLL */
    rcc_clk_init_handle.AHBCLKDivider = RCC_SYSCLK_DIV1;                /* AHB��Ƶϵ��Ϊ1 */
    rcc_clk_init_handle.APB1CLKDivider = RCC_HCLK_DIV4;                 /* APB1��Ƶϵ��Ϊ2 */
    rcc_clk_init_handle.APB2CLKDivider = RCC_HCLK_DIV2;                 /* APB2��Ƶϵ��Ϊ1 */

    ret = HAL_RCC_ClockConfig(&rcc_clk_init_handle, FLASH_LATENCY_4);   /* ͬʱ����FLASH��ʱ����Ϊ5WS��Ҳ����6��CPU���� */
    if(ret != HAL_OK)
    {
        return 1;                                                       /* ʱ�ӳ�ʼ��ʧ�� */
    }
    
    /* STM32F405x/407x/415x/417x Z�汾������֧��Ԥȡ���� */
    if (HAL_GetREVID() == 0x1001)
    {
        __HAL_FLASH_PREFETCH_BUFFER_ENABLE();                           /* ʹ��flashԤȡ */
    }
    return 0;
}

void sys_gpio_af_set(GPIO_TypeDef *p_gpiox, uint16_t pinx, uint8_t afx)
{
    uint32_t pinpos = 0, pos = 0, curpin = 0;;

    for (pinpos = 0; pinpos < 16; pinpos++)
    {
        pos = 1 << pinpos;      /* һ����λ��� */
        curpin = pinx & pos;    /* ��������Ƿ�Ҫ���� */

        if (curpin == pos)      /* ��Ҫ���� */
        {
            p_gpiox->AFR[pinpos >> 3] &= ~(0X0F << ((pinpos & 0X07) * 4));
            p_gpiox->AFR[pinpos >> 3] |= (uint32_t)afx << ((pinpos & 0X07) * 4);
        }
    }
}

/**
 * @brief       GPIOͨ������
 * @param       p_gpiox: GPIOA~GPIOI, GPIOָ��
 * @param       pinx: 0X0000~0XFFFF, ����λ��, ÿ��λ����һ��IO, ��0λ����Px0, ��1λ����Px1, ��������. ����0X0101, ����ͬʱ����Px0��Px8.
 *   @arg       SYS_GPIO_PIN0~SYS_GPIO_PIN15, 1<<0 ~ 1<<15
 *
 * @param       mode: 0~3; ģʽѡ��, ��������:
 *   @arg       SYS_GPIO_MODE_IN,  0, ����ģʽ(ϵͳ��λĬ��״̬)
 *   @arg       SYS_GPIO_MODE_OUT, 1, ���ģʽ
 *   @arg       SYS_GPIO_MODE_AF,  2, ���ù���ģʽ
 *   @arg       SYS_GPIO_MODE_AIN, 3, ģ������ģʽ
 *
 * @param       otype: 0 / 1; �������ѡ��, ��������:
 *   @arg       SYS_GPIO_OTYPE_PP, 0, �������
 *   @arg       SYS_GPIO_OTYPE_OD, 1, ��©���
 *
 * @param       ospeed: 0~3; ����ٶ�, ��������:
 *   @arg       SYS_GPIO_SPEED_LOW,  0, ����
 *   @arg       SYS_GPIO_SPEED_MID,  1, ����
 *   @arg       SYS_GPIO_SPEED_FAST, 2, ����
 *   @arg       SYS_GPIO_SPEED_HIGH, 3, ����
 *
 * @param       pupd: 0~3: ����������, ��������:
 *   @arg       SYS_GPIO_PUPD_NONE, 0, ����������
 *   @arg       SYS_GPIO_PUPD_PU,   1, ����
 *   @arg       SYS_GPIO_PUPD_PD,   2, ����
 *   @arg       SYS_GPIO_PUPD_RES,  3, ����
 *
 * @note:       ע��: ������ģʽ(��ͨ����/ģ������)��, OTYPE��OSPEED������Ч!!
 * @retval      ��
 */
void sys_gpio_set(GPIO_TypeDef *p_gpiox, uint16_t pinx, uint32_t mode, uint32_t otype, uint32_t ospeed, uint32_t pupd)
{
    uint32_t pinpos = 0, pos = 0, curpin = 0;

    for (pinpos = 0; pinpos < 16; pinpos++)
    {
        pos = 1 << pinpos;      /* һ����λ��� */
        curpin = pinx & pos;    /* ��������Ƿ�Ҫ���� */

        if (curpin == pos)      /* ��Ҫ���� */
        {
            p_gpiox->MODER &= ~(3 << (pinpos * 2)); /* �����ԭ�������� */
            p_gpiox->MODER |= mode << (pinpos * 2); /* �����µ�ģʽ */

            if ((mode == 0X01) || (mode == 0X02))   /* ��������ģʽ/���ù���ģʽ */
            {
                p_gpiox->OSPEEDR &= ~(3 << (pinpos * 2));       /* ���ԭ�������� */
                p_gpiox->OSPEEDR |= (ospeed << (pinpos * 2));   /* �����µ��ٶ�ֵ */
                p_gpiox->OTYPER &= ~(1 << pinpos) ;             /* ���ԭ�������� */
                p_gpiox->OTYPER |= otype << pinpos;             /* �����µ����ģʽ */
            }

            p_gpiox->PUPDR &= ~(3 << (pinpos * 2)); /* �����ԭ�������� */
            p_gpiox->PUPDR |= pupd << (pinpos * 2); /* �����µ������� */
        }
    }
}


#ifdef  USE_FULL_ASSERT

/**
 * @brief       ��������ʾ�����ʱ��˺����������������ļ���������
 * @param       file��ָ��Դ�ļ�
 *              line��ָ�����ļ��е�����
 * @retval      ��
 */
void assert_failed(uint8_t* file, uint32_t line)
{ 
    while (1)
    {
    }
}
#endif




