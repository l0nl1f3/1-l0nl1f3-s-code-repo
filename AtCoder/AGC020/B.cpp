#include <bits/stdc++.h>

#define fir first
#define sec second
#define MP make_pair
#define PB push_back

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

int n, a[MaxN];

int main() {
	int i;
	n = read();
	for(i = 1; i <= n; i++) a[i] = read();
	LL l = 2, r = 3;
	if(a[n] ^ 2) return puts("-1"), 0;
	
	for(i = n; i > 1; i--) {
		LL z = a[i - 1];
		l = (l + z - 1) / z * z;
		r = r / z * z + (z - 1);
	}
	
	if(l > r) puts("-1");
	else cout << l << " " << r << endl;
	return 0;
}



