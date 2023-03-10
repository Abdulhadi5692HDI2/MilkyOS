# MilkyOS
![GitHub last commit](https://img.shields.io/github/last-commit/Abdulhadi5692HDI2/MilkyOS)

**NOTE: I know it's been long since i've actually worked on this. Don't worry more stuff is coming in March**


**NOTE: MilkyOS can be compiled with a regular system compiler. (well by deleting src/GNUmakefile and rename src/GNUmakefile.rgcc to src/GNUmakefile). You should use an x86-elf cross compiler though.**

A **hobby** OS. :)
64-bit only.


## Screenshots
<img src="https://github.com/Abdulhadi5692HDI2/MilkyOS/raw/trunk/SCREENSHOT.PNG" />
MilkyOS running in QEMU.


<img src="https://github.com/Abdulhadi5692HDI2/MilkyOS/raw/trunk/SCREENSHOT2.PNG" />
MilkyOS with some typed input in QEMU


<img src="https://github.com/Abdulhadi5692HDI2/MilkyOS/raw/trunk/SCREENSHOT3.PNG" />
MilkyOS displaying the contents of ```hello.txt``` that was created by the kernel code.

## You probally should have
* x86-elf cross compiler (gcc, binutils)
* 64-bit nasm
* GDB (generic)


## Compile instructions
1. Clone this repo
2. Create a directory named `iso_root`
3. Run `make # (or gmake)`
4. You will have a ISO file named `milkyos.iso`
5. Type `make distclean` to clean everything

## Debug?
1. You should've already followed <a href="#compile-instructions">compile instructions</a>
2. Type `make debug`
3. From  a another shell (local) type `gdb`
4. now type `target remote localhost:1234`
5. have fun i guess


## Known issues when booting in QEMU (fixed permanently)
* No Graphical Output will show after the limine menu. (this can be temporarily fixed by **trying** to resize the emulator window)

## Known issues with UEFI  (well atleast OVMF-x64)

**UPDATE: MilkyOS is no longer compatable with UEFI. (sure it can be booted with issues)**
* The PS/2 Keyboard won't work at all. No matter how many code changes you make to the keyboard driver.
