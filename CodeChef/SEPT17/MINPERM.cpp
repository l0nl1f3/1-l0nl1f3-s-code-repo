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
int n, p[MaxN];

int main() {
	int i, T = inp();
	while(T--) {
		n = inp();
		if(n & 1) {
			for(i = 1; i <= n - 3; i++) printf("%d ", ((i + 1) ^ 1) - 1);
			printf("%d %d %d\n", n - 1, n, n - 2);
		} else {
			for(i = 1; i <= n; i++) printf("%d ", ((i + 1) ^ 1) - 1);
			puts("");
		}
	}
	return 0;
}



