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

const int MaxN = 201234, MaxM = 401234;
const int P = 1000000007;

struct edge{
	int to, nxt;
}e[MaxM]; int cnt, lst[MaxN];

void ins(int a, int b){
	e[++cnt] = (edge){b, lst[a]}; lst[a] = cnt;
}

void lnk(int a, int b){
	ins(a, b); 
	ins(b, a);
}

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
int exp(int a, LL n){
	int res = 1;
	for(; n; n >>= 1, a = (LL)a * a % P)
		if(n & 1) res = (LL) res * a % P;
	return res;
}
mat inv(mat x){
	int a = x[0][0], b = x[0][1], c = x[1][0], d = x[1][1];
	int iv = (LL) a * d % P - (LL) b * c % P;
	iv = exp((iv + P) % P, P - 2);
	mat c;
	c[0][0] = (LL) d * iv % P;
	c[0][1] = (LL) (P - b) * iv % P;
	c[1][0] = (LL) (P - c) * iv % P;
	c[1][1] = (LL) a * iv % P;
	return c;
}

int n, fib[MaxN], c[MaxN]; LL dep[MaxN];
mat a[MaxN], f[MaxN], g[MaxN], ans; 

void dfs0(int x, int fa){
	for(int i = lst[x]; i; i = e[i].nxt)
		if(e[i].to != fa){
			dep[e[i].to] = dep[x] + c[e[i].to];
			dfs0(e[i].to, x);
		}
}

void dfs1(int x, int fa){
	g[x] = a[x];
	mat G = C = O;
	for(int i = lst[x]; i; i = e[i].nxt) 
		if(e[i].to != fa){
			dfs1(e[i].to, x);			
			g[x] = add(g[x], g[e[i].to]);
			G = add(G, g[e[i].to]);
		}
	for(int i = lst[x]; i; i = e[i].nxt)
		if(e[i].to != fa) C = add(C, mul(g[e[i].to], sub(G, g[e[i].to])));		
	C = add(C, mul(g[x], a[x]));
	C = add(C, mul(g[x], a[x]));
	mat coff = inv(a[x]);
	if(fa) coff = mul(coff, inv(a[fa]));
	ans = add(ans , mul(C, coff));
}	

int main() {
	int i, u, v;
	n = inp();
	for(i = 1; i < n; i++) 	u = inp(), v = inp(), lnk(u, v);
	for(i = 1; i <= n; i++) c[i] = inp();
	
	A[0][0] = 1; A[0][1] = 1; 
	A[1][0] = 1; A[1][1] = 0;
	
	I[0][0] = 1; I[0][1] = 0; 
	I[1][0] = 0; I[1][1] = 1;
	
	dep[1] = c[1];
	dfs0(1, 0);
	
	for(i = 1; i <= n; i++)
		a[i] = exp(A, dep[i]);
	
	dfs1(1, 0);
	for(i = 1; i <= n; i++) ans = sub(ans, exp(A, c[i]));
	printf("%d", mul(ans, A)[0][1]);
	return 0;
}

