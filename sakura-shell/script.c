#include "opcode.h"
#include "timer.h"
#include "uart.h"

#define SCRIPT_MAX 100

static opcode_t script[SCRIPT_MAX];

static unsigned int script_pointer = 0;
static unsigned int script_running = 0;

void script_clear(void)
{
  int i;
  for (i = 0; i < SCRIPT_MAX; i++) {
    script[i] = OPCODE_NONE;
  }
  script_pointer = 0;
  script_running = 0;
}

void script_stop(void)
{
  script_running = 0;
}

void script_run(void)
{
  script_running = 1;
}

void script_execute(void)
{
  if (script_running == 0) {
    return;
  }

  if (timer_read() > 0) {
    return;
  }

  /* Possibly keep running until end of script, except delays. */
  while (script_pointer < SCRIPT_MAX) {
    timer_set(opcode_execute(script[script_pointer]) / 10);
    script_pointer++;
    if (timer_read() > 0) {
      return;
    }
  }
  script_pointer = 0;
}

void script_dump(void)
{
  int i;
  char output[7];

  for (i = 0; i < SCRIPT_MAX; i++) {
    if (script[i] != OPCODE_NONE) {
      output[0] = '\r';
      output[1] = '\n';
      output[2] = (i / 10) + 0x30;
      output[3] = (i % 10) + 0x30;
      output[4] = ':';
      output[5] = ' ';
      output[6] = '\0';
      uart0_send(output);

      uart0_send(opcode_command(script[i]));

      if ((int)script_pointer == i) {
        output[0] = ' ';
        output[1] = '<';
        output[2] = '-';
        output[3] = '-';
        output[4] = '\0';
        uart0_send(output);
      }
    }
  }
}

void script_state_print(void)
{
  if (script_running) {
    uart0_send("\r\nrunning");
  } else {
    uart0_send("\r\nstopped");
  }
}

void script_program(int line_no, opcode_t op)
{
  script[line_no] = op;
}

