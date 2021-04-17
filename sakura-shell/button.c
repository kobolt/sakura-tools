#include <iodefine.h>
#include "button.h"
#include "cdc.h"

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
    cdc_send("\r\nreleased");
  } else {
    cdc_send("\r\npressed");
  }
}

