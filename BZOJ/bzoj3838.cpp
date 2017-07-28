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
const int MaxN = 501234, MaxM = MaxN << 2;
int n, K, a[MaxN], b[MaxN];
struct info {
	int l, r;
	info(){}
	info(int l, int r):l(l), r(r){} 
}A[MaxM], B[MaxM], C[MaxM];
int seg[MaxM], tag[MaxM], a0[MaxM], b0[MaxM], a1[MaxM], b1[MaxM];
void push_down(int p){
	if(!tag[p]) return;
	seg[p + p] += tag[p]; seg[p + p + 1] += tag[p];
	tag[p + p + 1] += tag[p]; tag[p + p] += tag[p];
	tag[p] = 0;
} 
info operator + (info x, info y){
	return a[x.l] + b[x.r] < a[y.l] + b[y.r] ? x : y;
}
int Min(int a, int b, int *c){
	return c[a] < c[b] ? a : b;
}
void push_up(int p, int l, int r){
	A[p] = A[l] + A[r] + info(a0[l], b0[r]);
	B[p] = B[l] + B[r];
	C[p] = C[l] + C[r] + info(a0[r], b0[l]);
	a0[p] = Min(a0[l], a0[r], a);
	b0[p] = Min(b0[l], b0[r], b);
	seg[p] = min(seg[l], seg[r]);
	if(seg[l] == seg[r]) {
		B[p] = B[p] + info(a1[r], b1[l]);
		a1[p] = a1[l]; b1[p] = b1[r];
	}
	if(seg[l] < seg[r]){
		B[p] = B[p] + C[r] + info(a0[r], b1[l]);
		a1[p] = a1[l]; b1[p] = Min(b0[r], b1[l], b);
	}
	if(seg[l] > seg[r]){
		B[p] = B[p] + C[l] + info(a1[r], b0[l]);
		b1[p] = b1[r]; a1[p] = Min(a0[l], a1[r], a);
	} 	
}
void build(int p, int l, int r){
	if(l == r){
		A[p] = C[p] = info(l, l); B[p] = info();
		a0[p] = b0[p] = a1[p] = l;
	}else
		build(p + p, l, l + r >> 1),
		build(p + p + 1, (l + r >> 1) + 1, r), 
		push_up(p, p + p, p + p + 1);
}
void seg_modify(int p, int l, int r, int a, int b, int d){
	if(b < l || a > r) return;
	if(a <= l && r <= b) { seg[p] += d, tag[p] += d; return; }
	push_down(p);
	seg_modify(p + p, l, l + r >> 1, a, b, d);
	seg_modify(p + p + 1, (l + r >> 1) + 1, r, a, b ,d);
	push_up(p, p + p, p + p + 1);
} 
void sig_modify(int p, int l, int r, int q){
	if(l == r) return;
	push_down(p);
	if(q <= (l + r >> 1)) sig_modify(p + p, l, l + r >> 1, q);
	else sig_modify(p + p + 1, (l + r >> 1) + 1, r, q);
	push_up(p, p + p, p + p + 1);
}
int main() {
	int i; LL ans = 0;
	n = inp(); K = inp();
	for(a[0] = ~0U >> 2, i = 1; i <= n; i++) a[i] = inp();
	for(b[0] = ~0U >> 2, i = 1; i <= n; i++) b[i] = inp();	
	build(1, 0, n);
	while(K--) {
		info cur = A[1] + B[1];
		int l = cur.l, r = cur.r;
		ans += a[l] + b[r];
		if(l < r) seg_modify(1, 0, n, l, r - 1, 1);
		if(l > r) seg_modify(1, 0, n, r, l - 1, -1);
		a[l] = b[r] = ~0U >> 2;
		sig_modify(1, 0, n, l);
		sig_modify(1, 0, n, r);
	}
	cout << ans;
	return 0;
}

