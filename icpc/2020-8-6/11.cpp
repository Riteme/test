#include <cstdio>
#include <cstring>
#include <cassert>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000
#define MOD 31607
#define INV2 15804

struct vec {
    vec() : x(0), y(0) {}
    vec(int _x, int _y) : x(_x), y(_y) {}

    int x, y;

    int idx() const {
        if (x >= 0 && y >= 0)
            return 0;
        if (x <= 0 && y >= 0)
            return 1;
        if (x <= 0 && y <= 0)
            return 2;
        return 3;
    }

    int len2() const {
        return x * x + y * y;
    }

    bool operator<(const vec &z) const {
        int i = idx(), j = z.idx();
        if (i != j)
            return i < j;

        int c = (*this) % z;
        return c ? c > 0 : len2() < z.len2();
    }

    vec operator+(const vec &z) const {
        return vec(x + z.x, y + z.y);
    }

    vec operator-(const vec &z) const {
        return vec(x - z.x, y - z.y);
    }

    vec operator*(int k) const {
        return vec(x * k, y * k);
    }

    int operator*(const vec &z) const {
        return x * z.x + y * z.y;
    }

    int operator%(const vec &z) const {
        return x * z.y - z.x * y;
    }
};

int inv(int x) {
    return x == 1 ? 1 : MOD - MOD / x * inv(MOD % x) % MOD;
}

int n;
int idx[NMAX + 10];
vec P[NMAX + 10];
int npr[NMAX + 10], npi[NMAX + 10];

void initialize() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x, y, p, q;
        scanf("%d%d%d%d", &x, &y, &p, &q);
        assert(p < q);
        P[i] = vec(x, y);
        npr[i] = ((1 - p * inv(q)) % MOD + MOD) % MOD;
        assert(npr[i] != 0);
        npi[i] = inv(npr[i]);
    }
}

int O;
bool pcmp(int i, int j) {
    return (P[i] - P[O]) < (P[j] - P[O]);
}

int nxtp(int i) {
    return i + 1 < n ? i + 1 : 1;
}

int prep(int i) {
    return i > 1 ? i - 1 : n - 1;
}

int solve(int x) {
    for (int i = 1; i <= n; i++) {
        idx[i] = i;
    }
    idx[x] = n;
    O = x;
    sort(idx + 1, idx + n, pcmp);

    vec o = P[x];
    int prob = 1;
    int i = 1, j = 1, k = 1;

    while (nxtp(j) != k) {
        vec a = P[idx[nxtp(j)]] - o;
        vec b = P[idx[k]] - o;
        if (a % b == 0 && a * b > 0) {
            j = nxtp(j);
            // prob = prob * npr[idx[j]] % MOD;
        } else break;
    }

    while (prep(i) != j) {
        vec a = P[idx[prep(i)]] - o;
        vec b = P[idx[k]] - o;
        if (a % b > 0) {
            i = prep(i);
            // printf("+ %d\n", idx[i]);
            prob = prob * npr[idx[i]] % MOD;
        } else break;
    }

    int rax = 0;
    for (int _ = 1; _ < n; _++) {
        // printf("[x=%d] k=%d, j=%d, i=%d\n", x, idx[k], idx[j], idx[i]);
        int area = (o % P[idx[k]]) % MOD * (1 - npr[x]) % MOD;
        int p = prob * (1 - npr[idx[k]]) % MOD;
        // printf("incr = %d\n", (area * p % MOD + MOD) % MOD);
        rax = (rax + area * p) % MOD;

        // printf("+ %d\n", idx[k]);
        prob = prob * npr[idx[k]] % MOD;
        int nk = nxtp(k);
        if (j == k) {
            j = nk;
            // prob = prob * npr[idx[j]] % MOD;

            while (nxtp(j) != nk) {
                vec a = P[idx[nxtp(j)]] - o;
                vec b = P[idx[nk]] - o;
                if (a % b == 0 && a * b > 0) {
                    j = nxtp(j);
                    // prob = prob * npr[idx[j]] % MOD;
                } else break;
            }

            int oi = i;
            while (true) {
                vec a = P[idx[i]] - o;
                vec b = P[idx[nk]] - o;
                if (a % b == 0 && a * b > 0) {
                    // printf("- %d\n", idx[i]);
                    prob = prob * npi[idx[i]] % MOD;
                    i = nxtp(i);
                } else break;
                if (i == oi)
                    break;
            }

            while (true) {
                vec a = P[idx[i]] - o;
                vec b = P[idx[nk]] - o;
                if (a % b < 0 || (a % b == 0 && a * b < 0)) {
                    // printf("- %d\n", idx[i]);
                    prob = prob * npi[idx[i]] % MOD;
                    i = nxtp(i);
                } else break;
            }
        }

        k = nk;
    }

    return rax;
}

void _main() {
    initialize();

    if (n < 3) {
        puts("0");
        return;
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = (ans + solve(i)) % MOD;
    }
    ans = ans * INV2 % MOD;
    if (ans < 0)
        ans += MOD;
    printf("%d\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        _main();
    }

    return 0;
}