#include "renesas/usb_cdc.h"

static uint8_t cdc_buffer[8];
static volatile uint32_t cdc_recv_bytes = 0;
static volatile uint32_t cdc_recv_index = 0;

void cdc_setup(void)
{
  USBCDC_Init();
}

void cdc_send(char *s)
{
  USBCDC_WriteString(s);
}

static void cdc_callback(USB_ERR err, uint32_t num)
{
  if (err == USB_ERR_OK && num > 0) {
    cdc_recv_index = 0;
    cdc_recv_bytes = num;
  }
}

char cdc_recv(void)
{
  char c;

  if (cdc_recv_bytes > 0) {
    c = cdc_buffer[cdc_recv_index];
    cdc_recv_index++;
    cdc_recv_bytes--;
  } else {
    if (USBCDC_IsConnected()) {
      /* Always call, might return USB_ERR_BUSY which can be ignored. */
      USBCDC_Read_Async(8, cdc_buffer, cdc_callback);
    }
    c = '\0';
  }

  return c;
}

