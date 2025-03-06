//#include "sylib.h"
#include <time.h>
#include "2024-U03-25.in"
#define N 1024

void *memcpy(void *dest, const void *src, unsigned long n) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    int i;
    // Copy n bytes from src to dest
    for (i = 0; i < n; i++) {
        d[i] = s[i];
    }

    return dest; // Return the destination pointer
}

void trsm(int n, float A[][N], float B[][N]) {
  int i, j, k;

  k = 0;
  while (k < n) {
    i = 0;
    while (i < n) {
      B[i][k] = B[i][k] / A[i][i];
      j = i + 1;
      while (j < n) {
        B[j][k] = B[j][k] - A[j][i] * B[i][k];
        j = j + 1;
      }
      i = i + 1;
    }
    k = k + 1;
  }
}

int c = 0;
float getfloat1(){
  return inputfloat[c++];
}


float A[N][N];
float B[N][N];
float C[N][N];

float U03_25() {
  //int n = getint();
  int i, j, k;
  int numfloats = 0;
  c = 0;
  i = 0;
  j = 0;
  while (i < n) {
    j = 0;
    while (j < n) {
      A[i][j] = getfloat1();
      j = j + 1;
    }
    i = i + 1;
  }
  i = 0;
  j = 0;
  while (i < n) {
    j = 0;
    while (j < n) {
      C[i][j] = getfloat1();
      j = j + 1;
    }
    i = i + 1;
  }

  k = 0;
  while (k < 5) {
    i = 0;
    while (i < n) {
      j = 0;
      while (j < n) {
        B[i][j] = C[i][j];
        j = j + 1;
      }
      i = i + 1;
    }
    trsm(n, A, B);
    k = k + 1;
  }


  float ans = 0;
  i = 0;
  while (i < n) {
    j = 0;
    while (j < n) {
      ans = ans + B[i][j];
      j = j + 1;
    }
    i = i + 1;
  }

  return ans;
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


int main() {
  int j = 0;
  struct timespec start, end;
  long elapsed_ns;
  unsigned long max;
  double avg, std_dev;
  unsigned long arr[10];
  float ans;
  for (j = 0; j < 10; j++) {
    ans = 0;
    clock_gettime(CLOCK_MONOTONIC, &start);
    ans = U03_25();
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000L + (end.tv_nsec - start.tv_nsec);
    arr[j] = elapsed_ns/(2500);
    printf("%f\n", ans);
  }
  compute_stats(arr, 10, &max, &avg, &std_dev);
  printf("%d\n", ans);
  printf("max = %ldus, avg = %lfus, stddev= %lfus\n", max, avg, std_dev);
  
}
