#include <bits/stdc++.h>

#define fir first
#define sec second
using namespace std;
typedef long long LL;
typedef unsigned long long u64;

template <typename T> inline bool cmin(T & a, const T & b) { return a > b ? a = b, 1 : 0;}
template <typename T> inline bool cmax(T & a, const T & b) { return a < b ? a = b, 1 : 0;}
int inp() {
	int x = 0, f = 1;char ch;
	for(ch = getchar(); !isdigit(ch); ch = getchar())
		if(ch == '-') f = -1;
	for(; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	return x * f;
}

const int MaxN = 1001234, P = 998244353;
int n, m, fac[MaxN], rfac[MaxN];

int exp(int a, int n) {
	int res = 1;
	for(; n; n >>= 1) {
		if(n & 1)
			res = (LL) res * a % P;
		a = (LL) a * a % P; 
	}
	return res;
}

int C(int n, int m) {
	return n < 0 || m < 0 || n < m ? 0 : (LL) fac[n] * rfac[m] % P * rfac[n - m] % P;
}

int main() {
	int i;
	
	fac[0] = 1;
	for(i = 1; i < MaxN; i++) fac[i] = (LL) fac[i - 1] * i % P;
	rfac[MaxN - 1] = exp(fac[MaxN - 1], P - 2);
	for(i = MaxN - 1; i; i--) rfac[i - 1] = (LL) rfac[i] * i % P;
	
	n = inp(); m = inp(); 
	if(n < m) swap(n, m);
	int ans = 0;
	
	for(i = 1; i <= m; i++) {
		int wayA = C(i + i, i);
		int wayB = C(n - i + m - i, n - i);
		ans += (LL) wayA * wayB % P;
		ans %= P; 
	}
	
	ans = (LL) ans * exp(C(n + m, n), P - 2) % P;
	ans = (LL) ans * (P + 1) / 2 % P;
	
	cout << (ans + n) % P;
	return 0;
}



