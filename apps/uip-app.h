

#ifndef UIP_APP_H_
#define UIP_APP_H_

#include <avr/io.h>
#include "../net.h"
#include "../buffers.h"

#define LPORT 2069

#define UIP_APPCALL   uipAppCall
struct uipAppState {
  uint8_t state;
};
typedef struct uipAppState uip_tcp_appstate_t;






void uipAppInit(void);
void uipAppCall(void);

#endif
