#pragma GCC optimize(3)
#pragma GCC optimize("fast-math")

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

typedef long double ld;

#define NMAX 100
#define MMAX 20
#define EPS 1e-10L
#define INF 1e9L

inline bool eq(const ld &x, const ld &y) {
    return x - EPS < y && y < x + EPS;
}

struct Vector {
    Vector() : x(0.0L), y(0.0L) {}
    Vector(ld _x, ld _y) : x(_x), y(_y) {}

    ld x, y;

    Vector operator+(const Vector &v) const {
        return {x + v.x, y + v.y};
    }

    Vector operator-(const Vector &v) const {
        return {x - v.x, y - v.y};
    }

    Vector operator*(const ld &k) const {
        return {x * k, y * k};
    }

    Vector operator/(const ld &k) const {
        return {x / k, y / k};
    }
};

inline ld dot(const Vector &u, const Vector &v) {
    return u.x * v.x + u.y * v.y;
}

inline ld cross(const Vector &u, const Vector &v) {
    return u.x * v.y - u.y * v.x;
}

struct Segmemt {
    Segmemt(const Vector &_p, const Vector &_q) : p(_p), q(_q) {
        if (p.x > q.x) swap(p, q);
    }
    Vector p, q;
};

inline ld secty(const Segmemt &S, const ld &x) {
    return S.p.y + (S.q.y - S.p.y) / (S.q.x - S.p.x) * (x - S.p.x);
}

static int n, st;
static ld ans, L[NMAX + 10], R[NMAX + 10];
static vector<Segmemt> poly[NMAX + 10];
static ld scan[NMAX * MMAX + 10];

void initialize() {
    static Vector seq[MMAX + 10];
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int m;
        scanf("%d", &m);
        L[i] = INF;
        R[i] = -INF;
        for (int j = 1; j <= m; j++) {
            scanf("%Lf%Lf", &seq[j].x, &seq[j].y);
            scan[st++] = seq[j].x;
            L[i] = min(L[i], seq[j].x);
            R[i] = max(R[i], seq[j].x);
        }

        ld sum = 0.0L;
        poly[i].push_back({seq[1], seq[m]});
        for (int j = 1; j < m; j++) {
            poly[i].push_back({seq[j], seq[j + 1]});
            if (j > 1)
                sum += cross(seq[j] - seq[1], seq[j + 1] - seq[1]);
        }
        ans += fabs(sum);
    }
    ans *= 0.5L;
}

struct Interval {
    Interval() {}
    Interval(ld _l, ld _r) : l(_l), r(_r) {
        if (l > r) swap(l, r);
    }

    ld l, r;

    bool operator<(const Interval &z) const {
        return l < z.l;
    }
};

static int cnt, m;
static ld P[MMAX * 2 + 10];
static Interval S[NMAX * MMAX + 10];

#define CROSS 1
#define REFLECT 2
#define VERTICAL 3

inline bool same(const Vector &u, const Vector &v) {
    return eq(u.x, v.x) && eq(u.y, v.y);
}

inline int sgn(ld x) {
    if (x >= EPS) return 1;
    if (x <= -EPS) return -1;
    return 0;
}

inline void consider(const Segmemt &s1, const Segmemt &s2, ld x) {
    if (eq(s1.p.x, s1.q.x) || eq(s2.p.x, s2.q.x)) return;
    Vector mid = same(s1.p, s2.p) ? s2.p : s2.q;
    if (!eq(mid.x, x)) return;

    Vector p1 = same(s1.p, mid) ? s1.q : s1.p;
    Vector p2 = same(s2.p, mid) ? s2.q : s2.p;
    const Vector right(1, 0);
    if (sgn(dot(right, p1 - mid)) == sgn(dot(right, p2 - mid))) return;
    P[cnt++] = mid.y;
}

void cut(int i, const ld &x) {
    cnt = 0;
    for (auto &seg : poly[i]) {
        if (eq(seg.p.x, x) && eq(seg.q.x, x)) {
            P[cnt++] = seg.p.y;
            P[cnt++] = seg.q.y;
        } else if (eq(seg.p.x, x) || eq(seg.q.x, x))
            continue;
        else if (seg.p.x <= x && x <= seg.q.x)
            P[cnt++] = secty(seg, x);
    }

    consider(poly[i][0], poly[i].back(), x);
    for (int j = 0; j < poly[i].size() - 1; j++)
        consider(poly[i][j], poly[i][j + 1], x);

    sort(P, P + cnt);
    for  (int i = 0; i < cnt; i += 2)
        S[m++] = Interval(P[i], P[i + 1]);
}

ld eval(ld x) {
    m = 0;
    for (int i = 1; i <= n; i++) {
        if (L[i] <= x && x <= R[i])
            cut(i, x);
    }

    ld ret = 0.0L;
    sort(S, S + m);
    for (int i = 0; i < m; i++) {
        ld l = S[i].l, r = S[i].r;
        for (; i < m - 1 && S[i + 1].l <= r; i++)
            r = max(r, S[i + 1].r);
        ret += r - l;
    }

    return ret;
}


int main() {
    initialize();

    sort(scan, scan + st);
    ld ans2 = 0;
    for (int i = 0; i < st - 1; i++) {
        if (eq(scan[i], scan[i + 1])) continue;
        ld l = scan[i] + EPS, r = scan[i + 1] - EPS;
        ld lf = eval(l), rf = eval(r);
        ans2 += (lf + rf) * 0.5 * (r - l + 2 * EPS);
    }

    printf("%.10Lf %.10Lf\n", ans, ans2);

    return 0;
}
