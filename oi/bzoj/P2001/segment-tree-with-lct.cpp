/**
 * TLE got
 */

#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cctype>

#include <vector>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 65536
static size_t pos = BUFFERSIZE;
static char buffer[BUFFERSIZE];

inline char _getchar() {
    if (pos == BUFFERSIZE) {
        pos = 0;
        fread(buffer, 1, BUFFERSIZE, stdin);
    }

    return buffer[pos++];
}

template <typename T>
inline T read() {
    T x = 0;
    char c = _getchar();

    while (!isdigit(c))
        c = _getchar();
    while (isdigit(c)) {
        x = x * 10 + (c - '0');
        c = _getchar();
    }

    return x;
}

#define NMAX 20000
#define MMAX 50000
#define QMAX 50000
#define LCTSIZE (NMAX + MMAX)

typedef long long int64;

struct Edge {
    int id;
    int u, v;
    int64 w;
    int depth;
};

static int mempos = 1;
static Edge edges[MMAX + QMAX + 10];

inline int allocate() {
    return mempos++;
}

class LCT {
 public:
    class Splays {
     public:
        Splays() {
            memset(father, 0, sizeof(father));
            memset(left, 0, sizeof(left));
            memset(right, 0, sizeof(right));
            memset(edge, 0, sizeof(edge));
            memset(maxedge, 0, sizeof(maxedge));
            memset(reversed, 0, sizeof(reversed));
        }

        int father[LCTSIZE + 10];
        int left[LCTSIZE + 10];
        int right[LCTSIZE + 10];
        int edge[LCTSIZE + 10];
        int maxedge[LCTSIZE + 10];
        bool reversed[LCTSIZE + 10];

        void update(int x) {
            maxedge[x] = edge[x];

            if (left[x] &&
                edges[maxedge[left[x]]].w > edges[maxedge[x]].w)
                maxedge[x] = maxedge[left[x]];
            
            if (right[x] &&
                edges[maxedge[right[x]]].w > edges[maxedge[x]].w)
                maxedge[x] = maxedge[right[x]];
        }

        void pushdown(int x) {
            if (reversed[x]) {
                swap(left[x], right[x]);
                reversed[x] = false;
                reversed[left[x]] ^= true;
                reversed[right[x]] ^= true;
            }
        }

        void clear(int x) {
            if (x > 0) {
                clear(father[x]);
                pushdown(x);
            }
        }

        void splay(int x) {
            // Simple splay
            clear(x);

            while (father[x] > 0) {
                int y = father[x];

                if (x == left[y]) {
                    left[y] = right[x];
                    father[right[x]] = y;
                    right[x] = y;
                } else {
                    right[y] = left[x];
                    father[left[x]] = y;
                    left[x] = y;
                }

                if (father[y] > 0) {
                    if (y == left[father[y]])
                        left[father[y]] = x;
                    else
                        right[father[y]] = x;
                }
                father[x] = father[y];
                father[y] = x;
                update(y);
            }

            update(x);
        }
    } sp;

    int access(int x) {
        sp.splay(x);
        sp.father[sp.right[x]] = -x;
        sp.right[x] = 0;
        sp.update(x);

        while (sp.father[x] != 0) {
            int top = -sp.father[x];
            
            sp.splay(top);
            sp.father[sp.right[top]] = -top;
            sp.father[x] = top;
            sp.right[top] = x;
            sp.update(top);
            x = top;
        }

        return x;
    }

    int find_root(int x) {
        x = access(x);

        while (true) {
            if (sp.reversed[x]) {
                if (sp.right[x])
                    x = sp.right[x];
                else
                    break;
            } else {
                if (sp.left[x])
                    x = sp.left[x];
                else
                    break;
            }
        }

        return x;
    }

    void make_root(int x) {
        x = access(x);
        sp.reversed[x] ^= true;
    }

    void link(int x, int y) {
        make_root(y);
        sp.splay(y);
        sp.father[y] = -x;
        // access(y);
    }

    void cut(int x, int y) {
        access(y);
        sp.splay(x);
        sp.father[x] = 0;
    }
};

struct Node {
    Node (int l, int r)
        : left(l), right(r),
          leftchild(NULL),
          rightchild(NULL) {}

    int left;
    int right;
    vector<int> edges;
    Node *leftchild;
    Node *rightchild;
};

