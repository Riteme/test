#include <cmath>
#include <cstdio>
#include <cstring>
#include <cassert>

#include <algorithm>

using namespace std;

using f64 = double;

constexpr f64 EPS = 1e-9;
constexpr f64 EPS0 = 1e-3;
constexpr f64 zero = 0.0;
constexpr f64 one = 1.0;
constexpr f64 pi = 3.141592653589793;

constexpr int NMAX = 700;
constexpr int MMAX = 2000;
constexpr int TMAX = 40;

bool eq(f64 x, f64 y) {
    return fabs(x - y) < EPS;
}

f64 sqrt_s(f64 x) {
    return sqrt(fmax(zero, x));
}

f64 acos_s(f64 x) {
    if (x > one)
        x = one;
    else if (x < -one)
        x = -one;
    return acos(x);
}

struct vec {
    vec() : x(0), y(0) {}
    vec(f64 _x, f64 _y) : x(_x), y(_y) {}

    f64 x, y;

    f64 len() const {
        return hypot(x, y);
    }

    vec norm() const {
        return (*this) / len();
    }

    vec cw(f64 t) const {
        f64 c = cos(t), s = sin(t);
        return {c * x + s * y, -s * x + c * y};
    }
    vec ccw(f64 t) const {
        f64 c = cos(t), s = sin(t);
        return {c * x - s * y, s * x + c * y};
    }
    vec operator+(const vec &z) const {
        return {x + z.x, y + z.y};
    }
    vec operator-(const vec &z) const {
        return {x - z.x, y - z.y};
    }
    vec operator*(f64 k) const {
        return {x * k, y * k};
    }
    vec operator/(f64 k) const {
        return {x / k, y / k};
    }
    f64 operator*(const vec &z) const {
        return x * z.x + y * z.y;
    }
    f64 operator%(const vec &z) const {
        return x * z.y - y * z.x;
    }
};

struct cir {
    vec u;
    f64 r;
};

struct ray {
    vec u, v;
};

struct result {
    f64 a, b;
};

vec rrsect(const ray &a, const ray &b) {
    vec z = b.u - a.u;
    f64 t = (b.v % z) / (b.v % a.v);
    return a.u + a.v * t;
}

bool crsect(const cir &c, const ray &l, result &r) {
    vec z = c.u - l.u;
    f64 p = z * l.v;
    f64 d = fabs(z % l.v);
    if (d >= c.r + EPS)
        return false;

    f64 s = sqrt_s(c.r * c.r - d * d);
    r.a = p + s;
    r.b = p - s;
    return true;
}

f64 f(f64 x);

f64 simpson(f64 fl, f64 fr, f64 fm, f64 l, f64 r) {
    return (fl + fr + 4 * fm) * (r - l) / 6;
}

f64 rsimpson(f64 slr, f64 fl, f64 fr, f64 fm, f64 l, f64 r) {
    f64 mid = (l + r) / 2;
    f64 fml = f((l + mid) / 2);
    f64 fmr = f((mid + r) / 2);
    f64 slm = simpson(fl, fm, fml, l, mid);
    f64 smr = simpson(fm, fr, fmr, mid, r);
    if (fabs(slr - smr - slm) < EPS * slr + EPS)
    //if (fabs(slr - smr - slm) < EPS0)
        return slm + smr;
    return rsimpson(slm, fl, fm, fml, l, mid) +
        rsimpson(smr, fm, fr, fmr, mid, r);
}

int n, m, k;
vec P[NMAX + 10];
cir C[MMAX + 10];

f64 polar(vec u) {
    u = u.norm();
    f64 t = acos_s(u.x);
    if (u.y < -EPS)
        t = 2 * pi - t;
    return t;
}

f64 angle(const vec &u, const vec &v) {
    return acos_s((u * v) / u.len() / v.len());
}

f64 evaluate(f64 l, f64 r) {
    f64 m = (l + r) / 2;
    f64 fl = f(l), fr = f(r), fm = f(m);
    f64 v = simpson(fl, fr, fm, l, r);
    return rsimpson(v, f(l), f(r), f(m), l, r);
}

struct event {
    f64 x;
    int v;

    bool operator<(const event &z) const {
        return x < z.x || (eq(x, z.x) && v < z.v);
    }
};

int cnt;
event ev[MMAX * 2 + 10];

f64 c0;

f64 cube(f64 x) {
    return x * x * x;
}

f64 f(f64 x) {
    cnt = 0;
    ray l = {P[k], {cos(x), sin(x)}};

    ev[cnt++] = {0, -1};
    for (int i = k, j = 0; ; i = j) {
        assert(j != k);
        j = i % n + 1;
        vec p = P[j] - P[k];
        if (l.v % p > -EPS) {
            vec z = rrsect(l, {P[i], P[j] - P[i]});
            f64 s = (z - P[k]) * l.v;
            ev[cnt++] = {s, +1};
            break;
        }
    }

    for (int i = 1; i <= m; i++) {
        result r;
        if (crsect(C[i], l, r)) {
            if (r.a > r.b)
                swap(r.a, r.b);
            ev[cnt++] = {r.a, +1};
            ev[cnt++] = {r.b, -1};
        }
    }

    sort(ev, ev + cnt);
    f64 rax = 0, lp;
    int sum = 1;
    for (int i = 0; i < cnt; i++) {
        if (sum == 1 && ev[i].v == -1)
            lp = ev[i].x;
        else if (sum == 0 && ev[i].v == +1)
            rax += cube(ev[i].x) - cube(lp);
        sum += ev[i].v;
    }

    rax *= sin(x - c0) * 2 / 3;
    return rax;
}

f64 partial_area(f64 t) {
    f64 rax = 0;
    vec v = {cos(t), sin(t)}, p;
    for (int i = k, j = 0; ; i = j) {
        assert(j != k);
        j = i % n + 1;
        p = P[j] - P[k];
        if (v % p > -EPS) {
            vec z = rrsect({P[k], v}, {P[i], P[j] - P[i]});
            rax += P[i] % z;
            rax += z % P[k];
            break;
        }

        rax += P[i] % P[j];
    }

    return fabs(rax / 2);
}

f64 degree(f64 x) {
    return x / pi * 180;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf", &P[i].x, &P[i].y);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%lf%lf%lf", &C[i].u.x, &C[i].u.y, &C[i].r);
    }

    vec p0 = P[k % n + 1] - P[k];
    vec p1 = P[k > 1 ? k - 1 : n] - P[k];
    f64 l0 = polar(p0);
    f64 r0 = l0 + angle(p0, p1);
    f64 l = l0, r = r0;
    //f64 r = polar(P[k > 1 ? k - 1 : n] - P[k]);

    fprintf(stderr, "l = %.12lf\n", degree(l));
    fprintf(stderr, "r = %.12lf\n", degree(r));

    for (int _ = 0; _ < TMAX; _++) {
        f64 t = (l + r) / 2;

        c0 = t;
        f64 force = evaluate(l0, r0);
        if (force > 0)
            l = t;
        else
            r = t;
    }

    f64 t = (l + r) / 2;

    fprintf(stderr, "t = %.12lf\n", degree(t));

    t = pi * 3 / 2 - t;
    for (int i = 1; i <= n; i++) {
        vec z = P[i] - P[k];
        vec p = z.ccw(t);
        vec v = P[i] + p - z;
        printf("%.10lf %.10lf\n", v.x, v.y);
    }

    return 0;
}
