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
const int P = 10007; 
struct mat{
	int a[2][2];
	int * operator[] (int x){ return a[x]; } 
}A, I, O;

mat mul(mat a, mat b){
	mat c;
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++){
			c[i][j] = 0;
			for(int k = 0; k < 2; k++)
				c[i][j] = (c[i][j] + (LL) a[i][k] * b[k][j]) % P;
		}
	return c;	
}
mat add(mat a, mat b){
	mat c;
	c[0][0] = (a[0][0] + b[0][0]) % P;
	c[0][1] = (a[0][1] + b[0][1]) % P;
	c[1][0] = (a[1][0] + b[1][0]) % P;
	c[1][1] = (a[1][1] + b[1][1]) % P;
	return c;
}
mat sub(mat a, mat b){
	mat c;
	c[0][0] = (a[0][0] - b[0][0] + P) % P;
	c[0][1] = (a[0][1] - b[0][1] + P) % P;
	c[1][0] = (a[1][0] - b[1][0] + P) % P;
	c[1][1] = (a[1][1] - b[1][1] + P) % P;
	return c;
}
mat exp(mat a, LL n){
	mat res = I;
	for(; n; n >>= 1, a = mul(a, a))
		if(n & 1) res = mul(res, a);
	return res;
}

const int MaxN = 401234;

mat seg[MaxN], tag[MaxN];
int a[MaxN];
void build(int p, int l, int r){
	tag[p] = I; seg[p][0][1] = 1;
	if(l == r) {
		seg[p] = mul(seg[p], exp(A, a[l]));
		return ;
	}
	build(p << 1, l, l + r >> 1);
	build(p << 1 | 1, (l + r >> 1) + 1, r);
	seg[p] = add(seg[p << 1], seg[p << 1 | 1]);
} 
void push_down(int p, int l, int r){
	if(l == r) return;
	tag[p << 1] = mul(tag[p << 1], tag[p]);
	tag[p << 1 | 1] = mul(tag[p << 1 | 1], tag[p]);
	seg[p << 1] = mul(seg[p << 1], tag[p]);
	seg[p << 1 | 1] = mul(seg[p << 1 | 1], tag[p]);
	tag[p] = I;
}
int qry(int p, int l, int r, int a, int b){
	if(b < l || a > r) return 0;
	if(a <= l && r <= b) return seg[p][0][0];
	push_down(p, l, r);
	return qry(p << 1, l, l + r >> 1, a, b) + qry(p << 1 | 1, (l + r >> 1) + 1, r, a, b);
}
void mdf(int p, int l, int r, int a, int b, mat d){
	if(b < l || a > r) return;
	if(a <= l && r <= b) {
		tag[p] = mul(tag[p], d);
		seg[p] = mul(seg[p], d);
		return;
	}
	push_down(p, l, r);
	mdf(p << 1, l, l + r >> 1, a, b, d);
	mdf(p << 1 | 1, (l + r >> 1) + 1, r, a, b, d);
	seg[p] = add(seg[p << 1], seg[p << 1 | 1]);
}

int n, q;

int main() {
	int i;
	
	A[0][0] = 0; A[0][1] = 1; 
	A[1][0] = 1; A[1][1] = 1;
		
	I[0][0] = 1; I[1][1] = 1;
	
	n = inp(); q = inp();
	
	for(i = 1; i <= n; i++) a[i] = 1;
	build(1, 1, n);
	
	while(q--){
		int l = inp(), r = inp(), op = inp();
		if(op)
			mdf(1, 1, n, l, r, exp(A, op));
		else printf("%d\n", qry(1, 1, n, l, r));
	}
	return 0;
}



