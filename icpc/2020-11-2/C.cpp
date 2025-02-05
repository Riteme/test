#include <cstdio>
#include <cstring>

#include <unordered_map>
#include <algorithm>

using namespace std;

constexpr int NMAX = 110000;
constexpr int S = 26;

int mcnt;
struct node {
	int pa, top, dep, wson;
	int ch[S];
} m[NMAX + 10];

int n, tr;
char buf[NMAX + 10];

int allocate() {
	memset(m + mcnt, 0, sizeof(node));
	return mcnt++;
}

int insert(int x, char *s) {
	for (int i = 0; s[i]; i++) {
		int c = s[i] - 'a';
		if (!m[x].ch[c])
			m[x].ch[c] = allocate();
		int y = x;
		x = m[x].ch[c];
		m[x].pa = y;
	}
	return x;
}

void dfs1(int x) {
	m[x].top = 1;
	for (int c = 0; c < S; c++) {
		int v = m[x].ch[c];
		if (v) {
			m[v].dep = m[x].dep + 1;
			dfs1(v);
			m[x].top += m[v].top;
		}
	}
}

void dfs2(int x) {
	int u = 0;
	for (int c = 0; c < S; c++) {
		int v = m[x].ch[c];
		if (v && m[v].top > m[u].top)
			u = v;
	}
	m[x].wson = u;
	if (u) {
		m[u].top = m[x].top;
		dfs2(u);
	}
	for (int c = 0; c < S; c++) {
		int v = m[x].ch[c];
		if (!v || v == u)
			continue;
		m[v].top = v;
		dfs2(v);
	}
}

int lca(int x, int y) {
	while (m[x].top != m[y].top) {
		if (m[m[x].top].dep < m[m[y].top].dep)
			swap(x, y);
		x = m[m[x].top].pa;
	}
	return m[x].dep < m[y].dep ? x : y;
}

int below(int x, int y) {
	while (m[x].top != m[y].top) {
		x = m[x].top;
		if (m[x].pa == y)
			return x;
		x = m[x].pa;
	}
	return m[y].wson;
}

int col[NMAX + 10], pt[NMAX + 10];
int out[NMAX + 10];
unordered_map<int, int> rt;
bool mark[NMAX + 10], del[NMAX + 10];

int ans, cnt;
bool dfs3(int x) {
	bool ok = false;
	if (mark[x]) {
		ok = true;
		cnt++;
		out[x]++;
	}
	
	for (int c = 0; c < S; c++) {
		int v = m[x].ch[c];
		if (!v || del[v])
			continue;
		if (dfs3(v)) {
			ok = true;
		}
		out[x] += out[v];
	}

	return ok;
}

bool used[NMAX + 10];

void dfs4(int x) {
	if (!out[x])
		return;

	ans++;
	for (int c = 0; c < S; c++) {
		int v = m[x].ch[c];
		if (!v || !out[v])
			continue;
		dfs4(v);
	}

	if (out[x] == 1 && m[x].pa) {
		int p = m[x].pa;
		if (!mark[p] && !used[p]) {
			used[p] = 1;
			ans--;
		}
	}
}

void _main() {
	mcnt = 1;
	scanf("%d", &n);
	tr = allocate();
	for (int i = 1; i <= n; i++) {
		int v;
		scanf("%s%d", buf, &v);
		col[i] = v;
		pt[i] = insert(tr, buf);
	}

	dfs1(tr);
	m[tr].top = tr;
	dfs2(tr);

	memset(mark + 1, 0, mcnt);
	memset(del + 1, 0, mcnt);
	memset(out + 1, 0, sizeof(int) * mcnt);
	memset(used + 1, 0, mcnt);
	rt.clear();
	for (int i = 1; i <= n; i++) {
		if (!rt.count(col[i]))
			rt[col[i]] = pt[i];
		else {
			rt[col[i]] = lca(pt[i], rt[col[i]]);
		}
	}

	for (auto &e : rt) {
		int p = e.second;
		mark[p] = 1;
	}
	for (int i = 1; i <= n; i++) {
		int p = rt[col[i]];
		if (pt[i] == p)
			continue;
		int v = below(pt[i], p);
		del[v] = 1;
	}

	ans = cnt = 0;
	dfs3(tr);

	if (cnt != (int) rt.size())
		puts("-1");
	else {
		dfs4(tr);
		printf("%d\n", ans);
	}
}

int main() {
	int T;
	scanf("%d", &T);
	for (int i = 1; i <= T; i++) {
		printf("Case #%d: ", i);
		_main();
	}
	return 0;
}
