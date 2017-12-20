#include <bits/stdc++.h>

#define fir first
#define sec second
using namespace std;
typedef long long LL;
typedef unsigned long long u64;

template <typename T> inline bool cmin(T & a, const T & b) { return a > b ? a = b, 1 : 0;}
template <typename T> inline bool cmax(T & a, const T & b) { return a < b ? a = b, 1 : 0;}
int read() {
	int x = 0, f = 1;char ch;
	for(ch = getchar(); !isdigit(ch); ch = getchar())
		if(ch == '-') f = -1;
	for(; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	return x * f;
}

const int MaxN = 2333;

int r, c, a[MaxN][MaxN], ed[MaxN];

int nxt(int x, int y) {
	int mx = 0, my = 0;
	for(int t = x - 1; t <= x + 1; t++) 
		if(cmax(mx, a[(t + r) % r][(y + 1) % c]))
			my = (t + r) % r;
	return my;
}

int gao(int x, int y) {
	while(y < c) {
		x = nxt(x, y);
		y++;
	} y = 0;
	return x;
}

#define tm tmd
int px, py, clk, vis[MaxN], tm[MaxN];

void move(int K) {
	if(K >= c - py) {
		K -= c - py;
		px = gao(px, py); py = 0;
	}
	++clk;
	while(K >= c) {
		K -= c; px = ed[px];
		if(vis[px] == clk) {
			int L = tm[px] - K;
			if(K >= L) 
				K -= (K / L) * L;
		}
		vis[px] = clk; tm[px] = K;
	}
	while(K--) {
		px = nxt(px, py);
		py = (py + 1) % c;
	}
}

void update(int x, int y) {
	int 
}

int main() {
	int i, j, k;
	r = read(); c = read();
	for(i = 0; i < r; i++)
		for(j = 0; j < c; j++)
			a[i][j] = read();
	for(i = 0; i < r; i++)
		ed[i] = gao(i, 0);
	px = py = 0; int q = read();
	while(q--) {
		int op, x, y, K;
		char s[10]; scanf("%s", s);
		if(s[0] == 'm') {
			K = read();
			move(K);
			printf("%d %d\n", px + 1, py +1);
		}else {
			x = read() - 1; y = read() - 1;
			a[x][y] = read();
			for(i = x - 1; i <= x + 1; i++) 
				update((x + r) % r, (y - 1 + r) % r);
		}
	}
	return 0;
}

