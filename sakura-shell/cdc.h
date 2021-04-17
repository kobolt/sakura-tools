#ifndef _CDC_H
#define _CDC_H

void cdc_setup(void);
void cdc_send(char *s);
char cdc_recv(void);

#endif /* _CDC_H */
