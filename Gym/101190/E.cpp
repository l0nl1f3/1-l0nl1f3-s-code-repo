#include <bits/stdc++.h>

#define fir first
#define sec second
#define MP make_pair

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

int n, q, t[MaxN],  k[MaxN];
pair<int, int> a[MaxN], b[MaxN]; LL S[MaxN], T[MaxN], ans[MaxN]	;
int main() {
	int i, j;
	freopen("expect.in", "r", stdin);
	freopen("expect.out", "w", stdout);
	
	n = read(); q = read();
	for(i = 1; i <= n; i++) {
		char s[3]; scanf("%s", s);
		t[i] = read(), k[i] = (s[0] == '+' ? -1 : 1) * read();
	}
	for(i = 1; i <= n; i++) k[i] += k[i - 1];
	for(i = 1; i < n; i++) a[i] = MP(k[i], t[i + 1] - t[i]);
	sort(a + 1, a + n);
	for(i = 1; i <= q; i++) b[i] = MP(read(), i);
	sort(b + 1, b + q + 1);
	for(i = n - 1; i; i--) 
		S[i] = S[i + 1] + a[i].sec, 
		T[i] = T[i + 1] + (LL) a[i].fir * a[i].sec;
	for(i = j = 1; i <= q; i++) {
		int p = b[i].fir;
		if(p < k[n]) ans[b[i].sec] = -1;
		else {
			for(; j < n && p >= a[j].fir; ++j);
			ans[b[i].sec] = T[j] - S[j] * p;
		} 
	}
	for(i = 1; i <= q; i++) if(~ans[i]) printf("%lld\n", ans[i]); else puts("INFINITY");
	return 0;
}
