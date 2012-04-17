/*
 * clock-arch.c
 *
 *  Created on: 04.04.2012
 *      Author: gabm
 */


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>

#include "clock-arch.h"

//Counted time
clock_time_t clock_datetime = 0;

//Overflow itnerrupt
ISR(TIMER0_OVF_vect)
{
        clock_datetime += 1;
        TIFR |= (1<<TOV0);
}

//Initialise the clock
void clock_init(){
        //Activate overflow interrupt for timer0
        TIMSK |= (1<<TOIE0);

        //Use prescaler 1024
        TCCR0 |= ((1<<CS02)|(1<<CS00));

}

//Return time
clock_time_t clock_time(){
        clock_time_t time;

        cbi(TIMSK, TOIE0);
        time = clock_datetime;
        sbi(TIMSK, TOIE0);

        return time;
}
