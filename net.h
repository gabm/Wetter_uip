/*
 * net.h
 *
 *  Created on: 22.03.2012
 *      Author: gabm
 */

#ifndef NET_H_
#define NET_H_
#include "com.h"
#include "buffers.h"

#define NET_NOTHING 0
#define NET_RECEIVED 1
#define NET_SENT 2

unsigned char net_receive();
void net_notify();
void net_init();

#endif /* NET_H_ */
