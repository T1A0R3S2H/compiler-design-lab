// op_example.c
#include <stdio.h>

int main() {
    int a = 5;
    int b = 10;
    int c = a + b;
    int d = a - b;
    int e = a * b;
    int f = a / b;
    int g = a % b;

    if (a > b) {
        printf("a is greater than b\n");
    } else if (a < b) {
        printf("a is less than b\n");
    } else {
        printf("a is equal to b\n");
    }

    int h = (a == b) ? 1 : 0;
    int i = (a != b) ? 1 : 0;

    int j = a & b;
    int k = a | b;
    int l = a ^ b;
    int m = ~a;

    int n = a && b;
    int o = a || b;

    int p = a++;
    int q = ++a;
    int r = a--;
    int s = --a;

    int array[5] = {1, 2, 3, 4, 5};
    int t = array[2];

    printf("c = %d\n", c);
    printf("d = %d\n", d);
    printf("e = %d\n", e);
    printf("f = %d\n", f);
    printf("g = %d\n", g);
    printf("h = %d\n", h);
    printf("i = %d\n", i);
    printf("j = %d\n", j);
    printf("k = %d\n", k);
    printf("l = %d\n", l);
    printf("m = %d\n", m);
    printf("n = %d\n", n);
    printf("o = %d\n", o);
    printf("p = %d\n", p);
    printf("q = %d\n", q);
    printf("r = %d\n", r);
    printf("s = %d\n", s);
    printf("t = %d\n", t);

    return 0;
}

