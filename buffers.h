/*
 * buffers.h
 *
 *  Created on: 04.04.2012
 *      Author: gabm
 */

#ifndef BUFFERS_H_
#define BUFFERS_H_


#define MAX_CHUNK_SIZE 13

extern unsigned char com_receive_buffer[MAX_CHUNK_SIZE];
extern unsigned char com_send_buffer[MAX_CHUNK_SIZE];

extern uint8_t com_send_buffer_size;
extern uint8_t com_receive_buffer_size;

#endif /* BUFFERS_H_ */
