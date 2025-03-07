#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include "03_sort3.in"
#define base 16

int getMaxNum(int n, int arr[]){
    int ret = 0;
    int i = 0;
    while (i < n){
        if (arr[i] > ret) ret = arr[i];
        i = i + 1;
    }
    return ret;
}

int getNumPos(int num, int pos){
    int tmp = 1;
    int i = 0;
    while (i < pos){
        num = num / base;
        i = i + 1;
    }
    return num % base;
}

void radixSort(int bitround, int a[], int l, int r){
    int head[base] = {};
    int tail[base] = {};
    int cnt[base] = {};

    if (bitround == -1 || l + 1 >= r) return;

    {    
        int i = l;
        
        while (i < r){
            cnt[getNumPos(a[i], bitround)]
                = cnt[getNumPos(a[i], bitround)] + 1;
            i = i + 1;
        }        
        head[0] = l;
        tail[0] = l + cnt[0];

        i = 1;
        while (i < base){
            head[i] = tail[i - 1];
            tail[i] = head[i] + cnt[i];
            i = i + 1;
        }
        i = 0;
        while (i < base){
            while (head[i] < tail[i]){
                int v = a[head[i]];
                while (getNumPos(v, bitround) != i){
                    int t = v;
                    v = a[head[getNumPos(t, bitround)]];
                    a[head[getNumPos(t, bitround)]] = t;
                    head[getNumPos(t, bitround)] = head[getNumPos(t, bitround)] + 1;
                }
                a[head[i]] = v;
                head[i] = head[i] + 1;
            }
            i = i + 1;
        }
    }

    {
        int i = l;
        
        head[0] = l;
        tail[0] = l + cnt[0];

        i = 0;
        while (i < base){
            if (i > 0){
                head[i] = tail[i - 1];
                tail[i] = head[i] + cnt[i];
            }
            radixSort(bitround - 1, a, head[i], tail[i]);
            i = i + 1;
        }
    }

    return;
}


static int ans;

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

int main(){
    int n = 5000000;
    struct timespec start, end;
    long elapsed_ns;
    unsigned long max;
    double avg, std_dev;
    unsigned long arr[10];
    int j;
    printf("start to sort\n");
    for (j = 0; j < 10; j++) {
      ans = 0;
      clock_gettime(CLOCK_MONOTONIC, &start);
      radixSort(8, a, 0, n);

      int i = 0;
      while (i < n){
        ans = ans + i * (a[i] % (2 + i));
        i = i + 1;
      }

      if (ans < 0)
        ans = -ans;
      clock_gettime(CLOCK_MONOTONIC, &end);
      elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000L + (end.tv_nsec - start.tv_nsec);
      arr[j] = elapsed_ns/(2500);
      printf("%ld\n", arr[j]);
    }
    compute_stats(arr, 10, &max, &avg, &std_dev);
    printf("%d\n", ans);
    //printf("max = %ldus, avg = %lfus, stddev= %lfus\n", max, avg, std_dev);

    return 0;
}
