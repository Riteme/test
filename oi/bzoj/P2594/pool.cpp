/**
 * LCT维护最小生成树
 * * 离线操作
 * 在线操作太过暴力，考虑进行离线。发现如果逆序处理操作，就变成了动态最小生成树问题。
 *
 * * 边化点
 * 动态树中存储点权很方便，但边权就不简单了。
 * 因此考虑将边视为点，与其两个端点相连即可。
 *
 * * cut操作可以手动指定父亲
 * 这道题父亲是显而易见的，可以减少cut对父亲的查询的代价。
 *
 * * 哈希表最好手写......
 * std::map是红黑树
 * std::unoredered_map是线性探测法，由于是用在实际工程中，对空间要求比较严格才使用这种搞法。
 * 因此std::unoredered_map速度不是很理想。
 * OI中空间一般非常宽裕，用vector足矣。
 */

#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define MMAX 1000000
#define QMAX 100000

static int n, m, q;

#define BUFFER_SIZE 1024
static unsigned _i = BUFFER_SIZE;
static char buffer[BUFFER_SIZE];
inline char get_char() {
    if (_i == BUFFER_SIZE) {
        _i = 0;
        fread(buffer, 1, BUFFER_SIZE, stdin);
    }

    return buffer[_i++];
}

inline int readint() {
    char ch = get_char();
    for (; ch > '9' || ch < '0'; ch = get_char())
        ;
    int tmp = 0;
    for (; '0' <= ch && ch <= '9'; ch = get_char())
        tmp = tmp * 10 + int(ch) - 48;
    return tmp;
}

struct Edge {
    int id;
    int u, v, w;
};  // struct Edge

static Edge edges[MMAX + 10];

static int parent[NMAX + MMAX + 10];
static int left[NMAX + MMAX + 10];
static int right[NMAX + MMAX + 10];
static bool reversed[NMAX + MMAX + 10];
static int maxedge[NMAX + MMAX + 10];

static void initialize_lct() {
    // memset(parent, 0, sizeof(parent));
    // memset(left, 0, sizeof(left));
    // memset(right, 0, sizeof(right));
    // memset(reversed, false, sizeof(reversed));
    // memset(maxedge, 0, sizeof(maxedge));
}

inline void pushdown(int x) {
    if (x > 0 && reversed[x]) {
        swap(left[x], right[x]);

        reversed[left[x]] ^= true;
        reversed[right[x]] ^= true;
        reversed[x] = false;
    }
}

inline int choose_max(int a, int b) {
    if (a == 0 || maxedge[a] == 0) {
        return maxedge[b];
    }

    if (b == 0 || maxedge[b] == 0) {
        return maxedge[a];
    }

    assert(maxedge[a] != 0);
    assert(maxedge[b] != 0);
    assert(maxedge[a] <= m);
    assert(maxedge[b] <= m);
    if (edges[maxedge[a]].w > edges[maxedge[b]].w) {
        return maxedge[a];
    } else {
        return maxedge[b];
    }
}

inline void update(int x) {
    maxedge[x] = choose_max(left[x], right[x]);

    if (x > n) {
        int e = x - n;

        if (edges[e].w > edges[maxedge[x]].w /*|| maxedge[x] == 0*/) {
            maxedge[x] = e;
        }
    }
}

static void left_rotate(int x) {
    assert(x > 0);
    assert(left[x] > 0);
    assert(!reversed[x]);
    assert(!reversed[left[x]]);

    int y = left[x];
    left[x] = right[y];
    if (left[x] > 0)
        parent[left[x]] = x;
    right[y] = x;

    if (parent[x] > 0) {
        if (left[parent[x]] == x)
            left[parent[x]] = y;
        else
            right[parent[x]] = y;
    }

    parent[y] = parent[x];
    parent[x] = y;

    // update(x);
    // update(y);
}

static void right_rotate(int x) {
    assert(x > 0);
    assert(right[x] > 0);
    assert(!reversed[x]);
    assert(!reversed[right[x]]);

    int y = right[x];
    right[x] = left[y];
    if (right[x] > 0)
        parent[right[x]] = x;
    left[y] = x;

    if (parent[x] > 0) {
        if (left[parent[x]] == x)
            left[parent[x]] = y;
        else
            right[parent[x]] = y;
    }

    parent[y] = parent[x];
    parent[x] = y;

    // update(x);
    // update(y);
}

static void clear_marks(int x) {
    if (x <= 0)
        return;

    clear_marks(parent[x]);
    pushdown(x);
}

static void splay(int x) {
    clear_marks(x);

    while (parent[x] > 0) {
        int p1 = parent[x];
        int p2 = parent[p1];

        if (p2 <= 0) {
            if (left[p1] == x) {
                left_rotate(p1);
            } else {
                right_rotate(p1);
            }

            update(p1);
        } else {
            if (left[p1] == x) {
                if (left[p2] == p1) {
                    left_rotate(p2);
                    left_rotate(p1);
                } else {
                    left_rotate(p1);
                    right_rotate(p2);
                }
            } else {
                if (left[p2] == p1) {
                    right_rotate(p1);
                    left_rotate(p2);
                } else {
                    right_rotate(p2);
                    right_rotate(p1);
                }
            }

            update(p2);
            update(p1);
        }
    }  // while

    update(x);
}

