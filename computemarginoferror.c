#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define SAMPLE_SIZE 10
#define Z_SCORE 1.96  // 95% Confidence Interval

// Function to compute the mean of an array
double compute_mean(long data[], int size) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += data[i];
    }
    return sum / size;
}

// Function to compute the standard deviation
double compute_stddev(long data[], int size, double mean) {
    double sum_sq_diff = 0.0;
    for (int i = 0; i < size; i++) {
        sum_sq_diff += pow(data[i] - mean, 2);
    }
    return sqrt(sum_sq_diff / size);
}

// Function to compute Margin of Error
double compute_margin_of_error(double stddev, int size) {
    return Z_SCORE * (stddev / sqrt(size));
}

// Function to check if a line starts with a numeric prefix like "1.1)" or "2.1)"
int has_numeric_prefix(const char *line) {
    if (isdigit(line[0]) && line[1] == '.' && isdigit(line[2]) && line[3] == ')') {
        return 1; // Skip lines with prefixes like "1.1)" or "2.1)"
    }
    return 0;
}

// Function to check if a line contains only numbers and spaces
int is_numeric_line(const char *line) {
    while (*line) {
        if (!isdigit(*line) && !isspace(*line)) {
            return 0; // Non-numeric character found
        }
        line++;
    }
    return 1;
}

int main() {
    char line[256];
    long numbers[SAMPLE_SIZE];

    while (fgets(line, sizeof(line), stdin)) {
        char begin[50];
        if (!has_numeric_prefix(line))
	   continue;

        
        char *token = strstr(line, " ");
	memcpy(begin, line, 50);
	begin[token -line] = 0;
        int count = 0;
        
        while (token != NULL && count < SAMPLE_SIZE) {
            numbers[count++] = atol(token);
	    token += 2;
            token = strstr(token, " ");
        }
        
        if (count != SAMPLE_SIZE) {
            continue; // Skip lines that don't have exactly 10 numbers
        }
        
        double mean = compute_mean(numbers, SAMPLE_SIZE);
        double stddev = compute_stddev(numbers, SAMPLE_SIZE, mean);
        double margin_of_error = compute_margin_of_error(stddev, SAMPLE_SIZE);
	if (begin[0] == '1') {
	  double mean1 = compute_mean(numbers + 1, SAMPLE_SIZE - 1);
	  double stddev1 = compute_stddev(numbers + 1, SAMPLE_SIZE - 1, mean1);
	  double margin_of_error1 = compute_margin_of_error(stddev1, SAMPLE_SIZE - 1);
	  printf("%s %lf %lf\n", begin, margin_of_error/mean, margin_of_error1/mean1);
	} else
	  printf("%s %lf\n", begin, margin_of_error/mean);
    }
    
    return 0;
}
