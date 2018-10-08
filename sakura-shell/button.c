#include <iodefine.h>
#include "button.h"
#include "uart.h"

#define BUTTON_PIN PORTA.PDR.BIT.B7
#define BUTTON     PORTA.PIDR.BIT.B7

void button_setup(void)
{
  /* Set button pin to input mode. */
  BUTTON_PIN = 0;
}

void button_state_print(void)
{
  if (BUTTON) {
    uart0_send("\r\nreleased");
  } else {
    uart0_send("\r\npressed");
  }
}

