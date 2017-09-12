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
 
const int MaxN = 101234, MaxK = 55;
int n, K, h[MaxN], s[MaxN], top;
LL  f[MaxN][MaxK];
 
LL get_val(int i, int j, int x) {
	LL fpre = f[s[x]][j - 1];
	LL fnew = (LL) (i - s[x]) * h[s[x + 1]];
	return fpre + fnew;
}
 
 
LL tri_search(int i, int j) {
	int l = 0, r = top - 1;
	while(r - l > 4) {
		int mL = l + (r - l)/3;
		int mR = r - (r - l)/3;
		if(get_val(i, j, mL) < get_val(i, j, mR))
			l = mL;
		else 
			r = mR;
	}
	
	LL ans = 0;
	for(; l <= r; l++) 
		cmax(ans, get_val(i, j, l));
	return ans;
}
 
LL dp() {
	int i, j, k; top = 0;
	LL ans = 0;
	memset(f, 0, sizeof(f));
	for(i = 1; i <= n; i++) {
		while(top && h[s[top]] >= h[i]) --top; s[++top] = i;
		for(j = 1; j <= K; j++) f[i][j] = tri_search(i, j);
	}
	for(i = 1; i <= n; i++)  cmax(ans, f[i][K]);
	return ans;
}
 
void solve() {
	int i; LL ans = 0;
	n = inp(); K = inp() + 1;
	for(i = 1; i <= n; i++) h[i] = inp();
	cmax(ans, dp());
	for(i = 1; i <= n / 2; i++) swap(h[i], h[n - i + 1]);
	cmax(ans, dp());
	
	cout << ans << endl;
}
 
int main() {
	int T = inp();
	while(T--) {
		solve();
	}
	return 0;
} 
