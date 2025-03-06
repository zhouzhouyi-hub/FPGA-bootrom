#include "kprintf.h"
#include <stdint.h>


int realmain(void) {
  uint64_t startcycle;
  kprintf("sort3\n");
  //startcycle = get_cycle_count();
  //t03_sort3();
  //kprintf("t03_sort3 %lu cycles\n", get_cycle_count() - startcycle);
  while (1)
    ;
  return 0;
}


int main() {
  asm volatile (
	"li sp, 0x8ffffff0" // Load immediate value into sp
	);
  realmain();
}

