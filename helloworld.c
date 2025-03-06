#include "kprintf.h"
#include <stdint.h>

int realmain(void);

int main() {
  asm volatile (
	"li sp, 0x8ffffff0" // Load immediate value into sp
	);
  realmain();
}

uint64_t get_cycle_count() {
    uint64_t cycles;
    asm volatile ("rdcycle %0" : "=r" (cycles)); // Read cycle counter
    return cycles;
}

int realmain(void) {
  uint64_t startcycle;
  kprintf("begin sort3\n");
  startcycle = get_cycle_count();
  t03_sort3();
  kprintf("t03_sort3 %ld cycles\n", get_cycle_count() - startcycle);
  while (1)
    ;
  return 0;
}



