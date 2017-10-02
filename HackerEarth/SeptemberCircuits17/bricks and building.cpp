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

int n, q, a[MaxN], b[MaxN], c[MaxN];
int main() {
	int i, j;
	n = inp();
	for(i = 1; i <= n; i++) b[a[i] = inp()]++;
	for(i = 1; i < MaxN; i++)
		for(j = i; j < MaxN; j += i) c[i] += b[j];
	q = inp();
	while(q--) {
		int K = inp();
		printf("%d\n", c[K]);
	}
	return 0;
}



