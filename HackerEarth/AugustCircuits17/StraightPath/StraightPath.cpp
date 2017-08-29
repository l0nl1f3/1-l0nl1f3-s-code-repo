#include <bits/stdc++.h>

#define fir first
#define sec second
using namespace std;
typedef long long LL;

template <typename T> inline bool cmin(T & a, const T & b) { return a > b ? a = b, 1 : 0;}
template <typename T> inline bool cmax(T & a, const T & b) { return a < b ? a = b, 1 : 0;}
int inp() {
	int x = 0, f = 1;char ch;
	for(ch = getchar(); !isdigit(ch); ch = getchar())
		if(ch == '-') f = -1;
	for(; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	return x * f;
}

const int MaxN = 1234;

int n, m, sx, sy, tx, ty; 
char mp[MaxN][MaxN];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, 1, -1};

struct info {
	int x, y, d;
	info() {}
	info(int x, int y, int d) : x(x), y(y), d(d) {
	}
};
info q[MaxN * MaxN * 10]; int qh, qt;
int f[MaxN][MaxN][4];

int main() {
	int i, j;
	n = inp(); m = inp();
	for(i = 1; i <= n; i++) scanf("%s", mp[i] + 1);
	for(i = 1; i <= n; i++) 
		for(j = 1; j <= m; j++) {
			if(mp[i][j] == 'V') sx = i, sy = j;
			if(mp[i][j] == 'H') tx = i, ty = j;
		}
	
	qh = qt = MaxN * MaxN * 4;
	for(i = 0; i < 4; i++)
		f[sx][sy][i] = 1, q[++qt] = (info(sx, sy, i));
	 
	while(qh < qt){ 
		info c = q[++qh];
		//cout << c.x << " " << c.y << endl;
		for(i = 0; i < 4; i++) {
			if(i == c.d) continue;
			int nx = c.x + dx[i];
			int ny = c.y + dy[i];
			if(mp[nx][ny] && mp[nx][ny] != '*') {
				if(!f[nx][ny][i] || f[nx][ny][i] > f[c.x][c.y][c.d] + 1)
					f[nx][ny][i] = f[c.x][c.y][c.d] + 1, 
					q[++qt] = info(nx, ny, i);
			}
		}	
		
		int nx = c.x + dx[c.d];
		int ny = c.y + dy[c.d];
		
		if(mp[nx][ny] && mp[nx][ny] != '*')
			if(!f[nx][ny][c.d] || f[nx][ny][c.d] > f[c.x][c.y][c.d])
				f[nx][ny][c.d] = f[c.x][c.y][c.d], q[qh--] = info(nx, ny, c.d);
	}
	int ans = ~0U >> 1;
	for(i = 0; i < 4; i++)
	if(f[tx][ty][i]) cmin(ans, f[tx][ty][i]);
	if(ans == (~0U >> 1)) return puts("-1"), 0;
	cout << ans - 1;	
	return 0;
}



