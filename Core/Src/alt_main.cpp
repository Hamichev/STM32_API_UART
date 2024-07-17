/*
 * alt_main.cpp
 *
 *  Created on: Jul 13, 2024
 *      Author: Hamichev
 */

#include <alt_main.h>

#ifdef __cplusplus

GPIO_t cust_GPIO_Bt_User;

UART_t cust_USART1;
GPIO_t cust_GPIO_RX_USART1;
GPIO_t cust_GPIO_TX_USART1;

UART_t cust_USART2;
GPIO_t cust_GPIO_RX_USART2;
GPIO_t cust_GPIO_TX_USART2;

UART_t cust_USART3;
GPIO_t cust_GPIO_RX_USART3;
GPIO_t cust_GPIO_TX_USART3;

UART_t cust_UART5;
GPIO_t cust_GPIO_RX_UART5;
GPIO_t cust_GPIO_TX_UART5;
#endif

int alt_main()
{
	/* Initialization */
#ifdef __cplusplus
	Ini_GPIO();
	Ini_UART();

	for(uint16_t i=0; i<64; i++){
		cust_USART3.CreateSendPacket(i, i);
	}

	while (1)
	{
		if(cust_GPIO_Bt_User.Read()){ //pushbutton
			cust_USART3.SendBufTx(64);
			LL_GPIO_SetOutputPin(GPIOD, LL_GPIO_PIN_12); //Led
			while (cust_GPIO_Bt_User.Read()) {}
		}
		else
			LL_GPIO_ResetOutputPin(GPIOD, LL_GPIO_PIN_12); //Led

		switch(cust_USART1.StatusRx()){
		case STATUS_RX_EMPTY:
			break;
		case STATUS_RX_FULL_RX_BUF_EMPTY:
			cust_USART2.CopyDataTx(cust_USART1.AdrRx(), TX_SIZE);
			cust_USART1.ClearRx();
			cust_USART2.SendBufTx(TX_SIZE);
			break;
		case STATUS_RX_EMPTY_RX_BUF_ANY:
			break;
		case STATUS_RX_EMPTY_RX_BUF_FULL:
			cust_USART2.CopyDataTx(cust_USART1.AdrRx(), TX_SIZE);
			cust_USART1.ClearRxReserve();
			cust_USART2.SendBufTx(TX_SIZE);
			break;
		}
		/* Super loop */
	}
#else
	while (1)
	{

		/* Super loop */
	}
#endif
}

void alt_UART_IRQ(USART_TypeDef *uart){
#ifdef __cplusplus
	if(uart == USART1){
		if(cust_USART1.callBackFunc)
			cust_USART1.callBackFunc();
	}
	else if(uart == USART2){
		if(cust_USART2.callBackFunc)
			cust_USART2.callBackFunc();
	}
	else if(uart == USART3){
		if(cust_USART3.callBackFunc)
			cust_USART3.callBackFunc();
	}
	else if(uart == UART5){
		if(cust_UART5.callBackFunc)
			cust_UART5.callBackFunc();
	}
#endif
}

#ifdef __cplusplus

