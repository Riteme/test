#include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
    double price;
    scanf("%lf", &price);
    double output = price * 1.15;
    printf("%.2lf\n", output);
    }
}