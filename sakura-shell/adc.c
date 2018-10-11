#include <iodefine.h>
#include "adc.h"
#include "uart.h"

void adc_setup(void)
{
  SYSTEM.PRCR.WORD = 0xa502; /* Enable writing to MSTP registers. */
  MSTP_S12AD       = 0;      /* Disable module-stop state for 12-bit A/D. */
  SYSTEM.PRCR.WORD = 0xa500; /* Disable writing to MSTP registers. */

  /* Set analog ports as inputs. */
  PORT4.PDR.BIT.B0 = 0;
  PORT4.PDR.BIT.B1 = 0;
  PORT4.PDR.BIT.B2 = 0;
  PORT4.PDR.BIT.B3 = 0;
  PORT4.PDR.BIT.B4 = 0;
  PORT4.PDR.BIT.B5 = 0;

  /* Set analog ports as general I/O pins. */
  PORT4.PMR.BIT.B0 = 0;
  PORT4.PMR.BIT.B1 = 0;
  PORT4.PMR.BIT.B2 = 0;
  PORT4.PMR.BIT.B3 = 0;
  PORT4.PMR.BIT.B4 = 0;
  PORT4.PMR.BIT.B5 = 0;

  S12AD.ADCSR.BIT.CKS  = 0b00; /* Clock: PCLK/8 */
  S12AD.ADCSR.BIT.ADIE = 0;    /* Disable interrupt generation. */
  S12AD.ADCSR.BIT.ADCS = 0;    /* Single scan mode. */

  S12AD.ADANS0.WORD = 0b0000000000111111; /* Select channels 0 to 5. */
  S12AD.ADANS1.WORD = 0;

  S12AD.ADCER.BIT.ACE    = 0; /* Disable automatic clearing. */
  S12AD.ADCER.BIT.ADRFMT = 0; /* A/D data is flush-right. */

  MPC.PWPR.BIT.B0WI  = 0; /* Enable the PFSWE modification. */
  MPC.PWPR.BIT.PFSWE = 1; /* Disable the PFS register protect. */
  MPC.P40PFS.BIT.ASEL = 1; /* Use Port 40 as analog pin. */
  MPC.P41PFS.BIT.ASEL = 1; /* Use Port 41 as analog pin. */
  MPC.P42PFS.BIT.ASEL = 1; /* Use Port 42 as analog pin. */
  MPC.P43PFS.BIT.ASEL = 1; /* Use Port 43 as analog pin. */
  MPC.P44PFS.BIT.ASEL = 1; /* Use Port 44 as analog pin. */
  MPC.P45PFS.BIT.ASEL = 1; /* Use Port 45 as analog pin. */
  MPC.PWPR.BIT.PFSWE = 0; /* Enable the PFS register protect. */
  MPC.PWPR.BIT.B0WI  = 1; /* Disable the PFSWE modification. */
}

void adc_data_print(void)
{
  char adc_no;
  char text[13];
  short value;

  /* Start A/D conversion. */
  S12AD.ADCSR.BIT.ADST = 1;

  /* Wait for A/D conversion to finish; ADST bit becomes 0. */
  while (S12AD.ADCSR.BIT.ADST) {
    asm("nop");
  }

  for (adc_no = 0; adc_no <= 5; adc_no++) {
    uart0_send("\r\nAN");
    text[0] = adc_no + 0x30;
    text[1] = '\0';
    uart0_send(text);
    uart0_send(": ");
    switch (adc_no) {
    case 0:
      value = S12AD.ADDR0;
      break;
    case 1:
      value = S12AD.ADDR1;
      break;
    case 2:
      value = S12AD.ADDR2;
      break;
    case 3:
      value = S12AD.ADDR3;
      break;
    case 4:
      value = S12AD.ADDR4;
      break;
    case 5:
      value = S12AD.ADDR5;
      break;
    }
    text[0]  = ((value >> 11) & 0x1) + 0x30;
    text[1]  = ((value >> 10) & 0x1) + 0x30;
    text[2]  = ((value >> 9)  & 0x1) + 0x30;
    text[3]  = ((value >> 8)  & 0x1) + 0x30;
    text[4]  = ((value >> 7)  & 0x1) + 0x30;
    text[5]  = ((value >> 6)  & 0x1) + 0x30;
    text[6]  = ((value >> 5)  & 0x1) + 0x30;
    text[7]  = ((value >> 4)  & 0x1) + 0x30;
    text[8]  = ((value >> 3)  & 0x1) + 0x30;
    text[9]  = ((value >> 2)  & 0x1) + 0x30;
    text[10] = ((value >> 1)  & 0x1) + 0x30;
    text[11] = ( value        & 0x1) + 0x30;
    text[12] = '\0';
    uart0_send(text);
  }
}

