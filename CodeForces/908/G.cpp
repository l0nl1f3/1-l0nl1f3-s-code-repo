#include <bits/stdc++.h>

#define MP make_pair
#define PB push_back
#define FO(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)

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

const int MaxN = 777, P = 1e9 + 7;

int f[MaxN][MaxN][2]; string n;

int main() {
	int i, j, k, o, d;
	cin >> n; int nL = n.size(), ans = 0;
	for(d = 1; d <= 9; d++) {
		f[0][0][1] = 1;
		for(i = 0; i < nL; i++) 
			for(j = 0; j <= i; j++)
				for(o = 0; o <= 1; o++) 
					for(k = 0; k <= (o ? n[i] - '0' : 9); k++) 
						(f[i + 1][j + (k >= d)][k < n[i] - '0' ? 0 : o] += f[i][j][o]) %= P; 
		k = 1;
		for(j = 1; j <= nL; j++, k = (k * 10ll + 1) % P)
			ans = (ans + (LL) k * (f[nL][j][0] + f[nL][j][1])) % P;
		memset(f, 0, sizeof(f));
	}
	cout << ans << endl;
	return 0;
}

