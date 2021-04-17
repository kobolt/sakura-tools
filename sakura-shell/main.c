#include "led.h"
#include "button.h"
#include "adc.h"
#include "cdc.h"
#include "uart.h"
#include "timer.h"
#include "command.h"

static void hardware_init(void)
{
  /* Disable interrupts */
  asm("clrpsw i");

  uart0_setup();
  timer_setup();
  led_setup();
  button_setup();
  adc_setup();
  cdc_setup();

  /* Enable interrupts */
  asm("setpsw i");
}

int main(void)
{
  hardware_init();
  command_loop();
  return 0;
}

