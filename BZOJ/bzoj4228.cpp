#include <bits/stdc++.h>
  
#define fir first
#define sec second
#define MP make_pair
#define PB push_back
  
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
  
const int MaxN = (1 << 21) + 10;
int N = 1 << 21;
 
typedef unsigned int uint32;
typedef long long int64;
typedef unsigned long long uint64;
typedef uint32 word;
typedef uint64 dword;
typedef int sword;
 
word mod, Modinv, r2; 
const int word_bits = sizeof(word) * 8;
struct mint{
  word x;
  mint(): x(0) {}
  mint(word _x): x(init(_x)) {}
 
  mint& operator += (const mint& rhs) {
    if ((x += rhs.x) >= mod) x -= mod;
    return *this;
  }
  mint& operator -= (const mint& rhs) {
    if (sword(x -= rhs.x) < 0) x += mod;
    return *this;
  }
  mint& operator *= (const mint& rhs) {
    x = reduce(dword(x) * rhs.x);
    return *this;
  }
  mint operator + (const mint &rhs) const {
    return mint(*this) += rhs;
  }
  mint operator - (const mint &rhs) const {
    return mint(*this) -= rhs;
  }
  mint operator * (const mint &rhs) const {
    return mint(*this) *= rhs;
  }
  mint pow(uint64 e) const {
    mint ret(1);
    for (mint base = *this; e; e >>= 1, base *= base) {
      if (e & 1) ret *= base;
    }
    return ret;
  }
  word get() const {
    return reduce(x);
  }
  static word modulus() {
    return mod;
  }
  static word init(word w) {
    return reduce(dword(w) * r2);
  }
  static void set_mod(word m) {
    mod = m;
    Modinv = mul_inv(mod);
    r2 = -dword(mod) % mod;
  }
  static word reduce(dword x) {
    word y = word(x >> word_bits) - word((dword(word(x) * Modinv) * mod) >> word_bits);
    return sword(y) < 0 ? y + mod : y;
  }
  static word mul_inv(word n, int e = 6, word x = 1) {
    return !e ? x : mul_inv(n, e - 1, x * (2 - x * n));
  }
};
mint TWO;
 
mint add(mint a, mint b) {
    return a + b;
}
mint mul(mint a, mint b) {
    return a * b;
}
mint sub(mint a, mint b) {
    return a - b;
}
 
const int K = 20;
mint eps[MaxN], ieps[MaxN], g[K + 1], ng[K + 1], gw[MaxN], ngw[MaxN]; int rev[MaxN], lg[MaxN];
inline void init() {
    int i, j;
    g[K] = ((mint)3).pow((mod - 1) / N);
	ng[K] = g[K].pow(mod - 2),
    for(i = K - 1; ~i =; i--)
        g[i] = g[i + 1] * g[i + 1], ng[i] = ng[i + 1] * ng[i + 1];
    for(i = 0; i <= K; i++){
        gw[1 << i] = ngw[1 << i] = mint(1);
        for(j = 1; j < 1 << i ;j++){
            gw[(1 << i) + j]=gw[(1 << i) + j - 1] * g[i];
            ngw[(1 << i) + j]=ngw[(1 << i) + j - 1] * ng[i];
        }
    }
}
  
 
inline void trans(int n, mint x[], int op) {
    int nL = 0, tn = 1;
    while(tn < n) {
        nL++; tn <<= 1;
    } 
    for(int i = 1; i < n; i++) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << nL - 1);        
        if(i < rev[i]) swap(x[i], x[rev[i]]);
    }
    for(int e = 0; (1 << e) < n; e++) {
        int m = 1 << e, m2 = m << 1;
        mint *_w = (op > 0 ? gw : ngw); _w += (1 << e);
        for(int i = 0; i < n; i += m2) {
            mint *w = _w;
            for(int j = 0; j < m; j++, w++) {
                mint &A = x[i + j + m], &B = x[i + j], t = *w * A;
                A = B - t; B += t; 
            }
        } 
         
    }
}
  
inline void dft(int n, mint x[]) {
    trans(n, x, 1);
}
  
inline void idft(int n, mint x[]) {
    trans(n, x, -1); mint in = mint(n).pow(mod - 2);
    for (int i = 0; i < n; i++) x[i] = x[i] * in;
}
  
