#include<bits/stdc++.h>

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
const int MAXN = 401234, MAXM = MAXN << 2;

int n, x, y, z, m, P, s[MAXN], o[MAXN], a[MAXN], l[MAXN], r[MAXN], K[MAXN], R[MAXN];
int v[MAXN], vv[MAXN], c[MAXN], cc[MAXN], ans[MAXN];
struct tag{
	int v, c;
	void push_down(tag & ls, tag & rs){
		if(!c) return;
		ls.c += c; ls.v += c; 
		rs.c += c; rs.v += c; 
		c = 0;
	}
}fs[MAXM], gs[MAXM];
int mrg(int p){
	fs[p].v = min(fs[p + p].v, fs[p + p + 1].v);
	gs[p].v = max(gs[p + p].v, gs[p + p + 1].v);
}
int pushdown(int p){
	fs[p].push_down(fs[p + p], fs[p + p + 1]);
	gs[p].push_down(gs[p + p], gs[p + p + 1]); 
}
#define o (l + r >> 1)
void build(int p, int l, int r){
	if(l == r) fs[p].v = s[l], gs[p].v = s[l];
	else{
		build(p + p, l, o);
		build(p + p + 1, o + 1, r);
		mrg(p);
	}
}
void modify(int p, int l, int r, int a, int b, int c, int q){
	if(b < l || a > r) return;
	if(a <= l && r <= b){
		if(q)fs[p].c += c, fs[p].v += c;
		else gs[p].c += c, gs[p].v += c;
		return;
	}
	pushdown(p);
	modify(p + p, l, o, a, b, c, q);
	modify(p + p + 1, o + 1, r, a, b, c, q);
	mrg(p);
} 
int query(int p, int l, int r, int a, int b,int q) {
	if(b < l || a > r) return q ? 1e9 : -1e9;
	if(a <= l && r <= b) 
		return q ? fs[p].v : gs[p].v;
	pushdown(p);
	if(q) return min(query(p + p, l, o, a, b, q) ,query(p + p + 1, o + 1, r, a, b, q)); 
	else  return max(query(p + p, l, o, a, b, q) ,query(p + p + 1, o + 1, r, a, b, q));
} 
#undef o
struct Query{ int t,i;}q[MAXM];
bool cmp(Query a, Query b){ return r[a.t] < r[b.t];}
bool pmc(Query a, Query b){ return a.t < b.t; }
int main() {
	int i, j, k;
	n = inp();
	x = inp(); y = inp(); z = inp(); P = inp();
	for(i = 1; i <= n; i++)
		a[i] = ((i - x) * (i - x) % P + (i - y) * (i - y) % P + (i - z) * (i - z) % P) %P, s[i] = s[i - 1] + a[i];
	m = inp();
	K[1] = inp(); K[2] = inp(); x = inp(); y = inp(); z = inp(); P = inp();
	for(i = 3; i <= m; i++) K[i] = (x * K[i - 1] + y * K[i - 2] + z) % P;
	for(i = 1; i <= m; i++) l[i] = inp(), r[i] = inp();
	
	build(1, 0, n);
	for(i = 1; i <= n; i++){
		int F, G;
		F = query(1, 0, n, r[i], n, 1);
		G = query(1, 0, n, 0, l[i] - 1, 0);
		ans[i] = min(K[i], F - G);
		modify(1, 0, n, r[i], n, -ans[i], 1);
		modify(1, 0, n, l[i], n, -ans[i], 0);
	} 
	for(i = 1; i <= m; i++) printf("%d\n", ans[i]);
	return 0;
}



