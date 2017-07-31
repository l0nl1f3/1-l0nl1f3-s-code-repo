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
const int MaxN = 55;
int n; LL a[MaxN], ans;
int main() {
	int i;
	n = inp();
	for(i = 1; i <= n; i++) scanf("%lld", a+i);
	for(;;) {
		LL s = 0, b = 0;
		for(i = 1; i <= n; i++) b = a[i]/n, a[i] %= n, a[i] -= b, s += b;
		if(!s) break;
		for(i = 1; i <= n; i++) a[i] += s;
		ans += s;
	}
	cout << ans;
	return 0;
}



