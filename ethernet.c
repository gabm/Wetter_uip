/*
 * ethernet.c
 *
 *  Created on: 04.04.2012
 *      Author: gabm
 */
#include "ethernet.h"

#define BUF ((struct uip_eth_hdr *)&uip_buf[0])

volatile uint8_t eth_data_present =0;

struct timer periodic_timer;
struct timer arp_timer;

void ethernet_notify(uint8_t i)
{
	  uip_poll_conn(&uip_conns[i]);
	  if(uip_len > 0) {
		  uip_arp_out();
	  	  enc28j60PacketSend(uip_len,&uip_buf[0]);
	  }
}

void ethernet_init()
{
	timer_set(&periodic_timer, CLOCK_SECOND / 2);
	timer_set(&arp_timer, CLOCK_SECOND * 10);


	uip_ipaddr_t ipaddr;
	 uip_init();
	 uip_arp_init();
	 memcpy_P(uip_ethaddr.addr, PSTR("\xAC\xDE\x48\xFD\x0F\xD0"), 6);

	 uip_ipaddr(ipaddr, HOST_IP1, HOST_IP2, HOST_IP3, HOST_IP4);

	 uip_sethostaddr(ipaddr);
	 uip_ipaddr(ipaddr, 255,255,255,0);
	 uip_setnetmask(ipaddr);

	 enc28j60Init();
	 uipAppInit();

	 sbi(PORTD,PD2);
	 cbi(DDRD,PD2);

	 eth_data_present =0;
	 ETH_INT_ENABLE;
}

void ethernet_handle_timer()
{
	if(timer_expired(&periodic_timer)) {
		timer_reset(&periodic_timer);


	    for(uint8_t i = 0; i < UIP_CONNS; i++) {
	    	uip_periodic(i);
	        if(uip_len > 0) {
	        	uip_arp_out();
	        	enc28j60PacketSend(uip_len,&uip_buf[0]);
	        }
	    }
	    if(timer_expired(&arp_timer)) {
	    	timer_reset(&arp_timer);
	        uip_arp_timer();
	    }
	}
}

void ethernet_handle_pkgs()
{
	if (!eth_data_present)
		return;

	while (ETH_INT_ACTIVE)
	{
		uip_len = enc28j60PacketReceive(UIP_CONF_BUFFER_SIZE, &uip_buf[0]);
		if(uip_len > 0)
		{
			if(BUF->type == htons(UIP_ETHTYPE_IP)) {
				uip_arp_ipin();
				uip_input();
				if(uip_len > 0) {
					uip_arp_out();
					enc28j60PacketSend(uip_len,&uip_buf[0]);
				}
			} else if(BUF->type == htons(UIP_ETHTYPE_ARP)) {
				uip_arp_arpin();
				if(uip_len > 0) {
					enc28j60PacketSend(uip_len,&uip_buf[0]);
				}
			}
		}
	}
	eth_data_present =0;
	ETH_INT_ENABLE;
}

void ethernet_handle()
{
	ethernet_handle_timer();
	ethernet_handle_pkgs();
}

ISR (INT0_vect)
{
	eth_data_present = 1;
	ETH_INT_DISABLE;
}
