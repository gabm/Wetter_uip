#include "uip-app.h"
#include "../uip/uip.h"

void uipAppInit(void) {
  uip_listen(HTONS(LPORT));
}

void acked()
{
	//clear tcp-transmit buffer
	//this is the com receive buffer
	//our data received from the other uC
	com_receive_buffer_size =0;
}

void newdata()
{
	uint16_t len = uip_datalen();

	unsigned char* pSource = (unsigned char *)uip_appdata;
	unsigned char* pTarget = com_send_buffer;
	for (uint8_t i=0; i<len; i++)
		*pTarget++ = *pSource++;

	com_send_buffer_size = len;
	net_notify();

}
void senddata(void)
{
	if (com_receive_buffer_size !=0)
		uip_send(com_receive_buffer, com_receive_buffer_size);
}

void uipAppCall(void) {


	if(uip_acked()) {
		acked();
	}

	if(uip_newdata()) {
		newdata();
	}

	if(uip_rexmit() || uip_poll())
	{
		senddata();
	}
	if (uip_timedout())
	{
		uip_close();
	}
}
