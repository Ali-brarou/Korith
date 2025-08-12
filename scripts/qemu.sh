#!/bin/sh

qemu-system-i386 -kernel build/kernel.elf -d int,cpu_reset
