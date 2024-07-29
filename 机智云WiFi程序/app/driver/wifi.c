/*
 * wifi.c
 *
 *  Created on: 2019Äê8ÔÂ12ÈÕ
 *      Author: 21235
 */
#include "driver/wifi.h"
#include "driver/uart.h"
#include "gizwits_product.h"
#include "gizwits_protocol.h"

void sendToMcu(void) {
	unsigned char i;

	for(i =0;i<sizeof(sendDataPoint_t);i++){

		uart_tx_one_char_no_wait(UART0,sendDataPointer[i]);
	}
	uart_tx_one_char_no_wait(UART0,0x0d);
	uart_tx_one_char_no_wait(UART0,0x0a);
}




