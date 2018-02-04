
TOOL_PATH:=/disk/temp/RX-Toolchain/prefix/bin

CFLAGS = -c -O2 -ffunction-sections -fdata-sections -mcpu=rx600 -I. -Icommon -Wall -Wextra
LDFLAGS = -Wl,--gc-sections,--strip-debug -nostartfiles

sakura.bin: sakura.elf
	$(TOOL_PATH)/rx-elf-objcopy -O binary $^ $@

sakura.elf: crt0.o main.o led.o uart.o timer.o script.o opcode.o command.o
	$(TOOL_PATH)/rx-elf-gcc $(LDFLAGS) -T common/sakura_rx.ld $^ -o $@

crt0.o: common/sakura_crt0.S
	$(TOOL_PATH)/rx-elf-gcc $(CFLAGS) $^ -o $@

led.o: led.c
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

main.o: main.c
	$(TOOL_PATH)/rx-elf-gcc $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f *.o *.elf *.bin

