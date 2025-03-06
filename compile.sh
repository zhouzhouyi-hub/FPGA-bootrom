#riscv64-linux-gnu-gcc -T tmp.lds -o boot.elf -static -nostartfiles -O2  helloworld.c kprintf.c -nostdlib  03_sort3bare.c -lm
riscv64-linux-gnu-gcc -T tmp.lds -o boot.elf -static -nostartfiles -O2  helloworld.c kprintf.c -nostdlib 2024-U03-25.c 

