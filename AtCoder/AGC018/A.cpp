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
const int MaxN = 101234;
int n, K, a[MaxN];

int main() {
	int i, g;
	n = inp(); K = inp();
	for(i = 1; i <= n; i++) a[i] = inp();
	for(g = a[i = 1]; i <= n; i++) g = __gcd(g, a[i]);
	if(K % g == 0 && *max_element(a + 1, a + n + 1) >= K)
		puts("POSSIBLE");
	else 
		puts("IMPOSSIBLE");
	return 0;
}



