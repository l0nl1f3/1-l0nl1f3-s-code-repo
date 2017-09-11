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

const int MaxN = 101234;
LL pre[MaxN], suf[MaxN];
int n, a[MaxN];
int main() {
	int i, T = inp();
	while(T--) {
		n = inp();
		for(i = 1; i <= n; i++) a[i] = inp();
		for(i = 1; i <= n; i++) {
			pre[i] = pre[i - 1] + a[i];
		}	
		suf[n + 1] = 0;
		for(i = n; i; i--) suf[i] = suf[i + 1] + a[i];
		
		int ans = 0; LL p = LONG_LONG_MAX;
		for(i = 1; i <= n; i++)
			if(cmin(p, pre[i] + suf[i]))
				ans = i;

		cout << ans << endl;
	}
	return 0;
}



