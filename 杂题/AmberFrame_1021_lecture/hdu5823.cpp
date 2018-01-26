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
	for (ch = getchar(); !isdigit(ch); ch = getchar())
		if (ch == '-') f = -1;
	for (; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	return x * f;
}

const int MaxN = 18;
int n, f[1 << MaxN][MaxN], h[1 << MaxN], g[1 << MaxN]; char e[MaxN][MaxN];

void solve() {
	n = read();
	for (int i = 0; i < n; i++)
		scanf("%s", e[i]);
	int u = 1 << n;
	memset(f, 0, sizeof(f));
	for (int m = 0; m < u; m++) {
		h[m] = f[m][1] = 1;
		for (int i = 0; i < n; i++)
			if (m >> i & 1)
				for (int j = 0; j < n; j++)
					if(m >> j & 1)
						if(e[i][j] == '1') {
							h[m] = f[m][1] = 0; 
							break;
						}
	}	
	for (int i = 0; i < n; i++)
		for (int s = 0; s < u; s++)
			if(s >> i & 1) h[s] |= h[s ^ (1 << i)];
	
	for (int x = 2; x <= n; x++) {
		for (int s = 0; s < u; s++) g[s] = !!f[s][x - 1];
		for (int i = 0; i < n; i++)
			for (int s = 0; s < u; s++)
				if(s >> i & 1) 
					g[s] += g[s ^ (1 << i)];
		for (int s = 0; s < u; s++)
			f[s][x] = g[s] * h[s];
		for(int i = 0; i < n; i++)
			for (int s = 0; s < u; s++)
				if (s >> i & 1)
					f[s][x] -= f[s ^ (1 << i)][x];
	}
	
	unsigned ans = 0, coe = 1;
	for (int m = 0; m < u; m++) {
		int val = 0;
		for (val = 1; !f[m][val] && val <= n; val++);
		cout << val << " "; 
		ans = ans + coe * val;
		coe = coe * 233u;
	}
	cout << endl;
	cout << ans << endl;
		
}

int main() {
	int T = read(); while(T--) solve();
	return 0;
}




