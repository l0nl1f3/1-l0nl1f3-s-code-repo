#include <set>
#include <ctime>
#include <queue>
#include <cstdio>
#include <iostream>
using namespace std;
const int MaxN = 2020;
int T, a[MaxN][MaxN], X, Y;
int xx[8] = {1, 1, -1, -1, 2, 2, -2, -2};
int yy[8] = {2, -2, 2, -2, 1, -1, 1, -1};
queue <pair <int, int> > Q;
void solve() {
	for (int i = 0; i <= 2000; ++i)
		for (int j = 0; j <= 2000; ++j)
			a[i][j] = -1;
	a[1000][1000] = 0, Q.push(make_pair(1000, 1000));
	while (!Q.empty()) {
		pair <int, int> u = Q.front();
		Q.pop();
		for (int k = 0; k < 8; ++k) {
			int x = u.first + xx[k], y = u.second + yy[k];
			if (x < 0 || x > 2000) continue;
			if (y < 0 || y > 2000) continue;
			if (a[x][y] < 0) {
				a[x][y] = a[u.first][u.second] + 1;
				Q.push(make_pair(x, y));
			}
		}
	}
}
int main() {
	freopen("jump.in", "r", stdin);
	freopen("jump.out", "w", stdout);
	scanf("%d", &T);
	solve();
	while (T--) {
		scanf("%d%d", &X, &Y);
		if (X < 0) X = -X;
		if (Y < 0) Y = -Y;
		if (X > Y) swap(X, Y);
		if (X <= 1000 && Y <= 1000) printf("%d\n", a[X + 1000][Y + 1000]);
		else 
			if (X == Y) printf("%d\n", (X + 2) / 3 * 2);
			else
			if (X == 0) printf("%d\n", (Y + 2) / 4 * 2 + Y % 2);
	}
	fclose(stdin);
	fclose(stdout);
}