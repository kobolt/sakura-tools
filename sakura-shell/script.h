#ifndef _SCRIPT_H
#define _SCRIPT_H

#include "opcode.h"

void script_clear(void);
void script_stop(void);
void script_run(void);
void script_execute(void);
void script_dump(void);
void script_state_print(void);
void script_program(int line_no, opcode_t op);

#endif /* _SCRIPT_ */
