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

struct comp{ 
	double r, i;
	comp() { }	
	comp(double a, double b) : r(a), i(b) { }
};

const int N = (1 << 19), MaxN = (N << 1) + 10;
const int K = 32767, L = 15, P = 1000000007;
 
comp add(comp a, comp b) { return comp(a.r + b.r, a.i + b.i); }
comp sub(comp a, comp b) { return comp(a.r - b.r, a.i - b.i); }
comp mul(comp a, comp b) { return comp(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);}
comp div(comp a, double b){	return comp(a.r/b, a.i/b); }
comp conj(comp x) { return comp(x.r, -x.i); }

int add(int x, int y) { return x + y >= P ? x + y - P : x + y; }
int sub(int x, int y) {	return x - y < 0 ? x - y + P : x - y;  }
int mul(int x, int y) {	return (LL)x * y % P; }
int exp(int x, LL n) {
	int res = 1;
	for(; n; n >>= 1) {
		if(n & 1) 
			res = mul(res, x);
		x = mul(x, x);
	}
	return res;
}
	
comp eps[MaxN]; 
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
    static comp x[MaxN], y[MaxN], z[MaxN], w[MaxN];
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

int n, y, a[MaxN];
int fac[MaxN], rfac[MaxN], Ap[MaxN], Bp[MaxN], h[MaxN];

int bin(int n, int m) {
	return n < 0 || m < 0 || n < m ? 0 : mul(fac[n], mul(rfac[m], rfac[n - m]));
}

void Euler(int p, int ans[]) {
	int n = a[p], i, j;
	//https://en.wikipedia.org/wiki/Eulerian_number 
	//Explicit formula
	
	for(i = 0; i <= n; i++) Ap[i] = exp(i, n);
	for(i = 0; i <= n; i++) {
		int co = bin(n + 1, i);
		Bp[i] = (i & 1) ? P - co : co;
	}
	conv(n + 1, Ap, n + 1, Bp, n + 1, ans);
	
	/*
	n = 1
	A = x 
	n = 2
	A = x(x+1)
	n = 3
	A = x(x^2+4x+1)
	for(i = 0; i <= n; i++) 
		printf("%d ", ans[i]);
	cerr << endl;
	*/
}

vector <int> vec[MaxN]; 

namespace temp {
	int x[MaxN], y[MaxN], z[MaxN]; vector<int>c;
	vector<int> vector_mul(vector <int> a, vector <int> b) {
		int i;
		for(i = 0; i < a.size(); i++) x[i] = a[i];
		for(i = 0; i < b.size(); i++) y[i] = b[i];
		conv(a.size(), x, b.size(), y, a.size() + b.size() - 1, z);
		c.clear(); 
		for(i = 0; i < a.size() + b.size() - 1; i++) 
			c.emplace_back(z[i]);
		return c;
	}
}

void solve(int l, int r) {
	if(l == r) {
		// don't know what should do actually ...
		return;
	}
	int ul = 0, ur = 0;
	int i, j, o = r - 1;
	for(int i = l; i <= r; i++) ur += a[i] + 1;
	for(int i = l; i < r; i++) {
		ul += a[i] + 1;
		ur -= a[i] + 1;
		if(ul >= ur) 
			o = i, i = r + 1; 
	}
	
	solve(l, o);
	solve(o + 1, r);
	vec[l] = temp :: vector_mul(vec[l], vec[o + 1]);
}

int u[MaxN];
void divide() {
	int i, M = 0; 
	for(i = 1; i <= n; i++) M += a[i] + 1;
	int ans = 0; int C = 1;
	for(i = 1; i <= M; i++) C = mul(C, y + M + 2 - i);
	for(i = 1; i <= M; i++) C = mul(C, exp(i, P - 2));
	
	for(i = 0; i < min(M, y + 1); i++) {
		C = mul(C, y + 1 - i);
		C = mul(C, exp(y + M + 1 - i, P - 2));
		ans = add(ans, mul(C, u[i]));
	}
				
	cout << ans << endl;
}
int main() {
	int i, j; init();
	fac[0] = 1;
	for(i = 1; i < MaxN; i++) fac[i] = mul(fac[i - 1], i);
	rfac[MaxN - 1] = exp(fac[MaxN - 1], P - 2);
	for(i = MaxN - 1; i; i--) rfac[i - 1] = mul(rfac[i], i);
	
	n = inp();
	y = inp();
	
	for(i = 1; i <= n; i++) a[i] = inp();
	random_shuffle(a + 1, a + n + 1);
	
	for(i = 1; i <= n; i++) {
		Euler(i, h);
		for(j = 0; j <= a[i]; j++) vec[i].emplace_back(h[j]);
	}
	
	solve(1, n);
	
	for(i = 0; i < vec[1].size(); i++) u[i] = vec[1][i];
	divide();
	
	return 0;
}



