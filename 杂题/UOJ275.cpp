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

const int MaxN = 123, P = 1e9 + 7;
int T, p, L, a[MaxN], b[MaxN], f[MaxN][2][2]; LL n, m;

int main() {
	int i, j, k, l1, l2;
	cin >> T >> p;
	while (T--) {
		cin >> n >> m; cmin(m, n);
		int ans = (m % P + 2) * (m % P + 1) % P * (P + 1 >> 1) % P;
		ans = (ans + (n - m) % P * (m % P + 1)) % P;
		L = 0;
		for (; n; n /= p) a[++L] = n % p;
		for (i = 1; i <= L; i++) b[i] = m % p, m /= p;
		memset(f, 0, sizeof(f)); 
		f[L + 1][1][1] = 1;
		for (i = L; i; i--) 
			for (l1 = 0; l1 <= 1; l1++)
				for(l2 = 0; l2 <= 1; l2++)
					for (j = 0; j <= (l1 ? a[i] : p - 1); j++)
						for (k = 0; k <= (l2 ? b[i] : p - 1) && k <= j; k++) {	
							int _l1 = l1 && (j == a[i]);
							int _l2 = l2 && (k == b[i]);
							(f[i][_l1][_l2] += f[i + 1][l1][l2]) %= P;
						}
		for (l1 = 0; l1 <= 1; l1++)
			for (l2 = 0; l2 <= 1; l2++)
				ans = (ans - f[1][l1][l2] + P) % P;
		cout << ans << endl;				
	}
	return 0;
}



