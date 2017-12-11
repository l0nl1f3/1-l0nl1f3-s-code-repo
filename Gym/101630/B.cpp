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

bool chk(int a, int b, int c, int w, int h) {
	return (2 * a + 2 * b <= h && b * 2 + c <= w) || (a + c <= h && 3 * b + a + c <= w);
}

int main() {
	int a, b, c, w, h;
	cin >> a >> b >> c >> w >> h; 
	bool ans = chk(a, b, c, w, h) ||
	chk(a, c, b, w, h) ||
	chk(c, b, a, w, h) ||
	chk(c, a, b, w, h) ||
	chk(b, a, c, w, h) ||
	chk(b, c, a, w, h) ||
	chk(a, b, c, h, w) ||
	chk(a, c, b, h, w) ||
	chk(c, b, a, h, w) ||
	chk(c, a, b, h, w) ||
	chk(b, a, c, h, w) ||
	chk(b, c, a, h, w);
	if(ans) puts("Yes"); else puts("No");
	return 0;
}



