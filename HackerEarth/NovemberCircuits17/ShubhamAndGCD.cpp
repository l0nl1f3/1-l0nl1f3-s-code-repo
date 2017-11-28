#include <bits/stdc++.h>

#define fir first
#define sec second
using namespace std;
typedef __int128 LL;
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

const int MaxN = 101234;

int n, a[MaxN]; LL f[MaxN], g[MaxN];

int main() {
	int i, j;
	n = read();
	for(i = 1; i <= n; i++) {
		a[i] = read();
		f[a[i]] += i; g[a[i]]++;
	}
	
	int m = *max_element(a + 1, a + n + 1);
	
	LL p = 0, q = 0;
	
	LL ans = 0;
	LL ub = 1000000000000000000;
	long long _ans = ans > ub ? -1 : ans;
	cout << _ans;
	return 0;
}

