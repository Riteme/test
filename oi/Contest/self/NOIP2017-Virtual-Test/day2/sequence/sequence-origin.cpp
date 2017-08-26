#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 20
#define MOD 998244353

typedef long long i64;

static int n;
static char str[NMAX + 10];
static i64 cnt[NMAX + 10];

int main() {
    scanf("%s", str);
    n = strlen(str);

    for (int s = 0; s < (1 << n); s++) {
        bool ok = true;
        for (int i = 0; i < n && ok; i++) {
            if (str[i] != '.' && ((s >> i) & 1) + '0' != str[i])
                ok = false;
        }

        if (!ok)
            continue;

        int one = 0, zero = 0;
        for (int i = 0; i < n; i++) {
            if ((s >> i) & 1)
                one = max(one + 1, zero + 1);
            else
                zero++;
        }

        cnt[max(one, zero)]++;
    }

    i64 ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = (ans + cnt[i] * cnt[i]) % MOD;
    }

    printf("%lld\n", ans);

    return 0;
}
