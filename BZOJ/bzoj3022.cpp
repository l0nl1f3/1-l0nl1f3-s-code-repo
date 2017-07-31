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

const int MaxN = 301234, MaxM = MaxN << 2;

int n, m, ls[MaxN];
pair<int, int> a[MaxN];

struct query{ int a, k, i;}q[MaxN];
bool cmp(query x, query y) {
	return x.a < y.a;
}
int g[MaxM][2], c[MaxM][2]; LL s[MaxM][2];

void modify(int p, int l, int r, int q, int d){
	if(l == r){
		g[p][0] = c[p][0] = 1; s[p][0] = d;
		return;
	}
	if(q <= l + r >> 1) 
		modify(p << 1, l, l + r >> 1, q, d);
	else 
		modify(p << 1 | 1, (l + r >> 1) + 1, r, q, d);
		
	for(int o = 0; o < 2; o++){
		int t = g[p << 1 | 1][o];
		g[p][o] = g[p << 1][t];
		c[p][o] = c[p << 1 | 1][o] + c[p << 1][t];
		s[p][o] = s[p << 1 | 1][o] + s[p << 1][t];
	}
}

LL ans[MaxN];
LL query(int p, int l, int r, int k, int o = 0){
	if(k >= c[p][o]) return s[p][o];
	if(l == r) return 0;
	if(k <= c[p << 1 | 1][o])
		return query(p << 1 | 1, (l + r >> 1) + 1, r, k, o);
	else {
		return s[p << 1 | 1][o] + 
		query(p << 1, l, l + r >> 1, k - c[p << 1 | 1][o], g[p << 1 | 1][o]);
	}
} 
int main() {
	int i, j;
	n = inp();
	for(i = 1; i <= n; i++)
		scanf("%d %d", &a[i].fir, &a[i].sec), ls[i] = a[i].sec;
	sort(a + 1, a + n + 1); 
	sort(ls + 1, ls + n + 1);
	
	m = inp();
	for(i = 1; i <= m; i++) 
		scanf("%d %d", &q[i].a, &q[i].k), q[i].i = i;
	
	sort(q + 1, q + m + 1, cmp);
	
	for(i = 1, j = 1; i <= m; i++){
		while(j <= n && a[j].fir <= q[i].a)
			modify(1, 1, n, lower_bound(ls + 1, ls + n + 1, a[j].sec) - ls, a[j].sec), j++;
		ans[q[i].i] = query(1, 1, n, q[i].k);
	}
	
	for(i = 1; i <= m; i++) printf("%lld\n", ans[i]);
	return 0;
}



