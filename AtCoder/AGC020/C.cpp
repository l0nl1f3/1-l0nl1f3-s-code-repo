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

const int MaxN = 2333;
int n, a[MaxN];

bitset<MaxN * MaxN> f[2];
int main() {
	int i;
	n = read();
	for(i = 1; i <= n; i++) a[i] = read();
	if(n == 1) return printf("%d\n", a[n]), 0;
	f[0].set(0);
	
	for(i = 1; i <= n; i++) {
		f[i & 1] = f[~i & 1];
		f[i & 1] |= f[~i & 1] << a[i];
	}
	int s = 0;
	for(i = 1; i <= n; i++) s += a[i];
	
	for(i = s + 1 >> 1; ; i++)
		if(f[n & 1][i])
			return printf("%d\n", i), 0;
	return 0;
}



