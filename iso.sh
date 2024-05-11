#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/butterscotch.kernel isodir/boot/butterscotch.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "butterscotch" {
	multiboot2 /boot/butterscotch.kernel
	boot
}
EOF
grub2-mkrescue -o butterscotch.iso isodir
