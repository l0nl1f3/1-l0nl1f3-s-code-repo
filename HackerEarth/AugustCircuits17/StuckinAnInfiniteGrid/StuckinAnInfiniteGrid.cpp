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

const int P = 1000000007;
const int MaxN = 401234;

int xs, ys, xt, yt, K;
int fac[MaxN], rfac[MaxN];
 
int exp(int a, int n) {
	int res = 1;
	for(; n; n >>= 1) {
		if(n & 1) 
			res = (LL) res * a % P;
		a = (LL) a * a % P; 
	}
	return res;
}

int C(int n, int m) {
	if(n < m || n < 0 || m < 0) return 0;
	return (LL) fac[n] * rfac[m] % P * rfac[n - m] % P;
} 

int f[MaxN << 1];
void solve() {
	cin >> xs >> ys >> xt >> yt >> K;
	xt -= xs; yt -= ys; 
	if(xt < 0) xt = -xt; 
	if(yt < 0) yt = -yt;
	
	memset(f, 0, sizeof(f));
	
	int a, b, na, nb;
	for(a = xt; a <= K; a++) {
		na = a - xt;
		int t = a + na; 
		f[t] = C(t, a);
	}
	
	int ans = 0;
	for(b = yt; b <= K; b++) {
		nb = b - yt;
		if(b + nb > K) continue;
		int t = K - b - nb;
		ans += (LL) C(K, t) * f[t] % P * C(b + nb, b) % P; 
		ans %= P;
	}
	cout << ans << endl;
}

int main() {
	int i, T = inp();
	fac[0] = 1;
	for(i = 1; i < MaxN; i++) fac[i] = (LL) fac[i - 1] * i % P;
	rfac[MaxN - 1] = exp(fac[MaxN - 1], P - 2);
	for(i = MaxN - 1; i; i--) rfac[i - 1] = (LL) rfac[i] * i % P;
	 
	while(T--) solve();
	return 0;
}