mint temp[MaxN];
inline void inv(int n, mint x[], mint y[]) {
    mint *t = temp;
    fill(y, y + (n << 1), 0);
    y[0] = x[0].pow(mod - 2);
    for (int i = 4, j = 2; j <= n; j = i, i <<= 1) {
        copy(x, x + j, t);
        fill(t + j, t + i, 0);
        dft(i, t);
        dft(i, y);
        for (int k = 0; k < i; k++) y[k] = y[k] * (mint(2) - t[k] * y[k]);
        idft(i, y);
        fill(y + j, y + i, 0);
    }
}
  
void conv(int n, mint x[], mint y[], mint z[]) {
    dft(n, x); dft(n, y);
    for(int i = 0; i < n; i++) z[i] = mul(x[i], y[i]);
    idft(n, z);
}
 
int n, m;
 
mint x[MaxN], y[MaxN], z[MaxN], w[MaxN], fac[MaxN], rfac[MaxN], xz[MaxN], yw[MaxN], yww[MaxN], ans[MaxN], yy[MaxN], pw[MaxN];
 
int main() {
    int i;
    mint :: set_mod(1004535809);
    int nn = read(); // ();
    N = 1 << 21; init();
    //cerr << clock() << " ms\n";
    fac[0] = rfac[0] = 1;
    for(i = 1; i < MaxN; i++) fac[i] = fac[i - 1] * i;
    rfac[i - 1] = fac[i - 1].pow(mod - 2);
    for(--i; i; i--) rfac[i - 1] = mul(rfac[i], i);
     
    for(n = 1; n <= nn; n <<= 1); // N = n << 1;
      
    // x[] = e^H(x) checked
    x[0] = x[1] = 1; x[2] = 2;
    for(i = 3; i < n; i++) {
        x[i] = mul(sub(mul(x[i - 1], 2 * i - 1), mul(mul(i - 1, i - 1), x[i - 2])), 2);
        x[i] = add(x[i], mul(mul(i - 2, i - 1), x[i - 3]));
        x[i] = mul(x[i], mod + 1 >> 1);
    } 
    for(i = 0; i < n; i++) x[i] = mul(x[i], rfac[i]);
     
    // y[] = (1-x^3)^1/6
    yy[0] = 2; yy[1] = mod - 6; yy[2] = mod - 30;
    mint co = 11;
    for(i = 3; i < n; i++) yy[i] = mul(yy[i - 1], co), co = add(co, 6);
    mint pw = 1, r6 = mint(6).pow(mod - 2);
    for(i = 0; i * 3 < n; i++) pw = mul(pw, r6), y[i * 3] = mul(yy[i], mul(pw, rfac[i]));
    y[0] = 1;
     
    // z[] = e^(1/2ln(1-x)) = (1-x)^1/2 
    z[0] = 2; z[1] = mod - 2; z[2] = mod - 2;
     
    pw = 1;
    for(i = 3; i < n; i++) z[i] = mul(z[i - 1], 2 * i - 3); 
    for(i = 0; i < n; i++) {
        pw = mul(pw, mod + 1 >> 1);
        z[i] = mul(z[i], mul(pw, rfac[i]));
    }
     
     
    // w[] = e^(x/2 + x^2/4)
    w[0] = 1; w[1] = 1;
    for(i = 2; i < n; i++) w[i] = add(w[i - 1], mul(2 * (i - 1), w[i - 2]));
    pw = 1;
    for(i = 0; i < n; i++) {
        w[i] = mul(w[i], mul(pw, rfac[i]));
        pw = mul(pw, mod + 1 >> 1);
    }
     
//  cerr << clock() << " ms\n";
    conv(n << 1, z, w, xz);
    for(i = n; i < (n << 1); i++) xz[i] = 0;  
//  cerr << clock() << " ms\n";
    inv(n, xz, yw);
//  cerr << clock() << " ms\n";
    conv(n << 1, yw, y, yww);
    for(i = n; i < (n << 1); i++) yww[i] = 0; 
    //conv(n << 1, yww, x, ans);
    mint ans = 0;
    for(i = 0; i <= nn; i++)
        ans = add(ans, mul(yww[i], x[nn - i]));
    cout << mul(ans, fac[nn]).get() << endl;    
//  cerr << clock() << " ms\n"; 
    return 0;
}
