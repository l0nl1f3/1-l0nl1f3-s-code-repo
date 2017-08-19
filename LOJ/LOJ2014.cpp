#include <bits/stdc++.h>

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

const int MaxN = 201234, MaxL = 20, P = (1e9 + 7);

int f[MaxN * MaxL], a[MaxN][MaxL], pl[MaxN * MaxL], pr[MaxN * MaxL], pc;

int find(int x) {
	return f[x] == x ? x : f[x] = find(f[x]);
} 

int merge(int x, int y) {
	f[find(x)] = find(y); 
}

int n, q;
int main() {
	int i, j;
	n = inp(); q = inp();
	for(i = 1; i <= n; i++)
		for(j = 0; j < MaxL; j++)
			++pc, a[pl[pc] = i][pr[pc] = j] = pc, f[pc] = pc;
	
	for(i = 1; i <= q; i++) {
		int u = inp(), v = inp(), s = inp(), t = inp();
		for(j = MaxL - 1; ~ j; j--)
			if(u + (1 << j) - 1 <= v) {
				merge(a[u][j], a[s][j]),
				u += (1 << j), s += (1 << j);
			}
	}
	
	for(j = MaxL - 1; j; j--) {
		for(i = 1; i <= n; i++) {
			int u = find(a[i][j]);
			int L = pl[u], R = pr[u];
			merge(a[L][R - 1], a[i][j - 1]);
			merge(a[L + (1 << R - 1)][R - 1], a[i + (1 << R - 1)][R - 1]);
		}
	}
	
	int p = 0;
	for(i = 1; i <= n; i++) if(f[a[i][0]] == a[i][0]) ++p;
	int ans = 9;
	for(i = 1; i < p; i++) ans = ans * 10ll % P;
	
	cout << ans; 
	return 0;
}



