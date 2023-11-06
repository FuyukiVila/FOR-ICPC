#include <stdio.h>

template<typename T>
void print_int(T t) {
    printf("%d %#x\n", (int) t, (int) t);
}

template<typename T>
void print_short(T t) {
    printf("%hd %#x\n", (short) t, (short) t);
}

template<typename T>
void print_unsignedShort(T t) {
    printf("%u %#x\n", (unsigned short) t, (unsigned short) t);
}

template<typename T>
void print_unsignedInt(T t) {
    printf("%u %#x\n", (unsigned int) t, (unsigned int) t);
}

template<typename T>
void print_float(T t) {
    float f = t;
    printf("%f %#x\n", (float) t, *(unsigned int *) &f);
}

template<typename T>
void print_double(T t) {
    double f = t;
    printf("%lf %#x\n", (double) t, *(unsigned long long *) &f);
}

int main() {
    short a = -12345;
    int b = 2147483647;
    float c = 123456.789e5;
    double d = 123456.789e5;
    printf("x = %lf\n", d);
    print_double(d);
    print_float(d);
}