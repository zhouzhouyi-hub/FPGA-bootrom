riscv64-linux-gnu-gcc -T tmp.lds -o helloeducg.elf -static -nostartfiles  helloword.c kprintf.c -nostdlib shuffle2.o
