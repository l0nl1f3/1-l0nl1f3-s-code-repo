#include <bits/stdc++.h>

#define fir first
#define sec second
#define MP make_pair

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

LL n, p, r;

LL exp(LL a, LL n) {
	LL res = 1;
	for(; n; n >>= 1) {
		if(n & 1)
			res = res * a % p;
		a = a * a % p;
	}
	return res;
}
int main() {
	LL i;
	cin >> n >> p >> r;
	if(!r) {
		if(n < p || n <= 2) return puts("-1 -1"), 0;
		if(p == 2) return puts("3 2"), 0;
		return puts("2 1"), 0;
	}
	if(n >= 2 * p) return puts("-1 -1"), 0;
	if(n >= p) {
		LL s = 1;
		for(i = 1; i <= n; i++)
			if(i != p) (s *= i) %= p;
		for(i = 1; i < p; i++)
			if(s * i % p == r)
				return printf("%lld %lld\n", p, i), 0; 
		return printf("-1 -1"), 0; 
	}
	LL s = 1;
	for(i = 1; i <= n; i++) 
		s = s * i % p;
	s = exp(s, p - 2);
	for(i = 2; i <= n; i++) {
		LL nd = i * r % p * s % p;
		if(nd < i) return printf("%lld %lld\n", i, nd), 0;
	}puts("-1 -1");
	return 0;
}

close
