/*
 * com_neu.h
 *
 *  Created on: 19.03.2012
 *      Author: gabm
 */

#ifndef COM_H_
#define COM_H_

#include <avr/io.h>
#include <util/delay.h>
#include "util.h"
#include "buffers.h"


#define BUS_DDR DDRC
#define BUS_PORT PORTC
#define BUS_PIN PINC

#define COM_SCK_IN PC4
#define COM_SCK_OUT PC5


#define COM_INT_DDR DDRB
#define COM_INT_PORT PORTB
#define COM_INT_PIN PB0


#define CMD_PIN PIND
#define CMD_PORT PORTD
#define CMD_DDR DDRD

#define CMD_PIN_0 PD0
#define CMD_PIN_1 PD1

#define BUS_OUTPUT 0xFF
#define BUS_INPUT 0x00

#define BYTE_WAITING_TIME_US 200


#define CMD_MA_IDLE 0x00
#define CMD_MA_OUT 0x01
#define CMD_MA_REQ 0x02
#define CMD_END 0x03

void com_init();
void com_receive_chunk( uint8_t* uiLen );
void com_send_chunk(uint8_t uiLen);

void com_connect();
void com_disconnect();

void com_config(char cDirection);
char com_check();
unsigned char com_get_command();

#endif /* COM_H_ */
