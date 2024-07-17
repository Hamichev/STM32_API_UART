/*
 * alt_GPIO.cpp
 *
 *  Created on: Jul 15, 2024
 *      Author: Hamichev
 */

#include "alt_Inc/alt_GPIO.h"


void GPIO_t::Init()
{
	if(this->m_SetFlag & (1 << GPIO_SET_GPIO)){
		;
	}
	else{
		this->m_GPIO = GPIOA; //default
	}

	if(this->m_SetFlag & (1 << GPIO_SET_PIN)){
		;
	}
	else{
		this->m_Pin = LL_GPIO_PIN_0; //default
	}

	if(this->m_SetFlag & (1 << GPIO_SET_MODE)){
		;
	}
	else{
		this->m_Mode = LL_GPIO_MODE_ALTERNATE; //default
	}

	if(this->m_SetFlag & (1 << GPIO_SET_SPEED)){
		;
	}
	else{
		this->m_Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH; //default
	}

	if(this->m_SetFlag & (1 << GPIO_SET_OUTPUTTYPE)){
		;
	}
	else{
		this->m_OutputType = LL_GPIO_OUTPUT_PUSHPULL; //default
	}

	if(this->m_SetFlag & (1 << GPIO_SET_PULL)){
		;
	}
	else{
		this->m_Pull = LL_GPIO_PULL_NO; //default
	}

	if(this->m_SetFlag & (1 << GPIO_SET_ALTERNATE)){
		;
	}
	else{
		this->m_Alternate = LL_GPIO_AF_8; //default
	}

	if(this->m_SetFlag & (1 << GPIO_SET_ENABLECLOCK)){
		;
	}
	else{
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	}

	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = this->m_Pin;
	GPIO_InitStruct.Mode = this->m_Mode;
	GPIO_InitStruct.Speed = this->m_Speed;
	GPIO_InitStruct.OutputType = this->m_OutputType;
	GPIO_InitStruct.Pull = this->m_Pull;
	GPIO_InitStruct.Alternate = this->m_Alternate;
	LL_GPIO_Init(this->m_GPIO, &GPIO_InitStruct);
}

void GPIO_t::Init(GPIO_TypeDef *gpio,uint32_t pin,uint32_t mode,uint32_t speed,uint32_t outputtype,uint32_t pull,uint32_t alternate)
{
	if(gpio == GPIOA){
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	}
	else if(gpio == GPIOB){
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
	}
	else if(gpio == GPIOC){
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
	}
#if defined(GPIOD)
	else if(gpio == GPIOD){
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
	}
#endif
#if defined(GPIOE)
	else if(gpio == GPIOE){
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOE);
	}
#endif
#if defined(GPIOF)
	else if(gpio == GPIOF){
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF);
	}
#endif
#if defined(GPIOG)
	else if(gpio == GPIOG){
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOG);
	}
#endif
#if defined(GPIOH)
	else if(gpio == GPIOH){
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOH);
	}
#endif
#if defined(GPIOI)
	else if(gpio == GPIOI){
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOI);
	}
#endif

	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = pin;
	GPIO_InitStruct.Mode = mode;
	GPIO_InitStruct.Speed = speed;
	GPIO_InitStruct.OutputType = outputtype;
	GPIO_InitStruct.Pull = pull;
	GPIO_InitStruct.Alternate = alternate;
	LL_GPIO_Init(gpio, &GPIO_InitStruct);
}

void GPIO_t::InitInput(GPIO_TypeDef *gpio,uint32_t pin,uint32_t mode,uint32_t pull)
{
	if(gpio == GPIOA){
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	}
	else if(gpio == GPIOB){
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
	}
	else if(gpio == GPIOC){
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
	}
#if defined(GPIOD)
	else if(gpio == GPIOD){
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
	}
#endif
#if defined(GPIOE)
	else if(gpio == GPIOE){
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOE);
	}
#endif
#if defined(GPIOF)
	else if(gpio == GPIOF){
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF);
	}
#endif
#if defined(GPIOG)
	else if(gpio == GPIOG){
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOG);
	}
#endif
#if defined(GPIOH)
	else if(gpio == GPIOH){
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOH);
	}
#endif
#if defined(GPIOI)
	else if(gpio == GPIOI){
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOI);
	}
#endif

	this->m_GPIO = gpio;
	this->m_Pin = pin;
	this->m_Mode = mode;
	this->m_Pull = pull;

	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = pin;
	GPIO_InitStruct.Mode = mode;
	GPIO_InitStruct.Pull = pull;
	LL_GPIO_Init(gpio, &GPIO_InitStruct);
}
