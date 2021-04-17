
TOOL_PATH:=/opt/gcc-rx-elf/bin

CFLAGS = -c -O2 -ffunction-sections -fdata-sections -mcpu=rx600 -I. -Icommon -Wall -Wextra
LDFLAGS = -Wl,--gc-sections -nostartfiles

sakura.bin: sakura.elf
	$(TOOL_PATH)/rx-elf-objcopy -O binary $^ $@

sakura.elf: crt0.o stubs.o main.o led.o button.o adc.o uart.o timer.o script.o opcode.o command.o cdc.o usbdescriptors.o usb_hal.o usb_core.o usb_cdc.o
	$(TOOL_PATH)/rx-elf-gcc $(LDFLAGS) -T common/sakura_rx.ld $^ -o $@

crt0.o: common/sakura_crt0.S
	$(TOOL_PATH)/rx-elf-gcc $(CFLAGS) $^ -o $@

stubs.o: common/sakura_stubs.c
	$(TOOL_PATH)/rx-elf-gcc $(CFLAGS) $^ -o $@

led.o: led.c
	$(TOOL_PATH)/rx-elf-gcc $(CFLAGS) $^ -o $@

button.o: button.c
	$(TOOL_PATH)/rx-elf-gcc $(CFLAGS) $^ -o $@

adc.o: adc.c
	$(TOOL_PATH)/rx-elf-gcc $(CFLAGS) $^ -o $@

timer.o: timer.c
	$(TOOL_PATH)/rx-elf-gcc $(CFLAGS) $^ -o $@

uart.o: uart.c
	$(TOOL_PATH)/rx-elf-gcc $(CFLAGS) $^ -o $@

script.o: script.c
	$(TOOL_PATH)/rx-elf-gcc $(CFLAGS) $^ -o $@

opcode.o: opcode.c
	$(TOOL_PATH)/rx-elf-gcc $(CFLAGS) $^ -o $@

command.o: command.c
	$(TOOL_PATH)/rx-elf-gcc $(CFLAGS) $^ -o $@

cdc.o: cdc.c
	$(TOOL_PATH)/rx-elf-gcc $(CFLAGS) $^ -o $@

main.o: main.c
	$(TOOL_PATH)/rx-elf-gcc $(CFLAGS) $^ -o $@

usbdescriptors.o: renesas/usbdescriptors.c
	$(TOOL_PATH)/rx-elf-gcc $(CFLAGS) $^ -o $@ -DGRSAKURA

usb_hal.o: renesas/usb_hal.c
	$(TOOL_PATH)/rx-elf-gcc $(CFLAGS) $^ -o $@ -DGRSAKURA

usb_core.o: renesas/usb_core.c
	$(TOOL_PATH)/rx-elf-gcc $(CFLAGS) $^ -o $@

usb_cdc.o: renesas/usb_cdc.c
	$(TOOL_PATH)/rx-elf-gcc $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f *.o *.elf *.bin

