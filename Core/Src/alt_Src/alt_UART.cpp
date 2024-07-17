/*
 * alt_Uart.cpp
 *
 *  Created on: Jul 15, 2024
 *      Author: Hamichev
 */


#include "alt_Inc/alt_UART.h"

void UART_t::Init()
{
	if(this->m_SetFlag & (1 << UART_SET_UART)){
		;
	}
	else{
		this->m_UART = UART4; //default
	}

	if(this->m_SetFlag & (1 << UART_SET_BAUDRATE)){
		;
	}
	else{
		this->m_BaudRate = 115200; //default
	}

	if(this->m_SetFlag & (1 << UART_SET_DATAWIDTH)){
		;
	}
	else{
		this->m_DataWidth = LL_USART_DATAWIDTH_8B; //default
	}

	if(this->m_SetFlag & (1 << UART_SET_STOPBITS)){
		;
	}
	else{
		this->m_StopBits = LL_USART_STOPBITS_1; //default
	}

	if(this->m_SetFlag & (1 << UART_SET_PARITY)){
		;
	}
	else{
		this->m_Parity = LL_USART_PARITY_NONE; //default
	}

	if(this->m_SetFlag & (1 << UART_SET_TRANSFERDIRECTION)){
		;
	}
	else{
		this->m_TransferDirection = LL_USART_DIRECTION_TX_RX; //default
	}

	if(this->m_SetFlag & (1 << UART_SET_HARDWAREFLOWCONTROL)){
		;
	}
	else{
		this->m_HardwareFlowControl = LL_USART_HWCONTROL_NONE; //default
	}

	if(this->m_SetFlag & (1 << UART_SET_OVERSEMPLING)){
		;
	}
	else{
		this->m_OverSampling = LL_USART_OVERSAMPLING_16; //default
	}

	if(this->m_SetFlag & (1 << UART_SET_ENABLECLOCK)){
		;
	}
	else{
		switch((uint32_t)this->m_UART){
		case (uint32_t)USART1_BASE:
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
			break;
		case (uint32_t)USART2_BASE:
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
			break;
		case (uint32_t)USART3_BASE:
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);
			break;
		case (uint32_t)UART4_BASE:
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART4);
			break;
		case (uint32_t)UART5_BASE:
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART5);
			break;
		}
	}

	if(this->m_SetFlag & (1 << UART_SET_IRQ)){
		;
	}
	else{
		this->m_Irq = UART4_IRQn; //default
	}

	this->OnIRQ(this->m_Irq);

	LL_USART_EnableIT_RXNE(this->m_UART);

	LL_USART_InitTypeDef USART_InitStruct = {0};

	USART_InitStruct.BaudRate = this->m_BaudRate;
	USART_InitStruct.DataWidth = this->m_DataWidth;
	USART_InitStruct.StopBits = this->m_StopBits;
	USART_InitStruct.Parity = this->m_Parity;
	USART_InitStruct.TransferDirection = this->m_TransferDirection;
	USART_InitStruct.HardwareFlowControl = this->m_HardwareFlowControl;
	USART_InitStruct.OverSampling = this->m_OverSampling;
	LL_USART_Init(this->m_UART, &USART_InitStruct);
	LL_USART_ConfigAsyncMode(this->m_UART);
	LL_USART_Enable(this->m_UART);
}

