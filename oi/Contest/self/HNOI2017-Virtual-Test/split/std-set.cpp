// #define USE_FILE_IO
#define NDEBUG

#define NAME "split"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <set>
#include <vector>
#include <algorithm>

using namespace std;

#define WMAX 30
#define NMAX 900
#define EMAX 2000

struct Edge {
    Edge(int _u, int _v, int _c, int _w)
        : u(_u), v(_v), c(_c), w(_w) {}

    int u, v, c, w;

    int either(int x) {
        return u == x ? v : u;
    }

    int &select(int x) {
        return u == x ? u : v;
    }
};

struct Graph {
    Graph() {
        edges.reserve(EMAX);
    }

    Graph &operator=(const Graph &g) {
        edges = g.edges;

        for (int i = 1; i <= NMAX; i++) {
            adj[i].clear();
        }

        for (size_t i = 0; i < edges.size(); i++) {
            Edge *e = &edges[i];
            adj[e->u].push_back(e);
            adj[e->v].push_back(e);
        }

        return *this;
    }

    vector<Edge> edges;
    vector<Edge *> adj[NMAX + 10];

    void link(int u, int v, int c, int w) {
        edges.push_back(Edge(u, v, c, w));
        Edge *e = &edges[edges.size() - 1];
        adj[u].push_back(e);
        adj[v].push_back(e);
    }

    void merge(int u, int v) {
        for (size_t i = 0; i < adj[v].size(); i++) {
            Edge *e = adj[v][i];

            if (e->either(v) != u) {
                e->select(v) = u;
                adj[u].push_back(e);
            }
        }
    }

    vector<Edge *> &operator[](const int u) {
        return adj[u];
    }
};

template <typename TCompare>
struct Heap {
    void push(int x) {
        s.insert(x);
    }

    void pop(int x) {
        typename set<int, TCompare>::iterator iter = s.find(x);

        assert(iter != s.end());
        s.erase(iter);
    }

    void pop() {
        s.erase(s.begin());
    }

    int top() {
        return *s.begin();
    }

    size_t size() {
        return s.size();
    }

    set<int, TCompare> s;
};

static int n, m, money;
static Graph N;
static int tail;
static int sorted[EMAX + 10];

inline int id(int i, int j) {
    return (i - 1) * m + j;
}

void initialize() {
    scanf("%d%d%d", &n, &m, &money);

    tail = 2;
    sorted[1] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < m; j++) {
            int c, w;
            scanf("%d%d", &c, &w);
            sorted[tail++] = c;
            N.link(id(i, j), id(i, j + 1), c, w);
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= m; j++) {
            int c, w;
            scanf("%d%d", &c, &w);
            sorted[tail++] = c;
            N.link(id(i, j), id(i + 1, j), c, w);
        }
    }

    sort(sorted + 1, sorted + tail);
    tail = unique(sorted + 1, sorted + tail) - sorted;

    n = id(n, m);
}

static Graph G;
static int limit;
static int marked[NMAX + 10];
static int visited[NMAX + 10];
static int weight[NMAX + 10];

struct cmp {
    bool operator()(const int a, const int b) const {
        return weight[a] > weight[b] ||
              (weight[a] == weight[b] && a < b);
    }
};

int maximum_adjacency_search(int &s, int &t) {
    memset(weight, 0, sizeof(weight));
    memset(visited, 0, sizeof(visited));

    Heap<cmp> q;
    for (int u = 1; u <= n; u++) {
        if (!marked[u])
            q.push(u);
    }

    while (q.size() > 1) {
        int u = q.top();
        q.pop();

        s = u;
        visited[u] = true;
        for (size_t i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->either(u);

            if (e->c > limit || visited[v] || marked[v])
                continue;

            q.pop(v);
            weight[v] += e->w;
            q.push(v);
        }
    }

    t = q.top();
    return weight[t];
}

int mincut(int cnt) {
    if (cnt < 2)
        return INT_MAX;

    int s, t;
    int w = maximum_adjacency_search(s, t);
    G.merge(s, t);
    marked[t] = true;
    return min(w, mincut(cnt - 1));
}

bool test(int w) {
    limit = w;

    G.edges.clear();
    for (int u = 1; u <= n; u++) {
        G[u].clear();
    }

    for (size_t i = 0; i < N.edges.size(); i++) {
        Edge &e = N.edges[i];

        if (e.c <= w) {
            G.edges.push_back(e);

            Edge *ptr = &G.edges[G.edges.size() - 1];
            G[e.u].push_back(ptr);
            G[e.v].push_back(ptr);
        }
    }

    memset(marked, 0, sizeof(marked));
    return mincut(n) > money;
}

int main() {
    freopen(NAME ".in", "r", stdin);
#ifdef USE_FILE_IO
    freopen(NAME ".in", "r", stdin);
    freopen(NAME ".out", "w", stdout);
#endif
    initialize();

    int left = 1, right = tail - 1;
    while (left + 1 < right) {
        int mid = (left + right) / 2;

        if (test(sorted[mid]))
            right = mid;
        else
            left = mid + 1;
    }

    if (left != right && !test(sorted[left]))
        left = right;

    if (!test(sorted[left]))
        puts("-1");
    else
        printf("%d\n", sorted[left]);

    return 0;
}

