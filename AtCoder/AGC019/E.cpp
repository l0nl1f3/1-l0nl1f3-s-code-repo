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

const int M = 23, P = 998244353, G = 3;
const int MaxN = (1 << 19) + 10;
int N = 1 << 18;

inline int add(int a, int b) {
    return (a + b) % P;
}

inline int sub(int a, int b) {
    return (a - b + P) % P;
}

inline int mul(int a, int b) {
    return (LL)a * (LL)b % P;
}

inline int exp(int a, int b) {
    int ans = 1;
    for (; b; b >>= 1) {
        if (b & 1) ans = mul(ans, a);
        a = mul(a, a);
    }
    return ans;
}

inline int inv(int x) {
    return exp(x, P - 2);
}

int eps[MaxN], ieps[MaxN];

inline void init() {
    int g = exp(G, (P - 1) / N), ig = inv(g);
    eps[0] = ieps[0] = 1;
    for (int i = 1; i < N; i++) eps[i] = mul(eps[i - 1], ig), ieps[i] = mul(ieps[i - 1], g);
}

inline void trans(int n, int x[], int w[]) {
    for (int i = 0, j = 0; i != n; i++) {
        if (i < j) std::swap(x[i], x[j]);
        for (int l = n >> 1; (j ^= l) < l; l >>= 1);
    }
    for (int i = 2; i <= n; i <<= 1) {
        int l = i >> 1, d = N / i;
        for (int j = 0; j != n; j += i)
            for (int k = 0; k != l; k++) {
                int t = mul(x[j + k + l], w[d * k]);
                x[j + k + l] = sub(x[j + k], t);
                x[j + k] = add(x[j + k], t);
            }
    }
}

inline void dft(int n, int x[]) {
    trans(n, x, eps);
}

inline void idft(int n, int x[]) {
    trans(n, x, ieps);
    for (int i = 0, in = inv(n); i < n; i++) x[i] = mul(x[i], in);
} 

char A[MaxN], B[MaxN];
int n, fac[MaxN], rfac[MaxN], x[MaxN], y[MaxN], z[MaxN];
int main() {
	int i;
	init();
	scanf("%s%s", A + 1, B + 1); n = strlen(A + 1);
	int X = 0, Y = 0;
	for(i = 1; i <= n; i++) {
		if(A[i] == '1' && B[i] == '1')
			++X;
		if(A[i] == '1' && B[i] == '0')
			++Y;
	}
	for(fac[0] = i = 1; i < MaxN; i++) fac[i] = mul(fac[i - 1], i);
 	rfac[MaxN - 1] = inv(fac[MaxN - 1]);
	
	for(i = MaxN - 1; i; i--) rfac[i - 1] = mul(rfac[i], i); 
	int L = 1;
	while(L <= X + X + 1) L <<= 1;
	for(i = 0; i <= X; i++) x[i] = rfac[i + 1];
	z[0] = 1;
	for(int t = Y; t; t >>= 1) {
		if(t & 1) {
			dft(L, x); dft(L, z);
			for(i = 0; i < L; i++) z[i] = mul(z[i], x[i]);
			idft(L, z); idft(L, x);
		}
		
		dft(L, x);
		for(i = 0; i < L; i++) x[i] = mul(x[i], x[i]);
		idft(L, x);
	}
	
	int ans = 0;
	for(i = 0; i <= X; i++) ans = add(ans, z[i]);
	int co = mul(fac[X + Y], mul(fac[X], fac[Y]));
	
	printf("%d", mul(ans, co)); 
	return 0;
}



