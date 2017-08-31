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

int q, h, s, d, n;
int main() {
	int i;
	cin >> q >> h >> s >> d >> n;
	LL ans = 0;
	int c = min(q * 8, h * 4);
	c = min(c, min(s * 2, d));
	ans += (LL) c * (n/2);
	if(n & 1) {
		ans += min(min(q * 4, h * 2), s);
	}
	cout << ans;
	return 0;
}



