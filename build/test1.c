#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>

// Pascal-specific functions and types
typedef int boolean;
typedef char *string;

// Program: main

// Constants
#define o "o"
#define e "e"
#define five 5
#define three 3
#define two 2.9
#define max 1000000000
#define conv1 233
#define eval1 95.033188
#define eps 0.000001
#define pi 03.141595653589793
#define radius 5.5

// Variables
float input = 0.0;
float area = 0.0;
float area_trunc = 0.0;
float arr[10] = {0};
int p = 0;

// Forward declarations
float float_abs(float x);
float circle_area(int radius);
int float_eq(float a, float b);
void error();
void ok();
void assert(int cond);

float float_abs(float x) {
    float float_abstmp = 0.0;
// Variables
int radius = 0;

    if ((x < 0)) {
        radius = -(x);
    } else {
        float_abstmp = x;
    }
    return float_abstmp;
}

float circle_area(int radius) {
    float circle_areatmp = 0.0;
    circle_areatmp = (((((pi * radius) * radius) + (((radius * radius)) * pi))) / 2);
    return circle_areatmp;
}

int float_eq(float a, float b) {
    int float_eqtmp = 0;
    if ((float_abs((a - b)) < eps)) {
        float_eqtmp = 1;
    } else {
        float_eqtmp = 0;
    }
    return float_eqtmp;
}

void error() {
    printf("%s", e);
}

void ok() {
    printf("%s", o);
}

void assert(int cond) {
    if ((cond == 0)) {
        error();
    } else {
        ok();
    }
}

int main() {
    assert(float_eq(circle_area(5), circle_area(five)));
    if ((1.5 != 0.0)) {
        ok();
    } else {
    }
    if ((~(((3.3 == 0.0))))) {
        ok();
    } else {
    }
    if ((((0.0 != 0.0)) && ((3 != 0.0)))) {
        error();
    } else {
    }
    if ((((0 != 0.0)) || ((0.3 != 0.0)))) {
        ok();
    } else {
    }
    float_abs(1.1);
    p = 0;
    arr[0] = 1.0;
    arr[1] = 2.0;
    input = 0.520;
    area = ((pi * input) * input);
    area_trunc = circle_area(0);
    arr[p] = (arr[p] + input);
    printf("%f", area);
    printf("%f", area_trunc);
    printf("%f", arr[0]);
    return 0;
}
