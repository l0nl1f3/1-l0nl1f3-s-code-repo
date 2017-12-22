#include <bits/stdc++.h>

#define fir first
#define sec second
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

const int MaxN = 1001234;
int n; vector<int> e[MaxN], d;
int f[MaxN], s[MaxN];
void dfs(int x, int fa = 0) {
	s[x] = 1;
	for(auto y : e[x]) 
		if(y != fa) 
			dfs(y, x), 
			s[x] += s[y];
	f[__gcd(s[x], n)]++;
} 
int main() {
	int i, j;
	n = read();
	for(i = 1; i < n; i++)
		if(n % i == 0)
			d.PB(i);
	for(i = 1; i < n; i++) {
		int u = read(), v = read();
		e[u].PB(v); e[v].PB(u);
	}
	dfs(1); f[__gcd(s[1], n)]--;
	for(i = 0; i < d.size(); i++)
		for(j = i + 1; j < d.size(); j++)
			if(d[j] % d[i] == 0)
				f[d[i]] += f[d[j]];
	vector<int> ans;
	for(auto x : d) 
		if(f[x] == n / x - 1)
			ans.PB(n / x - 1);
	sort(ans.begin(), ans.end());
	for(auto x : ans) printf("%d ", x); 
	return 0;
}

