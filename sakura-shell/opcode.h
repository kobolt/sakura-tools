#ifndef _OPCODE_H
#define _OPCODE_H

typedef enum {
  OPCODE_NONE         = 0x0,

  OPCODE_EVAL_ERROR   = 0x1,

  OPCODE_SLEEP_10     = 0x10,
  OPCODE_SLEEP_50     = 0x11,
  OPCODE_SLEEP_100    = 0x12,
  OPCODE_SLEEP_500    = 0x13,
  OPCODE_SLEEP_1000   = 0x14,

  OPCODE_D1_OFF       = 0x20,
  OPCODE_D1_ON        = 0x21,
  OPCODE_D1_TOGGLE    = 0x22,

  OPCODE_D2_OFF       = 0x30,
  OPCODE_D2_ON        = 0x31,
  OPCODE_D2_TOGGLE    = 0x32,

  OPCODE_D3_OFF       = 0x40,
  OPCODE_D3_ON        = 0x41,
  OPCODE_D3_TOGGLE    = 0x42,

  OPCODE_D4_OFF       = 0x50,
  OPCODE_D4_ON        = 0x51,
  OPCODE_D4_TOGGLE    = 0x52,

  OPCODE_BUTTON       = 0x60,
  OPCODE_ADC          = 0x61,

  OPCODE_SCRIPT_RUN   = 0x101,
  OPCODE_SCRIPT_STOP  = 0x102,
  OPCODE_SCRIPT_DUMP  = 0x103,
  OPCODE_SCRIPT_CLEAR = 0x104,
  OPCODE_SCRIPT_STATE = 0x105,

} opcode_t;

char *opcode_command(opcode_t op);
unsigned int opcode_execute(opcode_t op);

#endif /* _OPCODE_H */
