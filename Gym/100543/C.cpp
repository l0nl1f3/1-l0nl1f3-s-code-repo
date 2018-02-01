#include <bits/stdc++.h>

#define fi first
#define se second
#define mp make_pair
#define pb push_back

using namespace std;
typedef long long LL;
typedef unsigned long long u64;

template <typename T> inline bool cmin(T & a, const T & b) { return a > b ? a = b, 1 : 0;}
template <typename T> inline bool cmax(T & a, const T & b) { return a < b ? a = b, 1 : 0;}
int read() {
	int x = 0, f = 1; char ch;
	for (ch = getchar(); !isdigit(ch); ch = getchar())
		if (ch == '-') f = -1;
	for (; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	return x * f;
}

inline pair<int, int> chk(int u, int v) {
	// a + b = u
	// b - a + 1 = v
	// 2b = u + v - 1
	int s = u + v - 1;
	if(s & 1) return mp(-1, -1);
	LL b = u + v - 1 >> 1, a = u - b;
	if(a >= b || a < 0 || b < 0) return mp(-1, -1);
	return mp(a, b);	
} 

int main() {
	for (int T = read(), n; T--; ) {
		n = read() << 1;
		
		int L = INT_MAX, a = 0, b = 0; 
		for (int u = 2; u * u <= n; u++) {
			if(n % u == 0) {
				int v = n / u - u + 1;
				if(v >= 2 && (~v & 1)) {
					v >>= 1; a = 1;
					printf("%d = ", n >> 1);
					for (int i = 1; i <= u; i++)
						printf("%d %c ", v + i - 1, "+ "[i == u]);
					puts(""); break;
				}
			}
		}
		if(!a) puts("IMPOSSIBLE");
	}
	return 0;
}




