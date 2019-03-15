/**
 ******************************************************************************
 * @file    Project/STM32F0xx_StdPeriph_Templates/stm32f0xx_it.c
 * @author  MCD Application Team
 * @version V1.5.0
 * @date    05-December-2014
 * @brief   Main Interrupt Service Routines.
 *          This file provides template for all exceptions handler and
 *          peripherals interrupt service routine.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
 *
 * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *        http://www.st.com/software_license_agreement_liberty_v2
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"
#include "stm32f0xx.h"
#include "stm32f0xx_gpio.h"
#include "Delay.h"
#include "Button/Button.h"
#include "DHCP/dhcp.h"

static Button & buttons = Button::GetInstance();
extern uint32_t leasetime;

/** @addtogroup Template_Project
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
 * @brief  This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler(void)
{
}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
	while (1)
	{
	}
}

/**
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
void SVC_Handler(void)
{
}

/**
 * @brief  This function handles PendSVC exception.
 * @param  None
 * @retval None
 */
void PendSV_Handler(void)
{
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void)
{
	IncrementTick();

	if (GetTick() % 1000 == 0)
	{
		// do sth
		DHCP_time_handler();

		if (leasetime > 0)
			leasetime--;
	}

	NVIC_ClearPendingIRQ(SysTick_IRQn);
}

void EXTI0_1_IRQHandler(void)
{
	Button::Button_Name name = Button::NOBTN;

	if (EXTI_GetFlagStatus(EXTI_Line0))
	{
		name = Button::WAKEUP;
	}
	else if (EXTI_GetFlagStatus(EXTI_Line1))
	{
		name = Button::USER1;
	}

	EXTI_ClearITPendingBit(EXTI_Line0);
	EXTI_ClearITPendingBit(EXTI_Line1);
	buttons.SetState(name);
	NVIC_ClearPendingIRQ(EXTI0_1_IRQn);
}

void EXTI2_3_IRQHandler(void)
{
	Button::Button_Name name = Button::NOBTN;

	if (EXTI_GetFlagStatus(EXTI_Line2))
	{
		name = Button::USER0;
	}

	buttons.SetState(name);

	EXTI_ClearITPendingBit(EXTI_Line2);
	NVIC_ClearPendingIRQ(EXTI2_3_IRQn);
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                            */
/******************************************************************************/

/**
 * @brief  This function handles PPP interrupt request.
 * @param  None
 * @retval None
 */
/*void PPP_IRQHandler(void)
 {
 }*/

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
