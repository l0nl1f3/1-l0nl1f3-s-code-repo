#include <bits/stdc++.h>
 
#define fir first
#define sec second
using namespace std;
typedef long long LL;
typedef unsigned long long u64;
 
template <typename T> inline bool cmin(T & a, const T & b) { return a > b ? a = b, 1 : 0;}
template <typename T> inline bool cmax(T & a, const T & b) { return a < b ? a = b, 1 : 0;}
int gint() {
	int x = 0, f = 1;char ch;
	for(ch = getchar(); !isdigit(ch); ch = getchar())
		if(ch == '-') f = -1;
	for(; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	return x * f;
}
 
const int MaxN = 1001234;
 
int n; char s[MaxN], t[MaxN];
int H[MaxN << 1], *h = H;
 
int main() {
	int i;
	scanf("%d %s %s", &n, s + 1, t + 1);
	if(!strcmp(s + 1, t + 1)) return puts("0"), 0;
	
	int l, r, d, ans;
	l = n + 1; r = n; d = ans = 0;
	for(i = n; i; i--) {
		if(t[i] == t[i - 1]) continue;
		int x, p;
		for(x = min(l - 1, i); x && s[x] != t[i]; x--);
		if(!x) return puts("-1"), 0;
		for(p = i; t[p + 1] == t[i]; ++p);
		for(; l > x; h[--l] = -d);
		for(; r >= p; cmax(ans, h[r--] + d));
		++h; ++d;
	}	
	for(; l > 1; h[--l] = -d);
	for(; r >= 1; cmax(ans, h[r--] + d));
	cout << ans;
	return 0;
}
