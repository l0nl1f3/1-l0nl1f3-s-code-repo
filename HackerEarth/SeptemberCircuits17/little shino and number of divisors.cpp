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

const int MaxN = 1001234, P = 1000000007;

int n, a[MaxN];
 
int exp(int a, int n) {
	int res = 1;
	for(; n; n >>= 1) {
		if(n & 1) 
			res = (LL) res * a % P;
		a = (LL) a * a % P;
	}
	return res;
}

//p_i \sum_{k=0}^{a[i]} 
int main() {
	int i;
	
	n = inp();
	for(i = 1; i <= n; i++) a[i] = inp();
	int all = 1;
	for(i = 1; i <= n; i++) all = (LL) all * (a[i] + 1) % P;
	int ans = 1;
	for(i = 1; i <= n; i++) {
		int t = (LL) all * exp(a[i] + 1, P - 2) % P;
		ans = (LL) ((LL)a[i] * (a[i] + 1) / 2 % P * t % P + 1) * ans % P;
	}
	cout << ans;
	return 0;
}



