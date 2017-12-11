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

const int MaxN = 1001234;
char s[MaxN]; int t[12] = {0, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1};
int solve() {
	int i, x = 0, y = 0;
	for(i = 1; i <= 10; i++) {
		if(i & 1)
			x += s[i] - '0';
		else
			y += s[i] - '0';
		if(x > y + t[i + 1])
			return printf("TEAM-A %d\n", i);
		if(y > x + (10 - i) - t[i + 1])
			return printf("TEAM-B %d\n", i);
	}
	for(i = 1; i <= 5; i++) {
		int a = s[10 + i * 2 - 1] - '0', b = s[10 + i * 2] - '0';
		x += a; y += b;
		if(x > y) return printf("TEAM-A %d\n", i * 2 + 10);
		if(x < y)  return printf("TEAM-B %d\n", i * 2 + 10);
	}
	puts("TIE");
}
int main() {
	while(scanf("%s", s + 1) != EOF)
		solve();
	return 0;
}

