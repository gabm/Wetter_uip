/*
 * net.c
 *
 *  Created on: 22.03.2012
 *      Author: gabm
 */

#include "net.h"

void net_init()
{
	com_init();
}
void net_notify()
{
	cbi(COM_INT_PORT, COM_INT_PIN);
}
unsigned char net_receive()
{
	if (!com_check())
		return NET_NOTHING;

	com_connect();
	unsigned char cCommand = com_get_command();

	switch (cCommand)
	{
	case (CMD_MA_OUT):
			com_receive_chunk(&com_receive_buffer_size);
			com_disconnect();
			return NET_RECEIVED;
			break;
	case (CMD_MA_REQ):
			sbi(COM_INT_PORT, COM_INT_PIN);
			com_config(BUS_OUTPUT);
			com_send_chunk(com_send_buffer_size);
			com_disconnect();
			return NET_SENT;
			break;
	}
	return NET_NOTHING;
}
