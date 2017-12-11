#include <bits/stdc++.h>

#define fir first
#define sec second
using namespace std;
typedef long long LL;

template <typename T> inline bool cmin(T & a, const T & b) { return a > b ? a = b, 1 : 0;}
template <typename T> inline bool cmax(T & a, const T & b) { return a < b ? a = b, 1 : 0;}
int read() {
	int x = 0, f = 1;char ch;
	for(ch = getchar(); !isdigit(ch); ch = getchar())
		if(ch == '-') f = -1;
	for(; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	return x * f;
}

const int MaxN = 2001234;
int T, n; LL f[MaxN], g[MaxN];

int abs(int x) {
	return x > 0 ? x : - x;
}

int calc(int x) {
	int p = 0, s[2]; s[0] = s[1] = 0;
	while(x) {
		s[(x % 10) & 1] += x % 10; x /= 10;
	}
	return abs(s[0] - s[1]);
}

int main() {
	for(int i = 1; i < MaxN; i++) g[i] = g[i - 1] + calc(i);
	for(int i = 1; i <= 1000000; i++) {
		f[i] = f[i - 1] + (g[i + i] - g[i]) + (g[i + i] - g[i]) - calc(i + i);
	} 
	cin >> T;
	while(T--) {
		cin >> n;
		cout << f[n] << endl;
	}
	return 0;
}

