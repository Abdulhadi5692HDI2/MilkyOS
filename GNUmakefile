.PHONY: all
all: milkyos.iso

.PHONY: all-hdd
all-hdd: milkyos.hdd

.PHONY: run
run: milkyos.iso
	qemu-system-x86_64 -M q35 -m 2G -cdrom milkyos.iso -boot d

.PHONY: run-uefi
run-uefi: ovmf-x64 milkyos.iso
	qemu-system-x86_64 -M q35 -m 2G -bios ovmf-x64/OVMF.fd -cdrom milkyos.iso -boot d

.PHONY: run-hdd
run-hdd: milkyos.hdd
	qemu-system-x86_64 -M q35 -m 2G -hda milkyos.hdd

.PHONY: run-hdd-uefi
run-hdd-uefi: ovmf-x64 milkyos.hdd
	qemu-system-x86_64 -M q35 -m 2G -bios ovmf-x64/OVMF.fd -hda milkyos.hdd

ovmf-x64:
	mkdir -p ovmf-x64
	cd ovmf-x64 && curl -o OVMF-X64.zip https://efi.akeo.ie/OVMF/OVMF-X64.zip && 7z x OVMF-X64.zip

limine:
	git clone https://github.com/limine-bootloader/limine.git --branch=v4.x-branch-binary --depth=1
	make -C limine

.PHONY: src
src:
	$(MAKE) -C src

milkyos.iso: limine src
	cp \
		img/background.bmp config/limine.cfg limine/limine.sys limine/limine-cd.bin limine/limine-cd-efi.bin sysroot/boot/
	cp src/mkernel.sys sysroot/sys/mkernel.sys
	xorriso -as mkisofs -b boot/limine-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot boot/limine-cd-efi.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		sysroot -o milkyos.iso
	limine/limine-deploy milkyos.iso

milkyos.hdd: limine src
	dd if=/dev/zero bs=1M count=0 seek=64 of=milkyos.hdd
	parted -s milkyos.hdd mklabel gpt
	parted -s milkyos.hdd mkpart ESP fat32 2048s 100%
	parted -s milkyos.hdd set 1 esp on
	limine/limine-deploy milkyos.hdd
	sudo losetup -Pf --show milkyos.hdd >loopback_dev
	sudo mkfs.fat -F 32 `cat loopback_dev`p1
	sudo mount `cat loopback_dev`p1 img_mount
	sudo mkdir -p img_mount/EFI/BOOT
	sudo cp -v src/mkernel.sys config/limine.cfg limine/limine.sys img_mount/
	sudo cp -v limine/BOOTX64.EFI img_mount/EFI/BOOT/
	sync
	sudo umount img_mount
	sudo losetup -d `cat loopback_dev`

.PHONY: debug
debug: milkyos.iso
	qemu-system-x86_64 -S -gdb tcp::1234 -boot d -cdrom milkyos.iso

.PHONY: clean
clean:
	rm -rf milkyos.iso milkyos.hdd
	$(MAKE) -C src clean

.PHONY: distclean
distclean: clean
	rm -f sysroot/boot/*.sys sysroot/boot/*.cfg sysroot/boot/*.bin
	rm -rf limine ovmf-x64
	rm -rf limine ovmf-x64