void Ini_GPIO(){

	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);

	cust_GPIO_Bt_User.InitInput(GPIOA,LL_GPIO_PIN_0,LL_GPIO_MODE_INPUT,LL_GPIO_PULL_NO);

	cust_GPIO_RX_USART1.EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

	cust_GPIO_RX_USART1.SetGPIO(GPIOA);
	cust_GPIO_RX_USART1.SetPin(LL_GPIO_PIN_10);
	cust_GPIO_RX_USART1.SetMode(LL_GPIO_MODE_ALTERNATE);
	cust_GPIO_RX_USART1.SetSpeed(LL_GPIO_SPEED_FREQ_VERY_HIGH);
	cust_GPIO_RX_USART1.SetOutputType(LL_GPIO_OUTPUT_PUSHPULL);
	cust_GPIO_RX_USART1.SetPull(LL_GPIO_PULL_NO);
	cust_GPIO_RX_USART1.SetAlternate(LL_GPIO_AF_7);

	cust_GPIO_RX_USART1.Init();

	cust_GPIO_TX_USART1.EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

	cust_GPIO_TX_USART1.SetGPIO(GPIOA);
	cust_GPIO_TX_USART1.SetPin(LL_GPIO_PIN_9);
	cust_GPIO_TX_USART1.SetMode(LL_GPIO_MODE_ALTERNATE);
	cust_GPIO_TX_USART1.SetSpeed(LL_GPIO_SPEED_FREQ_VERY_HIGH);
	cust_GPIO_TX_USART1.SetOutputType(LL_GPIO_OUTPUT_PUSHPULL);
	cust_GPIO_TX_USART1.SetPull(LL_GPIO_PULL_NO);
	cust_GPIO_TX_USART1.SetAlternate(LL_GPIO_AF_7);

	cust_GPIO_TX_USART1.Init();

	cust_GPIO_RX_USART2.Init(GPIOA,LL_GPIO_PIN_3,LL_GPIO_MODE_ALTERNATE,LL_GPIO_SPEED_FREQ_VERY_HIGH,LL_GPIO_OUTPUT_PUSHPULL,LL_GPIO_PULL_NO,LL_GPIO_AF_7);
	cust_GPIO_TX_USART2.Init(GPIOA,LL_GPIO_PIN_2,LL_GPIO_MODE_ALTERNATE,LL_GPIO_SPEED_FREQ_VERY_HIGH,LL_GPIO_OUTPUT_PUSHPULL,LL_GPIO_PULL_NO,LL_GPIO_AF_7);

	cust_GPIO_RX_USART3.Init(GPIOB,LL_GPIO_PIN_10,LL_GPIO_MODE_ALTERNATE,LL_GPIO_SPEED_FREQ_VERY_HIGH,LL_GPIO_OUTPUT_PUSHPULL,LL_GPIO_PULL_NO,LL_GPIO_AF_7);
	cust_GPIO_TX_USART3.Init(GPIOB,LL_GPIO_PIN_11,LL_GPIO_MODE_ALTERNATE,LL_GPIO_SPEED_FREQ_VERY_HIGH,LL_GPIO_OUTPUT_PUSHPULL,LL_GPIO_PULL_NO,LL_GPIO_AF_7);

	cust_GPIO_RX_UART5.Init(GPIOD,LL_GPIO_PIN_2,LL_GPIO_MODE_ALTERNATE,LL_GPIO_SPEED_FREQ_VERY_HIGH,LL_GPIO_OUTPUT_PUSHPULL,LL_GPIO_PULL_NO,LL_GPIO_AF_8);
	cust_GPIO_TX_UART5.Init(GPIOC,LL_GPIO_PIN_12,LL_GPIO_MODE_ALTERNATE,LL_GPIO_SPEED_FREQ_VERY_HIGH,LL_GPIO_OUTPUT_PUSHPULL,LL_GPIO_PULL_NO,LL_GPIO_AF_8);

}

void Ini_UART(){

	cust_USART1.SetUART(USART1);
	cust_USART1.SetBaudRate(9600);
	cust_USART1.SetDataWidth(LL_USART_DATAWIDTH_8B);
	cust_USART1.SetStopBits(LL_USART_STOPBITS_1);
	cust_USART1.SetParity(LL_USART_PARITY_NONE);
	cust_USART1.SetTransferDirection(LL_USART_DIRECTION_TX_RX);
	cust_USART1.SetHardwareFlowControl(LL_USART_HWCONTROL_NONE);
	cust_USART1.SetOverSampling(LL_USART_OVERSAMPLING_16);
	cust_USART1.SetIRQ(USART1_IRQn);

	cust_USART1.Init();
	cust_USART1.SetCallBackFunc(&USART1_callback);

	cust_USART2.Init(USART2,115200,LL_USART_DATAWIDTH_8B,LL_USART_STOPBITS_1,LL_USART_PARITY_NONE,LL_USART_DIRECTION_TX_RX,
					 LL_USART_HWCONTROL_NONE,LL_USART_OVERSAMPLING_16,USART2_IRQn);
	cust_USART2.SetCallBackFunc(&USART2_callback);

	cust_USART3.Init(USART3,9600,LL_USART_DATAWIDTH_8B,LL_USART_STOPBITS_1,LL_USART_PARITY_NONE,LL_USART_DIRECTION_TX_RX,
						 LL_USART_HWCONTROL_NONE,LL_USART_OVERSAMPLING_16,USART3_IRQn);
	cust_USART3.SetCallBackFunc(&USART3_callback);

	cust_UART5.Init(UART5,115200,LL_USART_DATAWIDTH_8B,LL_USART_STOPBITS_1,LL_USART_PARITY_NONE,LL_USART_DIRECTION_TX_RX,
						 LL_USART_HWCONTROL_NONE,LL_USART_OVERSAMPLING_16,UART5_IRQn);
	cust_UART5.SetCallBackFunc(&UART5_callback);
}

void USART1_callback()
{
	if(READ_BIT(USART1->SR,USART_SR_RXNE)){
		cust_USART1.AddReceiveData((uint8_t)(USART1->DR & 0x00FF));
	}
	else
		(void) USART1->DR;
}

void USART2_callback()
{
	if(READ_BIT(USART2->SR,USART_SR_RXNE)){
		cust_USART2.AddReceiveData((uint8_t)(USART2->DR & 0x00FF));
	}
	else
		(void) USART2->DR;
}

void USART3_callback()
{
	if(READ_BIT(USART3->SR,USART_SR_RXNE)){
		cust_USART3.AddReceiveData((uint8_t)(USART3->DR & 0x00FF));
	}
	else
		(void) USART3->DR;
}

void UART5_callback()
{
	if(READ_BIT(UART5->SR,USART_SR_RXNE)){
		cust_UART5.AddReceiveData((uint8_t)(UART5->DR & 0x00FF));
	}
	else
		(void) UART5->DR;
}
#endif
