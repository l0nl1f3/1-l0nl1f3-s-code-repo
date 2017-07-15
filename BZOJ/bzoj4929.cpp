#include<bits/stdc++.h>

#define FO(x) {freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout);}
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
struct comp{ 
	double r, i;
	comp() {
	}	
	comp(double a, double b) : r(a), i(b) {
		
	}
};
const int P = 1000003, N = (1 << 19), MAXN = (N << 1) + 10;
const int K = 32767, L = 15; 
comp add(comp a, comp b) { return comp(a.r + b.r, a.i + b.i); }
comp sub(comp a, comp b) { return comp(a.r - b.r, a.i - b.i); }
comp mul(comp a, comp b) { return comp(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);}
comp div(comp a, double b){	return comp(a.r/b, a.i/b); }
comp conj(comp x) { return comp(x.r, -x.i); }
	
comp eps[MAXN], ieps[MAXN];
void init() {
	double pi = acos(-1);
	for(int i = 0; i < N; i++)
		eps[i] = comp(cos(2 * pi * i /N), sin(2 * pi * i /N));
}

inline void trans(int n, comp x[], comp w[]) {
    for (int i = 0, j = 0; i != n; i++) {
        if (i < j) std::swap(x[i], x[j]);
        for (int l = n >> 1; (j ^= l) < l; l >>= 1);
    }
    for (int i = 2; i <= n; i <<= 1) {
        int l = i >> 1, d = N / i;
        for (int j = 0; j != n; j += i)
            for (int k = 0; k != l; k++) {
                comp t = mul(x[j + k + l], w[d * k]);
                x[j + k + l] = sub(x[j + k], t);
                x[j + k] = add(x[j + k], t);
            }
    }
}

inline void dft(int n, comp x[]) {
    trans(n, x, eps);
}
inline void idft(int n, comp x[]) {
    trans(n, x, eps);
    reverse(x + 1, x + n);
    for (int i = 0; i < n; i++) x[i] = div(x[i], n);
}
void conv(int na, int a[], int nb, int b[], int nc, int c[]) {
    int n, i;
    static comp x[MAXN], y[MAXN], z[MAXN], w[MAXN];
    for(n = 1; n < na + nb - 1; n <<= 1);
    for(i = 0; i < n; i++){
    	x[i] = i < na ? comp(a[i] & K, a[i] >> L): comp(0, 0);
    	y[i] = i < nb ? comp(b[i] & K, b[i] >> L): comp(0, 0);    	
	}
	dft(n, x); dft(n, y);
    comp r0(0.5, 0), r1(0, -0.5), r(0, 1);
	for(i = 0; i < n; i++){
		int j = (n - i) & (n - 1);
		comp x0, x1, y0, y1;
		x0 = mul(add(x[i], conj(x[j])), r0);
		x1 = mul(sub(x[i], conj(x[j])), r1);
		y0 = mul(add(y[i], conj(y[j])), r0);
		y1 = mul(sub(y[i], conj(y[j])), r1);
		z[i] = mul(x0, add(y0, mul(y1, r)));
		w[i] = mul(x1, add(y0, mul(y1, r)));
 	}
 	idft(n, z);
	idft(n, w); 
    for(i = 0; i < nc; i++) {
        int c00 = (LL)(z[i].r + 0.5) % P, c01 = (LL)(z[i].i + 0.5) % P;
        int c10 = (LL)(w[i].r + 0.5) % P, c11 = (LL)(w[i].i + 0.5) % P;
        c[i] = ((((LL)c11 << L) + c01 + c10 << L) + c00) % P;
    }
}
int add(int x, int y) {
	return x + y >= P ? x + y - P : x + y;
}
int sub(int x, int y) {
	return x - y < 0 ? x - y + P : x - y; 
}
int mul(int x, int y) {
	return (LL)x * y % P;
}
int fexp(int x, LL n) {
	int res = 1;
	for(n = (n % (P - 1) + P - 1) % (P - 1); n; n >>= 1, x = mul(x, x)) 
		if(n & 1) res = mul(res, x);
	return res;
}