void UART_t::Init(USART_TypeDef *uart,uint32_t baudrate,uint32_t datawidth,uint32_t stopbits,uint32_t parity,
			  uint32_t transferdirection,uint32_t hardwareflowcontrol,uint32_t oversampling,IRQn_Type irq)
{
	this->m_UART = uart;
	this->m_BaudRate = baudrate;
	this->m_DataWidth = datawidth;
	this->m_StopBits = stopbits;
	this->m_Parity = parity;
	this->m_TransferDirection = transferdirection;
	this->m_HardwareFlowControl = hardwareflowcontrol;
	this->m_OverSampling = oversampling;
	this->m_Irq = irq;
	this->m_SetFlag = (1 << UART_SET_UART) | (1 << UART_SET_BAUDRATE) | (1 << UART_SET_DATAWIDTH) | (1 << UART_SET_STOPBITS) |
					  (1 << UART_SET_PARITY) | (1 << UART_SET_TRANSFERDIRECTION) | (1 << UART_SET_HARDWAREFLOWCONTROL) | (1 << UART_SET_OVERSEMPLING) |
					  (1 << UART_SET_IRQ) | (1 << UART_SET_ENABLECLOCK);

	if(uart == USART1){
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
	}
	else if(uart == USART2){
		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
	}
	else if(uart == USART3){
		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);
	}
	else if(uart == UART4){
		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART4);
	}
	else if(uart == UART5){
		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART5);
	}

	this->OnIRQ(irq);

	LL_USART_EnableIT_RXNE(uart);

	LL_USART_InitTypeDef USART_InitStruct = {0};

	USART_InitStruct.BaudRate = baudrate;
	USART_InitStruct.DataWidth = datawidth;
	USART_InitStruct.StopBits = stopbits;
	USART_InitStruct.Parity = parity;
	USART_InitStruct.TransferDirection = transferdirection;
	USART_InitStruct.HardwareFlowControl = hardwareflowcontrol;
	USART_InitStruct.OverSampling = oversampling;
	LL_USART_Init(uart, &USART_InitStruct);
	LL_USART_ConfigAsyncMode(uart);
	LL_USART_Enable(uart);
}

void UART_t::AddReceiveData(uint8_t dt)
{
	if(this->m_status_rx == STATUS_RX_FULL_RX_BUF_EMPTY || this->m_status_rx == STATUS_RX_EMPTY_RX_BUF_ANY){
		if(this->m_size_rx < RX_SIZE){
			this->m_rx_reserve[this->m_size_rx++] = dt;
		}
		else{
			if(this->m_status_rx == STATUS_RX_EMPTY_RX_BUF_ANY){
				this->m_status_rx = STATUS_RX_EMPTY_RX_BUF_FULL;
				this->m_size_rx = 0;
				this->m_rx[this->m_size_rx++] = dt;
			}
			else{
				; //error
			}
		}
	}
	else{
		if(this->m_size_rx < RX_SIZE){
			this->m_rx[m_size_rx++] = dt;
		}
		else{
			this->m_status_rx = STATUS_RX_FULL_RX_BUF_EMPTY;
			this->m_size_rx = 0;
			this->m_rx_reserve[this->m_size_rx++] = dt;
		}
	}
}

void UART_t::SendBufTx(uint16_t sz)
{
	uint16_t ind = 0;

	if(sz > TX_SIZE)
		return;

	while(ind < sz){
		while (!LL_USART_IsActiveFlag_TXE(this->m_UART)) {}
		LL_USART_TransmitData8(this->m_UART,this->m_tx[ind]);
		ind++;
	}
}

void UART_t::SendBufRx()
{
	if(this->m_status_rx == STATUS_RX_FULL_RX_BUF_EMPTY){
		for(uint16_t i=0; i<RX_SIZE; i++){
			this->m_tx[i] = this->m_rx[i];
			this->m_rx[i] = 0;
		}

		this->SendBufTx(TX_SIZE);

		uint16_t rx_size = this->m_size_rx;
		this->m_status_rx = STATUS_RX_EMPTY_RX_BUF_FULL;
		this->m_size_rx = 0;

		for(uint16_t i=0; i<rx_size; i++){
			this->m_tx[i] = this->m_rx_reserve[i];
			this->m_rx_reserve[i] = 0;
		}

		this->SendBufTx(rx_size);
		this->m_status_rx = STATUS_RX_EMPTY;
	}
	else{
		uint16_t rx_size_prev = this->m_size_rx;

		for(uint16_t i=0; i<rx_size_prev; i++){
			if(this->m_size_rx > rx_size_prev)
				rx_size_prev = this->m_size_rx;
			this->m_tx[i] = this->m_rx[i];
			this->m_rx[i] = 0;
		}

		this->SendBufTx(rx_size_prev);
		this->m_status_rx = STATUS_RX_EMPTY;
	}
}

void UART_t::CopyDataTx(uint8_t *dt, uint16_t sz)
{
	uint16_t ind = 0;

	if(sz > TX_SIZE)
		return;

	while(ind < sz){
		this->m_tx[ind] = *(uint8_t*)(dt+ind);
		ind++;
	}

	this->m_size_tx = sz;
}


void UART_t::OnIRQ(IRQn_Type irq)
{
	NVIC_SetPriority(irq, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
	NVIC_EnableIRQ(irq);
}

void UART_t::OffIRQ(IRQn_Type irq)
{
	NVIC_DisableIRQ(irq);
}

