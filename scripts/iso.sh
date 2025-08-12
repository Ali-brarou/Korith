#!/bin/sh

mkdir -p build/isodir/boot/grub/
echo 'menuentry "korith" {
	multiboot /boot/kernel.elf
}' > build/isodir/boot/grub/grub.cfg
cp build/kernel.elf build/isodir/boot/
grub-mkrescue -o build/korith.iso build/isodir
