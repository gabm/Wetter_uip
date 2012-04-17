/*
 * com_neu.c
 *
 *  Created on: 19.03.2012
 *      Author: gabm
 */
#include "com.h"

unsigned char com_send_buffer[MAX_CHUNK_SIZE];
unsigned char com_receive_buffer[MAX_CHUNK_SIZE];
uint8_t com_send_buffer_size =0;
uint8_t com_receive_buffer_size =0;


void com_wait_low()
{
	loop_until_bit_is_clear(BUS_PIN, COM_SCK_IN);
}

void com_wait_high()
{
	loop_until_bit_is_set(BUS_PIN, COM_SCK_IN);
}

void com_send_ack()
{
	cbi(BUS_PORT,COM_SCK_OUT);
	com_wait_high();
	sbi(BUS_PORT,COM_SCK_OUT);
}
void com_mark_active_and_wait_ack()
{
	cbi(BUS_PORT,COM_SCK_OUT);
	com_wait_low();
	sbi(BUS_PORT, COM_SCK_OUT);
	com_wait_high();
}

unsigned char com_get_command()
{
	com_wait_low();
	unsigned char cCommand = CMD_PIN & 0x03;

	com_send_ack();
	return cCommand;
}


void com_connect()
{
	//SCK IN as input and pull up
	sbi(BUS_PORT, COM_SCK_IN);
	cbi(BUS_DDR, COM_SCK_IN);

	//SCK out as output and high
	sbi(BUS_PORT, COM_SCK_OUT);
	sbi(BUS_DDR, COM_SCK_OUT);

	//CMD as input and pull up
	cbi(CMD_DDR, CMD_PIN_0);
	sbi(CMD_PORT, CMD_PIN_0);

	cbi(CMD_DDR, CMD_PIN_1);
	sbi(CMD_PORT, CMD_PIN_1);

	com_config(BUS_INPUT);

	_delay_ms(10);
	com_wait_low();
	com_send_ack();
}

void com_disconnect()
{
	BUS_DDR = 0x00;
	BUS_PORT = 0xFF;

	cbi(CMD_DDR, CMD_PIN_0);
	sbi(CMD_PORT, CMD_PIN_0);

	cbi(CMD_DDR, CMD_PIN_1);
	sbi(CMD_PORT, CMD_PIN_1);

	_delay_ms(10);
}

void com_config(char cDirection)
{
	if (cDirection == BUS_OUTPUT)
	{
		BUS_DDR |= 0x0F;
		BUS_PORT &= ~(0x0F);
	} else {
		BUS_DDR &= ~(0x0F);
		BUS_PORT |= 0x0F;
	}
}

void com_init()
{
	DDRC = 0x00;
	PORTC = 0xFF;

	cbi(DDRB, PB1);
	sbi(PORTB, PB1);

	//initialize interrupt as high
	sbi(COM_INT_PORT, COM_INT_PIN);
	sbi(COM_INT_DDR, COM_INT_PIN);
}

void com_write_nibble(const unsigned char cData)
{
	BUS_PORT = (BUS_PORT & 0xF0) | (0x0F & cData);

	com_mark_active_and_wait_ack();
}

unsigned char com_read_nibble()
{
	unsigned char cResult = 0x00;
	com_wait_low();
	cResult |= (0x0F & BUS_PIN);

	com_send_ack();
	return cResult;
}

void com_write_byte(const unsigned char cData)
{
	com_write_nibble(cData >> 4);
	com_write_nibble(cData);
}

unsigned char com_read_byte()
{
	unsigned char cResult = 0x00;
	cResult |= (com_read_nibble() << 4);
	cResult |= com_read_nibble();
	return cResult;
}

void com_send_chunk(uint8_t uiLen)
{
	unsigned char* itr = com_send_buffer;
	com_write_byte(uiLen);

	for (uint8_t i =0; i<uiLen;i++)
	{
		com_write_byte(*itr);
		itr++;
	}
}

void com_receive_chunk( uint8_t* uiLen)
{
	//init and read first byte
	unsigned char* itr = com_receive_buffer;
	*uiLen = com_read_byte();

	//receive the proposed length of bytes
	uint8_t i=0;
	while(i < *uiLen)
	{
		*itr++ = com_read_byte();
		i++;
	}

}

char com_check()
{
	return bit_is_set(PINB, PB1);
}
