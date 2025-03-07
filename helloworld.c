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
  int answer;
  kprintf("begin 03 sort\n");
  for (j = 0; j < 10; j++) {
    startcycle = get_cycle_count();
    answer = t03_sort3();
    arr[j] = (get_cycle_count() - startcycle)/50;
    kprintf("round%d: %ld %d\n", j, arr[j], answer);
  }
  kprintf("end 03 sort\n");
  while (1)
    ;
  return 0;
}



