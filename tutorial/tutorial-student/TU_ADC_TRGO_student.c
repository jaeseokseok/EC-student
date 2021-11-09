

/**
******************************************************************************
* @author  SSSLAB
* @Mod		 2021-8-12 by YKKIM  	
* @brief   Embedded Controller:  Tutorial ___
*					 - _________________________________
* 
******************************************************************************
*/
#include "stm32f411xe.h"
#include "ecGPIO.h"
#include "ecRCC.h"
#include "ecTIM.h"
#include "ecSysTick.h"
#include "ecUART_student.h"
float result_v =0;
void setup(void);
	
int main(void) { 
	// Initialiization --------------------------------------------------------
	setup();
	
	/* ADC_initiation --------------------------------------------------------------------*/
  // 1) Enable the clock of ADC
  // 2) ...
	// 3) ...
  
// HW Trigger configuration -------------------------------------------------------------
// 1. TIMx Trigger Output Config
	// Enable TIMx Clock
	TIM_TypeDef *timx = TIM3;			// Default TRGO : TIM3
	int msec = 1;									// Default msec : 1 msec
	TIM_init(timx, msec);					// TIM3 init (use user defined HAL)
	timx->CR1 &= ~1; 							// counter disable
	
	// Set PSC, ARR
  TIM_period_ms(timx, msec);
	
  // Master Mode Selection MMS[2:0]: Trigger output (TRGO)
  timx->CR2 &= 								// reset MMS
  timx->CR2 |=    						//100: Compare - OC1REF signal is used as trigger output (TRGO)
   
	// Output Compare Mode
  timx->CCMR1 &=       				// OC1M : output compare 1 Mode 
  timx->CCMR1 |=          		// OC1M = 110 for compare 1 Mode ch1 
	
  // OC1 signal 
  timx->CCER |=            		// CC1E Capture enabled
	timx->CCR1  = 							// CCR set
   
  // Enable TIMx 
  timx->CR1 |= 1; 						//counter enable
	
// 2. HW Trigger
	// Select Trigger Source
	ADC1->CR2 &=  							// reset EXTSEL
	ADC1->CR2 |=  							// TIMx TRGO event (ADC : TIM2, TIM3 TRGO) default : TIM3
	
	//Select Trigger Polarity 
	ADC1->CR2 &= 								// reset EXTEN, default
	ADC1->CR2 |= 								// trigger detection rising edge
	
	// Enable ADC 
	ADC1->CR2 |= ADC_CR2_ADON;
	
  // ADC Start (SW, once)	  
  ADC1->CR2 |= ADC_CR2_SWSTART;

	/* Inifinite Loop --------------------------------------------------------------------*/
	while(1);
}

// Initialiization 
void setup(void)
{	
	RCC_PLL_init();                 // System Clock = 84MHz
	UART2_init();
	GPIO_init(GPIOA, 1, EC_ANG);    // calls RCC_GPIOA_enable()
	GPIO_pupdr(GPIOA, 1, EC_NONE);
}

void ADC_IRQHandler(void){		
	if((ADC1->SR & ADC_SR_OVR) == ADC_SR_OVR){
		ADC1->SR &= ~ADC_SR_OVR;
	}
	
	if(is_ADC_EOC()){       			
	  result_v = ADC_read();
		printf("voltage = %.3f\r\n",result_v*3.3/4095);
	
 }
}