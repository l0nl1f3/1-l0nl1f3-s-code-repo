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
const int MaxN = 201234;
int n, m, a[MaxN], b[MaxN], c[MaxN], d[MaxN];
int main() {
	int i;
	n = inp(); m = inp();
	for(i = 1; i <= m; i++){
		a[i] = inp(), b[i] = inp();
		if(a[i] == 1) c[b[i]] = 1;
		if(b[i] == n) d[a[i]] = 1;
	}
	for(i = 2; i < n; i++)
		if(c[i] && d[i])
			return puts("POSSIBLE"), 0;
	puts("IMPOSSIBLE");
	return 0;
}




