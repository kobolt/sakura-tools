#include "opcode.h"
#include "led.h"
#include "script.h"

char *opcode_command(opcode_t op)
{
  switch (op) {
  case OPCODE_SLEEP_10:     return "sleep 10";
  case OPCODE_SLEEP_50:     return "sleep 50";
  case OPCODE_SLEEP_100:    return "sleep 100";
  case OPCODE_SLEEP_500:    return "sleep 500";
  case OPCODE_SLEEP_1000:   return "sleep 1000";
  case OPCODE_D1_OFF:       return "d1 off";
  case OPCODE_D1_ON:        return "d1 on";
  case OPCODE_D1_TOGGLE:    return "d1 toggle";
  case OPCODE_D2_OFF:       return "d2 off";
  case OPCODE_D2_ON:        return "d2 on";
  case OPCODE_D2_TOGGLE:    return "d2 toggle";
  case OPCODE_D3_OFF:       return "d3 off";
  case OPCODE_D3_ON:        return "d3 on";
  case OPCODE_D3_TOGGLE:    return "d3 toggle";
  case OPCODE_D4_OFF:       return "d4 off";
  case OPCODE_D4_ON:        return "d4 on";
  case OPCODE_D4_TOGGLE:    return "d4 toggle";
  case OPCODE_SCRIPT_RUN:   return "run";
  case OPCODE_SCRIPT_STOP:  return "stop";
  case OPCODE_SCRIPT_DUMP:  return "dump";
  case OPCODE_SCRIPT_CLEAR: return "clear";
  case OPCODE_SCRIPT_STATE: return "state";
  default: 
    return "";
  }
}

unsigned int opcode_execute(opcode_t op)
{
  switch (op) {
  case OPCODE_NONE:
    break;

  case OPCODE_SLEEP_10:
    return 10;

  case OPCODE_SLEEP_50:
    return 50;

  case OPCODE_SLEEP_100:
    return 100;

  case OPCODE_SLEEP_500:
    return 500;

  case OPCODE_SLEEP_1000:
    return 1000;

  case OPCODE_D1_OFF:
    led_d1_command(LED_OFF);
    break;

  case OPCODE_D1_ON:
    led_d1_command(LED_ON);
    break;

  case OPCODE_D1_TOGGLE:
    led_d1_command(LED_TOGGLE);
    break;

  case OPCODE_D2_OFF:
    led_d2_command(LED_OFF);
    break;

  case OPCODE_D2_ON:
    led_d2_command(LED_ON);
    break;

  case OPCODE_D2_TOGGLE:
    led_d2_command(LED_TOGGLE);
    break;

  case OPCODE_D3_OFF:
    led_d3_command(LED_OFF);
    break;

  case OPCODE_D3_ON:
    led_d3_command(LED_ON);
    break;

  case OPCODE_D3_TOGGLE:
    led_d3_command(LED_TOGGLE);
    break;

  case OPCODE_D4_OFF:
    led_d4_command(LED_OFF);
    break;

  case OPCODE_D4_ON:
    led_d4_command(LED_ON);
    break;

  case OPCODE_D4_TOGGLE:
    led_d4_command(LED_TOGGLE);
    break;

  case OPCODE_SCRIPT_RUN:
    script_run();
    break;

  case OPCODE_SCRIPT_STOP:
    script_stop();
    break;

  case OPCODE_SCRIPT_DUMP:
    script_dump();
    break;

  case OPCODE_SCRIPT_CLEAR:
    script_clear();
    break;

  case OPCODE_SCRIPT_STATE:
    script_state_print();
    break;

  default:
    break;
  }

  return 0; /* No time to sleep. */
}

