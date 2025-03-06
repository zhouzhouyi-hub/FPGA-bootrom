#include "kprintf.h"
#include <stdint.h>
int errno;
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


float U03_25(void);

int realmain(void) {
  uint64_t startcycle;
  unsigned long arr[10];
  unsigned long max;
  double avg, std_dev;  
  int j;
  float answer;
  kprintf("begin sort3\n");
  for (j = 0; j < 10; j++) {
    startcycle = get_cycle_count();
    answer = U03_25();
    arr[j] = (get_cycle_count() - startcycle)/50;
    kprintf("%ld %lf\n", arr[j], answer);
  }

  while (1)
    ;
  return 0;
}



