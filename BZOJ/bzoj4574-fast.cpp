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

const int MaxN = 666, P = 1000000007;

int add(int a, int b){
	return (a + b) % P;
}
int sub(int a, int b){
	return (a - b + P) % P;
}
int mul(int a, int b){
	return (LL) a * b % P; 
}

int exp(int a, int n){
	int res = 1;
	for(; n; n >>= 1, a = mul(a, a))
		if(n & 1) 
			res = mul(res, a);
	return res;
}

int n, m, a[MaxN], p[MaxN], c[MaxN], co[MaxN][MaxN];
int f[2][MaxN][MaxN];
int p1[2][MaxN][MaxN], p2[2][MaxN][MaxN];

int main() {
	int i, j, k;
	
	n = inp(); m = inp(); a[0] = a[n + 1] = ~0U >> 1;
	for(i = 1; i <= n; i++) a[i] = inp(), p[i] = i;
	for(i = 0; i < MaxN; i++) c[i] = (LL)(i * (i + 1) >> 1) % P;
	for(i = 1; i <= n; i++)
		for(j = i; j <= n; j++)
			co[i][j] = (0ll + c[i - 1] + c[n - j] + c[j - i + 1]) % P;
	
	for(i = 1; i <= n; i++){
		int q = 0;
		for(j = i; j <= n; j++){
			cmax(q, a[j]);
			if(i > 1 || j < n){
				if(a[i - 1] > q && a[j + 1] > q)
					f[0][i][j] = (q - min(a[i - 1], a[j + 1]) + P) % P;
			}
			else
				f[0][i][j] = q;
		}
	}
	
	for(int o = 1; o <= m; o++){
		//int u = ~o & 1;
		//int v = o & 1;
		int (*p2u)[MaxN] = p2[~ o & 1];
		int (*p1u)[MaxN] = p1[~ o & 1];
		int (*fu)[MaxN] = f[~ o & 1];
		int (*fv)[MaxN] = f[o & 1];
		for(i = 1; i <= n; i++){
			for(j = n; j >= i; j--){
				p2u[i][j] = (p2u[i][j + 1] + (LL) fu[i][j] * (n - j)) % P;
			}
		}
		
		for(i = 1; i <= n; i++)
			for(j = i; j <= n; j++){
				p1u[i][j] =(p1u[i - 1][j] + (LL) fu[i][j] *(i - 1)) % P;
				fv[i][j] = ((LL)fu[i][j] * co[i][j] + p1u[i - 1][j] + p2u[i][j + 1]) % P;	
			}
	}
	
	int iv = exp(exp(c[n], m), P - 2);
	int (*fm)[MaxN] = f[m & 1];
	for(i = 1; i <= n; i++){
		int ans = 0;
		for(j = 1; j <= i; j++)
			for(k = i; k <= n; k++)
				ans = add(ans, fm[j][k]);
		printf("%d%c", ans, " \n"[i == n]);
	}
	return 0;
}



