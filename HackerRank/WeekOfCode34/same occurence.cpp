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
const int MaxN = 8010, MaxM = 501234;
int n, b[MaxN], a[MaxN], q; LL f[MaxN][MaxN];
int px[MaxN], py[MaxN], c[MaxN], sc[MaxN << 1];
vector<int> t[MaxN]; 
int main() {
	int i, j, x, y, xn;
	n = inp(); q = inp();
	for(i = 1; i <= n; i++) scanf("%d", a + i), b[i] = a[i]; //a[i] = b[i] = inp();
	sort(b + 1, b + n + 1); xn = unique(b + 1, b + n + 1) - b - 1;
	for(i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + xn + 1, a[i]) - b;
	for(i = 1; i <= n; i++) t[a[i]].push_back(i);
	for(x = 1; x <= xn + 1; x++) {
		for(y = x + (x != xn + 1); y <= xn + 1; y++){
			int cn = 0;
			for(i = j = 0; i < t[x].size() || j < t[y].size(); )
				if(i < t[x].size() && j < t[y].size()) {
					if(t[x][i] < t[y][j])  c[++cn] = t[x][i++];
					else c[++cn] = t[y][j++];
				}
				else
					if(i < t[x].size()) c[++cn] = t[x][i++];
					else c[++cn] = t[y][j++];
			for(i = 1; i <= cn; i++) 
				px[i] = px[i - 1] + (a[c[i]] == x), 
				py[i] = py[i - 1] + (a[c[i]] == y);
			c[cn + 1] = n + 1;
			for(i = 0; i <= cn; i++) 
				sc[py[i] - px[i] + MaxN] += c[i + 1] - c[i];
			for(i = 0; i <= cn; i++){
				int p = sc[py[i] - px[i] + MaxN];
				f[x][y] += (LL) p * (p - 1) >> 1;
				sc[py[i] - px[i] + MaxN] = 0;
			}
			f[y][x] = f[x][y];
		}
	}
	for(i = 1; i <= q; i++){
		int x0, y0;
		scanf("%d %d", &x0, &y0);
		//x = inp(); y = inp();
		x = lower_bound(b + 1, b + xn + 1, x0) - b;
		y = lower_bound(b + 1, b + xn + 1, y0) - b;
		if(b[x] != x0) x = xn + 1;
		if(b[y] != y0) y = xn + 1;
		if(x == y) printf("%lld\n", (LL) n * (n + 1) >> 1);
		else{
			assert(f[x][y] > 0);
			printf("%lld\n", f[x][y]);
		}
	}
	return 0;
}