int fac[MAXN], rfac[MAXN];
int n, b, c, d, e, x[MAXN], y[MAXN], p[MAXN], a[MAXN];

int solveb0(){
	int q, i;static int z[MAXN];
	b = d; d = e;
	for(q = 1; q <= n + n; q <<=1);
	for(i = 0; i < n; i++){
		x[n - i] = mul(fexp(d, i), fac[i]);
		x[n - i] = mul(x[n - i], a[i]);
		y[i] = rfac[i];
	}
	conv(n + 1, x, n + 1, y, n + 1, z);
	for(i = 0; i < n; i++) p[i] = z[n - i];
	
	memset(x, 0, sizeof(x));
	memset(y, 0, sizeof(y));
	int o = mul(b, fexp(d, P - 2));
	for(i = 0; i < n; i++) {
		int f0 = mul(rfac[i], fexp(o, i));
		int f1 = mul(p[i], fexp(c, (LL)i * i));
		x[i] = mul(f0, f1); 
	}
	for(i = 0; i < n + n; i++)
		y[i] = fexp(c, (LL) -(i - n) * (i - n));
	memset(z, 0, sizeof(z));
	conv(n + 1, x, n + n, y, n + n, z);
	
	for(i = 0; i < n; i++) printf("%d\n", mul(fexp(c, (LL)i * i), z[i + n]));
	
	return 0;
}

int solvec0(){
	int ans = 0, i;
	for(i = 0; i < n; i++)
		ans = add(ans, mul(fexp(b + d + e, i), a[i]));
	printf("%d\n", ans);
	for(i = ans = 0; i < n; i++)
		ans = add(ans, mul(fexp(e, i), a[i]));
	for(i = 1; i < n; i++)
		printf("%d\n", ans);
	return 0;
}

int h[MAXN];

int main() {
	int i, j, L;
	init();
	n = inp(), b = inp(), c = inp(), d = inp(); e = inp();
	for(i = 0; i < n; i++) a[i] = inp();
	
	int m = 2 * n - 1; 
	for(fac[0] = i = 1; i <= m; i++) fac[i] = mul(fac[i - 1], i);
	for(rfac[m] = fexp(fac[m], P - 2), i = m; i; i--)
		rfac[i - 1] = mul(rfac[i], i);
	
	if(c == 0) return solvec0(), 0;
	if(b == 0) return solveb0(), 0;
	
	int o = mul(d, fexp(b + b, P - 2)), q = mul(e, fexp(b, P - 2));
	q = sub(q, mul(o, o));
	for(i = 0; i < n; i++){
		x[i] = mul(a[i], fexp(b, i)); x[i] = mul(x[i], fac[i]);
		y[n - i] = mul(rfac[i], fexp(q, i));
	}
	conv(n, x, n + 1, y, n + n, h);

	for(i = 0; i < n; i++) p[i + i] = mul(h[i + n], rfac[i]);
	memset(x, 0, sizeof(x));
	memset(y, 0, sizeof(y));
	for(i = 0; i < m; i++){
		x[i] = mul(p[i], fac[i]);
		y[m - i] = mul(fexp(o, i), rfac[i]);
	}
	conv(m, x, m + 1, y, m + m, h);
	
	for(i = 0; i < m; i++) p[i] = mul(h[i + m], rfac[i]);
	memset(x, 0, sizeof(x));
	memset(y, 0, sizeof(y));
	for(i = 0; i < m; i++)x[i] = mul(p[i], fexp(c, (LL) i * i));
	for(i = 0; i < m + m; i++)
		y[i] = fexp(c, (LL) - (i - m) * (i - m));
	conv(m, x, m + m, y, m + n, h);
	for(i = 0; i < n; i++)printf("%d\n", mul(h[i + m], fexp(c, (LL)i * i)));
	return 0;
}



