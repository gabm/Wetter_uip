/*
 * UDP-app.c
 *
 *  Created on: 03.04.2012
 *      Author: gabm
 */
/*#include "UDP-app.h"
#include "../uip/uip.h"

void UDP_APP_appcall(void)
{
	if(uip_udp_conn->rport == HTONS(50000)) {
		if(uip_poll()) {
			//check_entries();
	    }
	    if(uip_newdata()) {
	      //new data in uip_appdata
	    	uip_udp_send(uip_datalen());
	    }
	  }
}

void UDP_APP_init()
{
	 uip_ipaddr_t addr;
	 struct uip_udp_conn *c;

	 uip_ipaddr(&addr, 192,168,1,1);
	 c = uip_udp_new(&addr, HTONS(50000));
	 if(c != NULL) {
	   uip_udp_bind(c, HTONS(50000));
	 }
}*/
