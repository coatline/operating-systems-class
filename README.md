Prerequisites:
- Qemu, an aarch64 emulator. Your will use this emulator to run, and test your operating system.
- gdb, the Gnu Debugger.  If you are using an Intel machine for your assignments, then you will use gdb-multiarch to debug your operating system.
- ddd, the Data Display Debugger.  This program provides a graphical user interface to GDB.  It has some nice features that you will not find in other debuggers, even though the interface is old.
- gcc, the Gnu C compiler. If you are using an Intel machine for your assignments, then you will use the cross compiler aarch64-linux-gnu-gcc. The Gnu C compiler will generate object code for the main driver of your stage 2 operating system.  You will run gcc (or aarch64-linux-gnu-gcc) to both compile C code as well as ARMv8 assembler code.


To install:
sudo apt update && sudo apt upgrade -y
sudo apt install -y build-essential gcc-aarch64-linux-gnu gdb-multiarch qemu-system-aarch64 ddd

Verification: Run `aarch64-linux-gnu-gcc --version` and `qemu-system-aarch64 --version` and `ddd &` to confirm these are accessible.




To compress to tarball:
tar -czf bncastlebe42_hw1.tar.gz bncastlebe42_hw1/