#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

static i64 L[100][100] =
{{0},
{0,1,1,1,2,1,1,1,1,1,1,1,2,1,1,1},
{0,1,1,1,1,1,3,1,1,1,3,1,1,1,1,1},
{0,1,1,1,1,1,1,2,1,2,1,1,1,1,1,1},
{0,2,1,1,1,1,1,1,2,1,1,1,1,1,1,2},
{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{0,1,3,1,1,1,1,1,1,1,1,1,1,1,3,1},
{0,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1},
{0,1,1,1,2,1,1,1,1,1,1,1,2,1,1,1},
{0,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1},
{0,1,3,1,1,1,1,1,1,1,1,1,1,1,3,1},
{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{0,2,1,1,1,1,1,1,2,1,1,1,1,1,1,2},
{0,1,1,1,1,1,1,2,1,2,1,1,1,1,1,1},
{0,1,1,1,1,1,3,1,1,1,3,1,1,1,1,1},
{0,1,1,1,2,1,1,1,1,1,1,1,2,1,1,1}};

static i64 W[100][100] =
{{0},
{0,3,1,1,1,1,1,1,3,1,1,1,1,1,1,3},
{0,1,2,1,1,1,1,1,1,1,1,1,1,1,2,1},
{0,1,1,2,1,1,1,1,1,1,1,1,1,2,1,1},
{0,1,1,1,2,1,1,1,1,1,1,1,2,1,1,1},
{0,1,1,1,1,2,1,1,1,1,1,2,1,1,1,1},
{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{0,3,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{0,1,1,1,1,2,1,1,1,1,1,2,1,1,1,1},
{0,1,1,1,2,1,1,1,1,1,1,1,2,1,1,1},
{0,1,1,2,1,1,1,1,1,1,1,1,1,2,1,1},
{0,1,2,1,1,1,1,1,1,1,1,1,1,1,2,1},
{0,3,1,1,1,1,1,1,3,1,1,1,1,1,1,3}};

static i64 M[1000] = {0,1,3,2,3,2,1,5,5,1,2,2,2,2,1,1,2,2,2,2,3,10,5,10,5,10,10,10,5,5,10,10,3};

static i64 S[100];
static int mat[100][100];

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	int t = 1;
	while (m--) {
		int w, used = 0;
		scanf("%d", &w);
		while (w--) {
			int c;
			scanf("%d", &c);
			char d;
			do {
				d = getchar();
			} while (d != 'h' && d != 'v');
			int x, y;
			scanf("%d%d", &x, &y);
            swap(x, y);
            int dx = d == 'v' ? 1 : 0;
            int dy = d == 'h' ? 1 : 0;
            i64 sum = 0, prod = 1;
            while (c--) {
                int v;
                scanf("%d", &v);
                if (!mat[x][y]) {
                    used++;
                    //S[t] += M[v] * L[x][y];
                }
                sum += M[v] * L[x][y];
                mat[x][y] = v;
                //sum += M[v];
                prod *= W[x][y];
                x += dx;
                y += dy;
            }
            S[t] += sum * prod;
		}
        if (used == 7) S[t] += 15;
        t++;
        if (t > n) t = 1;
	}

    for (int i = 1; i <= n; i++)
        printf("%lld\n", S[i]);

	return 0;
}
