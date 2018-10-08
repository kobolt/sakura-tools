#include "uart.h"
#include "script.h"
#include "opcode.h"

#define COMMAND_MAX 20

static int command_match(char *cmd, signed char len, char *pattern)
{
  int i = 0;
  for (i = 0; pattern[i] != '\0'; i++) {
    if (i == len) {
      return 0;
    }
    if (cmd[i] != pattern[i]) {
      return 0;
    }
  }
  if (len == i) {
    return 1;
  } else {
    return 0;
  }
}

static opcode_t command_eval(char *cmd, signed char len)
{
  int script_line;
  opcode_t op = OPCODE_EVAL_ERROR;

  if (len <= 0) {
    return OPCODE_NONE;
  }

  if (cmd[0] >= 0x30 && cmd[0] <= 0x39) {
    if (cmd[1] >= 0x30 && cmd[1] <= 0x39) {
      if (cmd[2] == ' ') {
        script_line = ((cmd[0] - 0x30) * 10) + (cmd[1] - 0x30);
        op = command_eval(&cmd[3], len - 3);
      } else {
        script_line = ((cmd[0] - 0x30) * 10) + (cmd[1] - 0x30);
        op = command_eval(&cmd[2], len - 2);
      }

    } else {
      if (cmd[1] == ' ') {
        script_line = cmd[0] - 0x30;
        op = command_eval(&cmd[2], len - 2);
      } else {
        script_line = cmd[0] - 0x30;
        op = command_eval(&cmd[1], len - 1);
      }
    }

    if (op == OPCODE_EVAL_ERROR) {
      return OPCODE_EVAL_ERROR;
    } else {
      script_program(script_line, op);
      return OPCODE_NONE;
    }
  }

  if (command_match(cmd, len, opcode_command(OPCODE_SLEEP_10))) {
    return OPCODE_SLEEP_10;
  } else if (command_match(cmd, len, opcode_command(OPCODE_SLEEP_50))) {
    return OPCODE_SLEEP_50;
  } else if (command_match(cmd, len, opcode_command(OPCODE_SLEEP_100))) {
    return OPCODE_SLEEP_100;
  } else if (command_match(cmd, len, opcode_command(OPCODE_SLEEP_500))) {
    return OPCODE_SLEEP_500;
  } else if (command_match(cmd, len, opcode_command(OPCODE_SLEEP_1000))) {
    return OPCODE_SLEEP_1000;
  } else if (command_match(cmd, len, opcode_command(OPCODE_D1_OFF))) {
    return OPCODE_D1_OFF;
  } else if (command_match(cmd, len, opcode_command(OPCODE_D1_ON))) {
    return OPCODE_D1_ON;
  } else if (command_match(cmd, len, opcode_command(OPCODE_D1_TOGGLE))) {
    return OPCODE_D1_TOGGLE;
  } else if (command_match(cmd, len, opcode_command(OPCODE_D2_OFF))) {
    return OPCODE_D2_OFF;
  } else if (command_match(cmd, len, opcode_command(OPCODE_D2_ON))) {
    return OPCODE_D2_ON;
  } else if (command_match(cmd, len, opcode_command(OPCODE_D2_TOGGLE))) {
    return OPCODE_D2_TOGGLE;
  } else if (command_match(cmd, len, opcode_command(OPCODE_D3_OFF))) {
    return OPCODE_D3_OFF;
  } else if (command_match(cmd, len, opcode_command(OPCODE_D3_ON))) {
    return OPCODE_D3_ON;
  } else if (command_match(cmd, len, opcode_command(OPCODE_D3_TOGGLE))) {
    return OPCODE_D3_TOGGLE;
  } else if (command_match(cmd, len, opcode_command(OPCODE_D4_OFF))) {
    return OPCODE_D4_OFF;
  } else if (command_match(cmd, len, opcode_command(OPCODE_D4_ON))) {
    return OPCODE_D4_ON;
  } else if (command_match(cmd, len, opcode_command(OPCODE_D4_TOGGLE))) {
    return OPCODE_D4_TOGGLE;
  } else if (command_match(cmd, len, opcode_command(OPCODE_BUTTON))) {
    return OPCODE_BUTTON;
  } else if (command_match(cmd, len, opcode_command(OPCODE_SCRIPT_RUN))) {
    return OPCODE_SCRIPT_RUN;
  } else if (command_match(cmd, len, opcode_command(OPCODE_SCRIPT_STOP))) {
    return OPCODE_SCRIPT_STOP;
  } else if (command_match(cmd, len, opcode_command(OPCODE_SCRIPT_DUMP))) {
    return OPCODE_SCRIPT_DUMP;
  } else if (command_match(cmd, len, opcode_command(OPCODE_SCRIPT_CLEAR))) {
    return OPCODE_SCRIPT_CLEAR;
  } else if (command_match(cmd, len, opcode_command(OPCODE_SCRIPT_STATE))) {
    return OPCODE_SCRIPT_STATE;
  }

  return OPCODE_EVAL_ERROR;
}

void command_loop(void)
{
  char c;
  char echo[2];
  char command[COMMAND_MAX];
  signed char command_len;
  opcode_t op;

  script_clear();
  
  command_len = 0;

  while(1) {
    asm("wait");

    script_execute();

    c = uart0_recv();
    if (c == '\0') {
      continue;
    }

    /* Handling of backspace. */
    if (c == 0x7f) {
      command_len--;
      if (command_len < 0) {
        command_len = 0;
        continue;
      }
      
      echo[0] = 0x08;
      echo[1] = '\0';
      uart0_send(echo);
      echo[0] = ' ';
      echo[1] = '\0';
      uart0_send(echo);
      echo[0] = 0x08;
      echo[1] = '\0';
      uart0_send(echo);

      continue;
    }

    if (c == '\r') {
      op = command_eval(command, command_len);
      command_len = 0;
      
      if (op == OPCODE_EVAL_ERROR) {
        uart0_send("\r\nsyntax error!");
      } else {
        opcode_execute(op);
        /* Any returned delay is just ignored. */
      }

      uart0_send("\r\nsakura> ");
    } else {
      command[command_len] = c;
      command_len++;
      if (command_len >= COMMAND_MAX) {
        command_len = 0;
      }

      echo[0] = c;
      echo[1] = '\0';
      uart0_send(echo);
    }
  }
}

