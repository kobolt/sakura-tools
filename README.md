# GR-SAKURA Tools

This is a collection of various support tools for the [Gadget Renesas GR-SAKURA](http://gadget.renesas.com/en/product/sakura.html) reference board. The goal is to have the board usable under a local Linux development environment. The board uses the RX63N microcontroller, so make sure to get the [RX GCC Toolchain](https://gcc-renesas.com/wiki/index.php?title=How_to_build_the_RX_Toolchain_under_Ubuntu_14.04).

### Sakura Shell
Similar to the Kurumi Shell, but this runs on the GR-SAKURA board instead. Coded in C and to be compiled with the RX GCC toolchain. It provides a command shell interface against its LED and timer functions. The shell is spawned using the USB CDC library from Renesas, so it will show up as a virtual serial port (typically /dev/ttyACM0). The code and build environment also assumes that the pre-flashed USB mass-storage based bootloader is in use, so the binary may be transferred using that USB interface.

### Sakura Script
A small Python script to upload and run script files on a GR-SAKURA which has been flashed with the Sakura Shell code.

