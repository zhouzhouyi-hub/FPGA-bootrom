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

double pow(double base, int exp) {
    double result = 1.0;
    int negative_exp = (exp < 0); // Check if exponent is negative
    if (negative_exp) exp = -exp; // Work with positive exponent

    while (exp > 0) {
        if (exp % 2 == 1) { // If exponent is odd, multiply by base
            result *= base;
        }
        base *= base; // Square the base
        exp /= 2;     // Divide exponent by 2
    }

    return negative_exp ? 1.0 / result : result; // Handle negative exponent case
}

double sqrt(double x) {
    if (x < 0) return -1.0; // Return -1 for negative numbers (error case)
    if (x == 0 || x == 1) return x; // Base cases

    double guess = x;
    double epsilon = 1e-9; // Precision threshold

    while (1) {
        double new_guess = 0.5 * (guess + x / guess);
        if (fabs(new_guess - guess) < epsilon) // Check for convergence
            break;
        guess = new_guess;
    }

    return guess;
}

void compute_stats(unsigned long arr[], int size, unsigned long *max, double *avg, double *std_dev) {
    unsigned long sum = 0;
    *max = arr[0];  // Assume first element is max initially

    // Compute max and sum
    for (int i = 0; i < size; i++) {
        if (arr[i] > *max) {
            *max = arr[i];
        }
        sum += arr[i];
    }

    // Compute average
    *avg = (double)sum / size;

    // Compute standard deviation
    double variance_sum = 0.0;
    for (int i = 0; i < size; i++) {
        variance_sum += pow(arr[i] - *avg, 2);
    }
    *std_dev = sqrt(variance_sum / size);
}

int realmain(void) {
  uint64_t startcycle;
  unsigned long arr[10];
  unsigned long max;
  double avg, std_dev;  
  int j;
  int answer;
  kprintf("begin sort3\n");
  for (j = 0; j < 10; j++) {
    startcycle = get_cycle_count();
    answer = t03_sort3();
    arr[j] = (get_cycle_count() - startcycle)/50;
  }
  compute_stats(arr, 10, &max, &avg, &std_dev);
  kprintf("answer = %d max = %ldus, avg = %lfus, stddev= %lfus\n", answer, max, avg, std_dev);
  while (1)
    ;
  return 0;
}



