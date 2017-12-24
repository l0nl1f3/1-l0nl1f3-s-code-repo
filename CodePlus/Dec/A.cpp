#include <bits/stdc++.h>

#define fir first
#define sec second
#define MP make_pair
#define PB push_back

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

int P, m; LL f1, l, r, K;
struct mat {
	int a[2][2];
	mat() {a[0][0] = a[0][1] = a[1][0] = a[1][1] = 0; }
	int * operator [] (int x) {return a[x]; }
}I, t;

mat mul(mat a, mat b) {
	mat c;
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++)
			for(int k = 0; k < 2; k++) {
				c[i][j] = (c[i][j] + (LL) a[i][k] * b[k][j]) % P;
			}
	return c;
} 

mat exp(mat a, LL n) {
	mat res = I;
	for(; n; n >>= 1) {
		if(n & 1) 
			res = mul(res, a);
		a = mul(a, a);
	}	
	return res;
}
int exp(int a, LL n) {
	int res = 1;
	for(; n; n >>= 1) {
		if(n & 1) 
			res = (LL) res * a % P;
		a = (LL) a * a % P;
	}	
	return res;
}

LL F(LL r) {
	if(r < m) return 0;
	return (r - m) / P + 1; 
} 

void exgcd(int a, int b, LL & x, LL & y) {
	if(!b) x = 1, y = 0;
	else {
		exgcd(b, a % b, x, y);
		LL t = x; x = y; y = t - (a / b) * y;
	}
}

int main() {
	t[0][0] = 0; t[0][1] = 1;
	t[1][0] = 1; t[1][1] = 1;
	I[0][0] = 1; I[1][1] = 1;
	int T = read();
	while(T--) {
		cin >> f1 >> l >> r >> K >> P >> m;
		mat c = exp(t, K - 1); f1 %= P;
		LL ans = 0;
		m = (m - (LL) f1 * c[0][0] % P + P) % P;
		int g = __gcd(c[1][0], P);
		LL a, b;
		exgcd(c[1][0], P, a, b);
		if(r <= 1e5) {
			for(LL f2 = l; f2 <= r; f2++)
				ans += ((LL) f2 * c[1][0] % P == m);
		}else {
			if(m % g == 0) {
				m /= g;
				a = (LL) a * m % P;
				b = ((l - a) * g + P - 1) / P; l = a + b * (P / g);
			 	ans = (r - l) / (P / g) + 1;
			} 
		}
		cout << ans << endl;
	}
	return 0;
}

