/*
 * alt_GPIO.h
 *
 *  Created on: Jul 15, 2024
 *      Author: Hamichev
 */

#ifndef INC_ALT_INC_ALT_GPIO_H_
#define INC_ALT_INC_ALT_GPIO_H_

#define GPIO_SET_GPIO					0
#define GPIO_SET_PIN					1
#define GPIO_SET_MODE					2
#define GPIO_SET_SPEED					3
#define GPIO_SET_OUTPUTTYPE				4
#define GPIO_SET_PULL					5
#define GPIO_SET_ALTERNATE				6
#define GPIO_SET_ENABLECLOCK			15

#define MACRO_CREATE_SET_AND_UP_FLAG(__VAR__,__VAL__,__BIT__)	{ \
	this->__VAR__ = __VAL__; \
	this->m_SetFlag |= (1 << __BIT__); \
}

#ifdef __cplusplus
extern "C"
{

#include <stdint.h>

#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_gpio.h"

class GPIO_t
{

public:
	GPIO_t() {};
	~GPIO_t() {};

	void SetGPIO(GPIO_TypeDef *gpio) {MACRO_CREATE_SET_AND_UP_FLAG(m_GPIO,gpio,GPIO_SET_GPIO)};
	void SetPin(uint32_t pin) {MACRO_CREATE_SET_AND_UP_FLAG(m_Pin,pin,GPIO_SET_PIN)};
	void SetMode(uint32_t mode) {MACRO_CREATE_SET_AND_UP_FLAG(m_Mode,mode,GPIO_SET_MODE)};
	void SetSpeed(uint32_t speed) {MACRO_CREATE_SET_AND_UP_FLAG(m_Speed,speed,GPIO_SET_SPEED)};
	void SetOutputType(uint32_t outputtype) {MACRO_CREATE_SET_AND_UP_FLAG(m_OutputType,outputtype,GPIO_SET_OUTPUTTYPE)};
	void SetPull(uint32_t pull) {MACRO_CREATE_SET_AND_UP_FLAG(m_Pull,pull,GPIO_SET_PULL)};
	void SetAlternate(uint32_t alternate) {MACRO_CREATE_SET_AND_UP_FLAG(m_Alternate,alternate,GPIO_SET_ALTERNATE)};

	void Init();
	void Init(GPIO_TypeDef *gpio,uint32_t pin,uint32_t mode,uint32_t speed,uint32_t outputtype,uint32_t pull,uint32_t alternate);

	void InitInput(GPIO_TypeDef *gpio,uint32_t pin,uint32_t mode,uint32_t pull);

	bool Read() {return (bool)LL_GPIO_IsInputPinSet(this->m_GPIO, this->m_Pin);};

	void EnableClock(uint32_t channel) {LL_AHB1_GRP1_EnableClock(channel);};

private:

	GPIO_TypeDef *m_GPIO;
	uint32_t m_Pin;
	uint32_t m_Mode;
	uint32_t m_Speed;
	uint32_t m_OutputType;
	uint32_t m_Pull;
	uint32_t m_Alternate;

	uint16_t m_SetFlag = 0;
};
#endif


#ifdef __cplusplus
}
#endif

#endif /* INC_ALT_INC_ALT_GPIO_H_ */