static Node *build(int left, int right) {
    Node *x = new Node(left, right);

    if (left < right) {
        int mid = (left + right) / 2;
        x->leftchild = build(left, mid);
        x->rightchild = build(mid + 1, right);
    }

    return x;
}

static void modify(Node *x, int left, int right, int e) {
    if (edges[e].u == edges[e].v)
        return;

    if (left <= x->left && x->right <= right)
        x->edges.push_back(e);
    else {
        int mid = (x->left + x->right) / 2;

        if (left <= mid)
            modify(x->leftchild, left, right, e);
        if (right > mid)
            modify(x->rightchild, left, right, e);
    }
}

static int n, m, q;
static Node *tree;
static LCT lct;
static int start[MMAX + 10];
static int last[MMAX + 10];
static int64 answer[QMAX + 10];

static void initialize() {
    // scanf("%d%d%d", &n, &m, &q);
    n = read<int>();
    m = read<int>();
    q = read<int>();
    tree = build(0, q);

    for (int i = 1; i <= m; i++) {
        // Edge *e = new Edge;
        int e = allocate();
        // scanf("%d%d%lld", &e->u, &e->v, &e->w);
        edges[e].u = read<int>();
        edges[e].v = read<int>();
        edges[e].w = read<int64>();
        edges[e].id = i;
        start[i] = 0;
        last[i] = e;
    }

    for (int i = 1; i <= q; i++) {
        int k;
        int64 d;
        // scanf("%d%lld", &k, &d);
        k = read<int>();
        d = read<int64>();

        int e = last[k];
        // Edge *ne = new Edge;
        int ne = allocate();
        edges[ne] = edges[e];
        edges[ne].w = d;
        modify(tree, start[k], i - 1, e);
        start[k] = i;
        last[k] = ne;
    }

    for (int i = 1; i <= m; i++) {
        modify(tree, start[i], q, last[i]);
    }
}

inline void cut_edge(int id) {
    Edge &e = edges[id];

    lct.make_root(n + e.id);
    if (lct.find_root(e.u) == n + e.id) {
        lct.cut(e.u, n + e.id);
        lct.cut(e.v, n + e.id);
    }
}

inline void add_edge(int id) {
    Edge &e = edges[id];

    lct.sp.edge[n + e.id] = lct.sp.maxedge[n + e.id] = id;
    lct.make_root(e.u);
    lct.make_root(e.v);
    lct.sp.splay(e.u);
    lct.sp.splay(e.v);
    lct.sp.father[e.u] = -(n + e.id);
    lct.sp.father[e.v] = -(n + e.id);
}

static void dfs(Node *x, int64 sum = 0, int depth = 0) {
    vector<int> removed;
    vector<int> added;

    for (size_t i = 0; i < x->edges.size(); i++) {
        int id = x->edges[i];
        Edge &e = edges[id];

        if (lct.find_root(e.u) == lct.find_root(e.v)) {
            lct.make_root(e.u);
            int top = lct.access(e.v);
            int maxid = lct.sp.maxedge[top];
            Edge &maxe = edges[maxid];

            if (maxe.w <= e.w)
                continue;

            cut_edge(maxid);
            sum -= maxe.w;

            if (maxe.depth != depth)
                removed.push_back(maxid);
        }

        e.depth = depth;
        add_edge(id);
        sum += e.w;
        added.push_back(id);
    }

    if (x->left < x->right) {
        dfs(x->leftchild, sum, depth + 1);
        dfs(x->rightchild, sum, depth + 1);
    } else
        answer[x->left] = sum;

    if (depth > 0) {
        for (size_t i = 0; i < added.size(); i++) {
            int e = added[i];
            cut_edge(e);
        }

        for (size_t i = 0; i < removed.size(); i++) {
            int e = removed[i];
            add_edge(e);
        }
    }
}

int main() {
    // freopen("hnoi2010_city.in", "r", stdin);
    // freopen("hnoi2010_city.out", "w", stdout);
    initialize();

    edges[0].w = -1;
    for (int i = 1; i <= LCTSIZE; i++) {
        lct.sp.edge[i] = lct.sp.maxedge[i] = 0;
    }

    dfs(tree);

    for (int i = 1; i <= q; i++) {
        printf("%lld\n", answer[i]);
    }

    return 0;
}
