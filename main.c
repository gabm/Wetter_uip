#include <avr/io.h>
#include "net.h"
#include "ethernet.h"



/*---------------------------------------------------------------------------*/
int main(void) {
	//why do we need this?
	_delay_ms(1000);
	net_init();
	ethernet_init();
	clock_init();


	//enable ints
	sei();

  while(1) {
	  if (net_receive() == NET_RECEIVED)
		  ethernet_notify(0);
	  ethernet_handle();
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
