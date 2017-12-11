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

int T, x, y, z, a, b, c;

int main() {
	int i;
	T = read();
	while(T--) {
		x = read(); y = read(); z = read();
		a = read(); b = read(); c = read();
		cmin(b, a + a);
		cmin(c, b + a);
		cout << a << " " << b << " " << c << endl;
		int u = min(x, min(y, z));
		LL ans = 0;
		ans += u * c; x -= u; y -= u; z -= u;
		cout << ans << endl;
		if(!x) u = min(y, z);
		if(!y) u = min(x, z);
		if(!z) u = min(x, y);
		ans += u * b;
		x -= u; y -= u; z -= u;
		if(x > 0) u = x;
		if(y > 0) u = y;
		if(z > 0) u = z;
		ans += u * a; 
		printf("%lld\n", ans);
	}
	return 0;
}

