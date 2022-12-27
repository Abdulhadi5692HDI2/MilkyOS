# MilkyOS
![GitHub last commit](https://img.shields.io/github/last-commit/Abdulhadi5692HDI2/MilkyOS)
<img src="https://img.shields.io/tokei/lines/github/Abdulhadi5692HDI2/MilkyOS" />


A **hobby** OS. :)
64-bit only.


## You probally should have
* Everything that the BuildDepMilkyOS script installs.


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

## TODO

* [x] Load an [IDT](https://wiki.osdev.org/Interrupt_Descriptor_Table) so that exceptions and interrupts can be handled. (completed 15/12/2022 19:51)

* [x] W̶r̶i̶t̶e̶ ̶a̶ ̶v̶i̶r̶t̶u̶a̶l̶ ̶a̶n̶d̶ ̶p̶h̶y̶s̶i̶c̶a̶l̶ ̶m̶e̶m̶o̶r̶y̶ ̶m̶a̶n̶a̶g̶e̶r̶ Write a dynamic memory manger (completed 19/12/2022 19:48)

* [x] Implement a interrupt controller (most common in osdev is `8259 PIC` ) (completed 19/12/2022)
* [x] Add a PS/2 Keyboard driver
* [ ] Configure a timer such as the Local APIC timer, the PIT, or the HPET.
* [ ] Implement a scheduler to schedule threads in order make multitasking possible.
* [x] Design a virtual file system (VFS) and implement it. (completed 26/12/2022)
* [x] Implement a simple virtual file system like a memory-only tmpfs to avoid crippling the design of your VFS too much while implementing it alongside real storage filesystems. (completed 26/12/2022)
* [ ] Decide how to abstract devices. UNIX likes usually go for a `/dev` virtual filesystem containing device nodes and use `ioctl()` alongside standard FS calls to do operations on them.

* [ ] Get a userland going by loading executables from your VFS and running them in ring 3. Set up a way to perform system calls.
* [ ] Write a PCI driver.
* [ ] Add support for a storage medium, the easiest and most common ones are AHCI and NVMe.
 
## Known issues when booting in QEMU (fixed permanently)
* No Graphical Output will show after the limine menu. (this can be temporarily fixed by **trying** to resize the emulator window)

## Known issues with UEFI  (well atleast OVMF-x64)

**UPDATE: MilkyOS is no longer compatable with UEFI. (sure it can be booted with issues)**
* The PS/2 Keyboard won't work at all. No matter how many code changes you make to the keyboard driver.