static void access(int x) {
    assert(x > 0);

    splay(x);
    parent[right[x]] = -x;
    right[x] = 0;
    update(x);
    while (parent[x] != 0) {
        int top = -parent[x];

        assert(top > 0);
        splay(top);
        parent[right[top]] = -top;
        parent[x] = top;
        right[top] = x;
        update(top);

        x = top;
    }  // while
}

static void link(int x, int y) {
    assert((!reversed[y] && left[y] == 0) || (reversed[y] && right[y] == 0));

    access(x);
    splay(y);
    // connect(x, y);
    right[x] = y;
    parent[y] = x;
    update(x);
}

static void cut(int x, int f) {
    assert(f != 0);

    access(f);
    splay(x);
    parent[x] = 0;
}

static void make_root(int x) {
    assert(x > 0);

    access(x);
    splay(x);
    reversed[x] ^= true;
}

struct Operation {
    int id;
    int a, b;
};  // struct Operation

typedef pair<int, int> IntPair;
static vector<IntPair> hb[MMAX + 10];

inline void set_id(int x, int y, int id) {
    if (x > y) {
        hb[y].push_back(IntPair(x, id));
    } else {
        hb[x].push_back(IntPair(y, id));
    }
}

inline int find_id(int x, int y) {
    if (x > y) {
        swap(x, y);
    }

    for (int i = 0; i < hb[x].size(); i++) {
        if (hb[x][i].first == y) {
            return hb[x][i].second;
        }
    }  // for

    return 0;
}

static Edge *sorted[MMAX + 10];
static Operation op[QMAX + 10];
static bool disabled[MMAX + 10];

static bool cmp(const Edge *a, const Edge *b) {
    return a->w < b->w;
}

static void read_graph() {
    for (int i = 1; i <= m; i++) {
        edges[i].id = i;
        edges[i].u = readint();
        edges[i].v = readint();
        edges[i].w = readint();
        sorted[i] = edges + i;
        set_id(edges[i].u, edges[i].v, i);

        // printf("Edge %d -- %d (%d) / id = %d\n", sorted[i]->u, sorted[i]->v,
        // sorted[i]->w, i);
    }  // for

    sort(sorted + 1, sorted + m + 1, cmp);
}

static void read_operations() {
    // memset(disabled, false, sizeof(disabled));
    for (int i = 1; i <= q; i++) {
        op[i].id = readint();
        op[i].a = readint();
        op[i].b = readint();

        if (op[i].id == 2) {
            int e = find_id(op[i].a, op[i].b);

            disabled[e] = true;
        }
    }  // for
}

static int s[NMAX + 10];
inline int find_set(int x) {
    return x == s[x] ? x : s[x] = find_set(s[x]);
}

static void generate_mst() {
    for (int i = 1; i <= n; i++) {
        s[i] = i;
    }  // for

    int edgecnt = 0;
    int p = 1;
    while (edgecnt < n - 1) {
        Edge *e = sorted[p++];

        if (disabled[e->id]) {
            continue;
        }

        int u = find_set(e->u);
        int v = find_set(e->v);

        if (u != v) {
            // printf("Selected %d -- %d (%d)\n", e->u, e->v, e->w);

            edgecnt++;
            s[u] = v;
            make_root(e->v);
            link(e->u, e->id + n);
            link(e->id + n, e->v);
        }
    }  // while
}

static void initialize() {
    n = readint();
    m = readint();
    q = readint();

    read_graph();
    read_operations();
    initialize_lct();
    generate_mst();
}

static int stack[QMAX + 10];
static int stacksize = 1;

inline void push(int x) {
    stack[stacksize++] = x;
}

inline int pop() {
    return stack[--stacksize];
}

int main() {
    initialize();

    for (int i = q; i > 0; i--) {
        Operation &command = op[i];

        if (command.id == 1) {
            make_root(command.a);
            access(command.b);
            splay(command.b);

            assert(maxedge[command.b] != 0);
            push(edges[maxedge[command.b]].w);
        } else {
            int u = command.a;
            int v = command.b;

            make_root(u);
            access(v);
            splay(v);
            int target = maxedge[v];
            int e = find_id(u, v);

            if (edges[target].w > edges[e].w) {
                int mid = target + n;
                int a = edges[target].u;
                int b = edges[target].v;

                make_root(mid);
                cut(a, mid);
                cut(b, mid);

                make_root(v);
                link(u, e + n);
                link(e + n, v);
            }
        }
        // print();
    }  // for

    while (stacksize > 1) {
        printf("%d\n", pop());
    }  // while

    return 0;
}  // function main
