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
	comp() { }	
	comp(double a, double b) : r(a), i(b) { }
};
const int N = (1 << 19), MAXN = (N << 1) + 10;
const int K = 32767, L = 15;
int P; 
comp add(comp a, comp b) { return comp(a.r + b.r, a.i + b.i); }
comp sub(comp a, comp b) { return comp(a.r - b.r, a.i - b.i); }
comp mul(comp a, comp b) { return comp(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);}
comp div(comp a, double b){	return comp(a.r/b, a.i/b); }
comp conj(comp x) { return comp(x.r, -x.i); }
int add(int x, int y) { return x + y >= P ? x + y - P : x + y; }
int sub(int x, int y) {	return x - y < 0 ? x - y + P : x - y;  }
int mul(int x, int y) {	return (LL)x * y % P; }
int fexp(int x, LL n) {
	int res = 1;
	for(n = (n % (P - 1) + P - 1) % (P - 1); n; n >>= 1, x = mul(x, x)) 
		if(n & 1) res = mul(res, x);
	return res;
}
	
comp eps[MAXN]; 
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
void inv(int n, int f[], int g[]) {
    if (n == 1) g[0] = fexp(f[0], P - 2);
    else {
        int l = n + 1 >> 1, i;
        static int t[MAXN];
        inv(l, f, g);
        conv(n, f, l, g, n, t);
		conv(l, g, n - l, t + l, n - l, g + l);
        for(i = l; i < n; i++) if (g[i]) g[i] = P - g[i];
    }
}
vector<int> s;
int n, f[MAXN], g[MAXN], df[MAXN], h[MAXN];
int main(){
	int i;
	n = inp(); P = inp(); init();
	for(i = 1; i <= n; i++) f[i] = inp(); f[0] = 1;
	inv(n + 1, f, g);
	for(i = 0; i <= n; i++) f[i] = mul(i, f[i]);
	conv(n + 1, f, n + 1, g, n + 1, h);
	for(i = 1; i <= n; i++)
		if(h[i]){
			s.push_back(i);
			for(int j = i + i; j <= n; j += i)
				h[j] = sub(h[j], i);
		}
	printf("%d\n",s.size());
	for(i = 0; i < s.size(); i++) printf("%d%c", s[i], " \n"[i == s.size() - 1]);
	return 0;
}
