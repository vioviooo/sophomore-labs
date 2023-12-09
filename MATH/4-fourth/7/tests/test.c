#include <stdio.h>

int main() {
    int a=15;
    int b=25;
    int c=b+11;
    a=c;
    b=c*a;
    printf("%d %d %d", a, b, c);
}