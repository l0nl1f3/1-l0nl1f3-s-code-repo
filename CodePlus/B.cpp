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

const int MaxN = 101234;
pair<int, int> a[MaxN]; int n, m;
int b[MaxN], l[MaxN], r[MaxN], bn;
int main() {
	int i;
	n = read();  m = read();
	LL ans = 0;
	for(i = 1; i <= m; i++) a[i].fir = read(), a[i].sec = read();
	sort(a + 1, a + m + 1);
	for(i = 1; i <= m; i++) {
		if(a[i].fir == a[i - 1].fir + 1) {
		}
		else {
		}
	}
	// B-A (-BK)
	return 0;
}

