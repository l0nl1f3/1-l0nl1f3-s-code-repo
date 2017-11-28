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
 
const int MaxN = 2001234, P = 1000000007;
 
int T, n, m, K;
struct Int {
	int x, p; // n = xK + p;
	Int() {}
	Int(int n) : x(n / K), p(n % K) {}
	Int(int x, int p) : x(x), p(p) {}
	Int operator + (Int b) {
		return Int((x + b.x + (p + b.p >= K)) % P, (p + b.p) % K); 
	}
	Int operator * (Int b) {
		int X = ((LL) x * b.x % P * K % P + (LL) x * b.p % P) % P + (LL) b.x * p % P;
		X %= P; (X += (LL) p * b.p / K) %= P;
		int B = (LL) p * b.p % K;
		return Int(X, B);
	}
	// (x1K+p1)(x2K+p2)=x1x2K^2+x1p2K+p1x2K+p1p2 
	// (x1x2K+x1p2+x2p1+(p1p2/K)) K + p1p2%K
}fac[MaxN], fib[MaxN];
 
int solve(int l, int r) {
	Int ans = Int(0);
	for(int i = l; i <= r; i++)
	 	ans = ans + fib[i] * fac[i];
	return ans.x;
}
 
int main() {
	int i;
	T = read();
	while(T--) {
		n = read(); m = read(); K = read();
		fac[0] = Int(1);
		for(i = 1; i < MaxN; i++) fac[i] = fac[i - 1] * Int(i);
		fib[0] = fib[1] = Int(1);
		for(i = 2; i < MaxN; i++) fib[i] = fib[i - 1] + fib[i - 2];
		printf("%d\n", solve(n, m));
	}
	return 0;
}
 
