#include <bits/stdc++.h>
 
#define fir first
#define sec second
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
 
const LL P = 10000019;
int T;
LL n, m, r, fac[P], rfac[P];
 
LL exp(LL a, LL n) {
	LL res = 1;
	for(; n; n >>= 1) {
		if(n & 1)
			res = res * a % P;
		a = a * a % P;
	}
	return res;
}
 
LL C(LL n, LL m) {
	if(n < m || n < 0 || m < 0) 
		return 0;
	if(n < P && m < P)
		return fac[n] * rfac[m] % P * rfac[n - m] % P;
	return C(n / P, m / P) * C(n % P, m % P) % P;
}
 
int main() {
	int i;
	cin >> T;
	fac[0] = 1;
	for(i = 1; i < P; i++) fac[i] = fac[i - 1] * i % P;
	rfac[P - 1] = exp(fac[P - 1], P - 2);
	for(i = P - 1; i; i--) rfac[i - 1] = rfac[i] * i % P;
	while(T--) {
		cin >> n >> m >> r;
		cout << (n % P * (m % P) % P * C(n + m - 2, n + m - r) % P) << endl;
	}
	return 0;
}
