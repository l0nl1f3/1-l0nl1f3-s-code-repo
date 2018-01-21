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

const int MaxP = 101234;

LL l, r, f[2][2][MaxP], g[MaxP], h[MaxP], t[MaxP]; int p, L, a[100], mu[MaxP], pr[MaxP], pn, np[MaxP];

LL solve(LL n) {
	if(!n) return 0;
	int i, j, k, l, m;
	for (L = 0; n; n /= p) a[++L] = n % p; 
	reverse(a + 1, a + L + 1);
	
	for(l = 0; l <= 1; l++)
			for(j = 0; j < p; j++)
				f[0][l][j] = 0;
					
	f[0][1][0] = 1;	
	for (i = 1; i <= L; i++) {
		int cur = i & 1, q = cur ^ 1;
		for (l = 0; l <= 1; l++)
				for(j = 0; j < p; j++)
					f[cur][l][j] = 0;
		for (l = 0; l <= 1; l++) {
			m = 0; {
				if(!l) {
					int u = p - 1;
					for (k = m; k <= u; k++) 
						f[cur][l && (k == a[i])][k] += f[q][l][0];
					
					for (j = 1; j <= u; j++) h[j] = f[q][l][j], t[j] = g[j] = 0;
					
					for (j = 1; j <= u; j++)
						for(k = j; k <= u; k += j)
							t[j] += h[k];
					
					for (j = 1; j <= u; j++)
						if(mu[j])
							for (k = j; k <= u; k += j)
								mu[j] > 0 ? g[k] += t[j] : g[k] -= t[j];

					for(k = m; k <= u; k++)
						f[cur][0][k] += g[k];
				} else {
					int u = a[i];
					LL x = f[q][l][a[i - 1]];
					if(!a[i - 1])
						for(k = m; k <= u; k++)
							f[cur][k == a[i]][k] += x;
					else
						for(k = m; k <= u; k++)
							if(__gcd(k, a[i - 1]) == 1)
								f[cur][k == a[i]][k] += x;
				}
			} 
		} 
	}
	
	LL ans = 0;
	for (i = 1; i < p; i++)
			for (m = 0; m <= 1; m++)
				ans += f[L & 1][m][i];
	return ans;
}

int main() {
	p = MaxP - 1;
	mu[1] = 1;
	for (int i = 2; i <= p; i++) {
		if (!np[i]) pr[++pn] = i, mu[i] = -1;
		for (int j = 1; j <= pn && i * pr[j] <= p; j++) {
			np[i * pr[j]] = 1;
			if (i % pr[j] == 0) {
				mu[i * pr[j]] = 0;
			 	break;
			}
			mu[i * pr[j]] = -mu[i];
		}
	}
	
	int T = read();
	while(T--) {
		cin >> l >> r >> p;
		// l = 1e18 - 1e7;
		// r = 1e18;
		// p = 1e5;
		cout << solve(r) - solve(l - 1) << endl;
	}
	return 0;
}



