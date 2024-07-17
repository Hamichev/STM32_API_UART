/*
 * alt_Uart.h
 *
 *  Created on: Jul 15, 2024
 *      Author: Hamichev
 */

#ifndef INC_ALT_INC_ALT_UART_H_
#define INC_ALT_INC_ALT_UART_H_

#define UART_SET_UART					0
#define UART_SET_BAUDRATE				1
#define UART_SET_DATAWIDTH				2
#define UART_SET_STOPBITS				3
#define UART_SET_PARITY					4
#define UART_SET_TRANSFERDIRECTION		5
#define UART_SET_HARDWAREFLOWCONTROL	6
#define UART_SET_OVERSEMPLING			7
#define UART_SET_IRQ					8
#define UART_SET_ENABLECLOCK			15

#define RX_SIZE 128
#define TX_SIZE 128

typedef enum {
	STATUS_RX_EMPTY = 0,
	STATUS_RX_FULL_RX_BUF_EMPTY,
	STATUS_RX_EMPTY_RX_BUF_ANY,
	STATUS_RX_EMPTY_RX_BUF_FULL
} Status_rx_t;

#define MACRO_CREATE_SET_AND_UP_FLAG(__VAR__,__VAL__,__BIT__)	{ \
	this->__VAR__ = __VAL__; \
	this->m_SetFlag |= (1 << __BIT__); \
}

#ifdef __cplusplus
extern "C"
{

#include <stdint.h>

#include "usart.h"

class UART_t
{

public:
	UART_t() {};
	~UART_t() {};

	void SetUART(USART_TypeDef *uart) {MACRO_CREATE_SET_AND_UP_FLAG(m_UART,uart,UART_SET_UART)};
	void SetBaudRate(uint32_t baudrate) {MACRO_CREATE_SET_AND_UP_FLAG(m_BaudRate,baudrate,UART_SET_BAUDRATE)};
	void SetDataWidth(uint32_t datawidth) {MACRO_CREATE_SET_AND_UP_FLAG(m_DataWidth,datawidth,UART_SET_DATAWIDTH)};
	void SetStopBits(uint32_t stopbits) {MACRO_CREATE_SET_AND_UP_FLAG(m_StopBits,stopbits,UART_SET_STOPBITS)};
	void SetParity(uint32_t parity) {MACRO_CREATE_SET_AND_UP_FLAG(m_Parity,parity,UART_SET_PARITY)};
	void SetTransferDirection(uint32_t transferdirection) {MACRO_CREATE_SET_AND_UP_FLAG(m_TransferDirection,transferdirection,UART_SET_TRANSFERDIRECTION)};
	void SetHardwareFlowControl(uint32_t hardwareflowcontrol) {MACRO_CREATE_SET_AND_UP_FLAG(m_HardwareFlowControl,hardwareflowcontrol,UART_SET_HARDWAREFLOWCONTROL)};
	void SetOverSampling(uint32_t oversampling) {MACRO_CREATE_SET_AND_UP_FLAG(m_OverSampling,oversampling,UART_SET_OVERSEMPLING)};
	void SetIRQ(IRQn_Type irq) {MACRO_CREATE_SET_AND_UP_FLAG(m_Irq,irq,UART_SET_IRQ)};

	void SetCallBackFunc(void (*func)()) {this->callBackFunc = func;};

	void Init();
	void Init(USART_TypeDef *uart,uint32_t baudrate,uint32_t datawidth,uint32_t stopbits,uint32_t parity,
			  uint32_t transferdirection,uint32_t hardwareflowcontrol,uint32_t oversampling,IRQn_Type irq);

	void EnableClock(uint32_t channel) {LL_APB1_GRP1_EnableClock(channel);};

	void OnIRQ(IRQn_Type irq);
	void OffIRQ(IRQn_Type irq);

	void AddReceiveData(uint8_t dt);

	void CreateSendPacket(uint8_t dt, uint8_t ind)	{
		this->m_tx[ind] = dt;
	};

	void SendBufTx(uint16_t sz);

	void SendBufRx();

	void CopyDataTx(uint8_t *dt, uint16_t sz);

	Status_rx_t StatusRx(){
		return this->m_status_rx;
	}

	void ClearRx(){
		uint16_t ind = 0;
		while(ind < RX_SIZE)
			this->m_rx[ind++] = 0;
		if(this->m_status_rx == STATUS_RX_FULL_RX_BUF_EMPTY)
			this->m_status_rx = STATUS_RX_EMPTY_RX_BUF_ANY;
	};

	void ClearRxReserve(){
		uint16_t ind = 0;
		while(ind < RX_SIZE)
			this->m_rx_reserve[ind++] = 0;
		if(this->m_status_rx == STATUS_RX_EMPTY_RX_BUF_FULL)
			this->m_status_rx = STATUS_RX_EMPTY;
	};

	uint8_t* AdrRx() {
		switch(this->m_status_rx){
		case STATUS_RX_EMPTY:
			return &this->m_rx[0];
			break;
		case STATUS_RX_FULL_RX_BUF_EMPTY:
			return &this->m_rx[0];
			break;
		case STATUS_RX_EMPTY_RX_BUF_ANY:
			return &this->m_rx_reserve[0];
			break;
		case STATUS_RX_EMPTY_RX_BUF_FULL:
			return &this->m_rx_reserve[0];
			break;
		}

		return &this->m_rx[0];
	};



	void (*callBackFunc)();

private:

	USART_TypeDef *m_UART;
	uint32_t m_BaudRate;
	uint32_t m_DataWidth;
	uint32_t m_StopBits;
	uint32_t m_Parity;
	uint32_t m_TransferDirection;
	uint32_t m_HardwareFlowControl;
	uint32_t m_OverSampling;
	IRQn_Type m_Irq;

	uint16_t m_size_rx = 0;
	uint8_t m_rx[RX_SIZE];
	uint8_t m_rx_reserve[RX_SIZE];
	Status_rx_t m_status_rx = STATUS_RX_EMPTY;

	uint16_t m_size_tx = 0;
	uint8_t m_tx[TX_SIZE];

	uint16_t m_SetFlag = 0;
};
#endif

#ifdef __cplusplus
}
#endif

#endif /* INC_ALT_INC_ALT_UART_H_ */
