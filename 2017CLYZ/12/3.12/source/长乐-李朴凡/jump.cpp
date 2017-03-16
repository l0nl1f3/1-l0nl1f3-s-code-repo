#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN = 1205;
int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2}, dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
int n, m, i, j, k, l, q[22000005][2], f[1205][1205];
bool e[MAXN][MAXN];
int a[9] = {0, 3, 2, 3, 2, 3, 4, 5, 4}, b[4] = {0, 2, 4, 2};
int main()
{
	freopen("jump.in", "r", stdin);
	freopen("jump.out", "w", stdout);
	int T;
	q[1][0] = 100; q[1][1] = 100;
	e[100][100] = 1;
	memset(f, 127 / 3, sizeof(f));
	f[100][100] = 0;
	int w = 1;
	for(int gzb = 1; gzb <= w; ++ gzb)
	{
		for(i = 0; i < 8; i ++)
		{
			int x = dx[i] + q[gzb][0];
			int y = dy[i] + q[gzb][1];
			if (x >= 0 && x <= 1200 && y >= 0 && y <= 1200 && f[x][y] > 1 + f[q[gzb][0]][q[gzb][1]])
			{
				f[x][y] = f[q[gzb][0]][q[gzb][1]] + 1;
				if (!e[x][y])
				{
					e[x][y] = 1;
					q[++w][0] = x;
					q[w][1] = y;
					if (f[x][y] < f[q[gzb + 1][0]][q[gzb + 1][1]])
						swap(q[gzb + 1][0], q[w][0]), swap(q[gzb + 1][1], q[w][1]);
				}
			}
		}
		e[q[gzb][0]][q[gzb][1]] = 0;
	}
	cin >> T;
	while (T --)
	{
		scanf("%d%d", &n, &m);
		if (!m)
		{
			if (n <= 8) printf("%d\n", a[n]);
			else {
				int jj = (n - 8) / 4 + (n % 4 != 0);
				jj *= 2;
				int jb = n % 4;
				while (jb <= 4) jb += 4;
				printf("%d\n", jj + a[jb]);
			}
			continue;
		}
		if (n == m)
		{
			if (n <= 3) printf("%d\n", b[n]);
			else {
				int jb = n / 3 - (n % 3 == 0);
				printf("%d\n", (jb + 1) * 2);
			}
			continue;
		}
		printf("%d\n", f[n + 100][m + 100]);
	}
	/*for(i = 0; i <= 50; i ++)
	{
		for(j = 0; j <= 50; j ++)
			printf("%2d ", f[i + 100][j + 100]);
		//	cout << f[i + 100][j + 100] << " ";
		cout << endl;
	}*/
}
