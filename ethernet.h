/*
 * ethernet.h
 *
 *  Created on: 04.04.2012
 *      Author: gabm
 */

#ifndef ETHERNET_H_
#define ETHERNET_H_

#include "uip/uip.h"
#include "uip/uip_arp.h"
#include "hardware/enc28j60.h"
#include "apps-conf.h"
#include "avr/interrupt.h"
#include <avr/pgmspace.h>
#include "uip/clock.h"
#include "uip/timer.h"

#define HOST_IP1 192
#define HOST_IP2 168
#define HOST_IP3 0
#define HOST_IP4 50

#define ETH_INT_ENABLE  GICR |= (1<<INT0)
#define ETH_INT_DISABLE GICR &= ~(1<<INT0)

#define ETH_INT_ACTIVE          (!(PIND & _BV(PD2)))

extern struct timer periodic_timer;
extern struct timer arp_timer;
volatile extern uint8_t eth_data_present;

void ethernet_init();
void ethernet_handle();
void ethernet_notify(uint8_t i);

#endif /* ETHERNET_H_ */
