#include <cstdio>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                if (j == 1 || j == i)
                    printf("1 ");
                else
                    printf("0 ");
            }
            puts("");
        }
    }
    return 0;
}
