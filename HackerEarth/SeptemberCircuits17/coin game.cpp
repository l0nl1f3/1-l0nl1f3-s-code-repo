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

const int MaxN = 1234;

int n, a[MaxN];

int main() {
	int i; T = inp() 
	while(T--) {
	n = inp();
	for(i = 1; i <= n; i++) a[i] = inp();
	
	int cnt = 0;
	for(i = 1; i <= n; i++) while(~a[i] & 1) cnt++, a[i] >>= 1;
	puts((~ cnt & 1) ? "Alan" : "Charlie");
	}
	return 0;
}



