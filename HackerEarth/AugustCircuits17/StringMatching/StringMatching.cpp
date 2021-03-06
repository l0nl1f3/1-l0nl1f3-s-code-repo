#include <bits/stdc++.h>

#define fir first
#define sec second
using namespace std;
typedef long long LL;

template <typename T> inline bool cmin(T & a, const T & b) { return a > b ? a = b, 1 : 0;}
template <typename T> inline bool cmax(T & a, const T & b) { return a < b ? a = b, 1 : 0;}
int inp() {
	int x = 0, f = 1;char ch;
	for(ch = getchar(); !isdigit(ch); ch = getchar())
		if(ch == '-') f = -1;
	for(; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	return x * f;
}

const int MaxN = 101234, MaxD = 10;

char s[MaxN]; int n, m, a[MaxN], b[MaxD], c[MaxD];

int main() {
	int i;
	scanf("%s", s + 1); n = strlen(s + 1);
	for(i = 1; i <= n; i++) a[i] = s[i] - '0';
	
	m = inp();
	for(i = 1; i <= m; i++) b[inp()] = 1;
	
	int l, r; LL ans = 0;
	int cnt = 0;
	for(r = 1, l = 1; r <= n; r++) {
		int p = a[r];
		if(b[p]) {
			if(!c[p]) ++cnt; ++c[p];
		}
		
		p = a[l];
		while(cnt == m) {
			if(!--c[p]) --cnt;
			p = a[++l];
		}
		
		ans += l - 1;
	}
	
	cout << ans;
	return 0;
}



