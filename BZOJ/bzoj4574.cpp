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

const int MaxN = 666;
const int P = 1000000007;
#define add(a, b) (a + b) % P
#define sub(a, b) (a - b + P) % P
#define mul(a, b) ((LL) a * b % P)

int n, m, a[MaxN], c[MaxN], p[MaxN], v[MaxN];

bool cmp(int x, int y){
	return a[x] < a[y];
}
int exp(int a, int n){
	int res = 1;
	for(; n; n >>= 1, a = mul(a, a))
		if(n & 1) 
			res = mul(res, a);
	return res;
}
int f[MaxN][MaxN], ans[MaxN], sum[MaxN]; LL g[MaxN][MaxN];
int main() {
	register int i, o, j, k;
 	for(i = 0; i < MaxN; i++) c[i] = ((LL) i * (i + 1) >> 1 )% P;
	
	n = inp(); m = inp();
	for(i = 0; i < n; i++) a[i] = inp(), p[i] = i;
	sort(p, p + n, cmp);
	for(o = 0; o < n; o++){
		int x = p[o], l, r; v[x] = 1;
		for(l = x; l > 0 && v[l - 1]; --l);
		for(r = x; r < n && v[r]; ++r);
		for(i = l; i <= r; i++)
			for(j = i; j <= r; j++)
				f[i][j] = 0;
		f[l][r] = 1;
		for(k = 0; k < m; k++){ 	
			for(i = l; i <= r; i++)
				for(j = i; j <= r; j++)
					g[i][j] = 0;
			for(i = l; i <= r; i++){
				for(j = i; j <= r; j++)
					if(f[i][j]){
						g[i][j] += (LL)f[i][j] * (c[i] + c[j - i] + c[n - j]);
						g[l][l] += (LL)f[i][j] * i * (n - j);
					}
			}
			for(i = l; i <= r; i++){
				register LL co = 0;
				for(j = r; j >= i; j--){ 
					g[i][j] += co;
					if(f[i][j])
						co += (LL) f[i][j] * (n - j);
				}
			}
			for(i = l; i <= r; i++){
				register LL co = 0;
				for(j = l; j <= i; j++){
					g[j][i] += co;
					if(f[j][i])
						co += (LL) f[j][i] * j;
				}
			}
			for(i = l; i <= r; i++)
				for(j = i; j <= r; j++)
					f[i][j] = g[i][j] % P;
		}
		for(i = l; i < r; i++) 
			ans[i] = (ans[i] - (LL)sum[i] * a[x]) % P, sum[i] = 0;
			
		for(i = l; i <= r; i++)
			for(j = i; j <= r; j++)
				if(f[i][j])
					for(k = i; k < j; k++)
						sum[k] = add(sum[k], f[i][j]);
		
		for(i = l; i < r; i++) 
			ans[i] = (ans[i] + (LL)sum[i] * a[x]) % P;
	}
	int iv = 1
	for(i = 0; i < n; i++) printf("%d%c", ans[i], " \n"[i == n - 1]); 
	return 0;
}



