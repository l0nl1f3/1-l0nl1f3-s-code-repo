#include <bits/stdc++.h>

#define exp MDSB
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

const int MaxN = 101234, MaxM = 1001234, MaxP = 6;
const int base = 1234567, p1 = 1000000007, p2 = 1000000009;
typedef pair<int, int> Pint;

Pint operator + (Pint a, Pint b) {
	(a.fir += b.fir) %= p1;
	(a.sec += b.sec) %= p2;
	return a;		
}

Pint operator * (Pint a, int x) {
	a.fir = (LL) a.fir * x % p1;
	a.sec = (LL) a.sec * x % p2;
	return a;
}

Pint operator - (Pint a, Pint b) {
	a.fir = (a.fir - b.fir + p1) % p1;
	a.sec = (a.sec - b.sec + p2) % p2;
	return a;
} 

vector<int> e[MaxN]; int n, a[MaxN];

int d[MaxM];
void prime_init() {
	for(int i = 2; i < MaxM; i++)
		if(!d[i]) 
			for(int j = i; j < MaxM; j += i)
				d[j] = i;
}

Pint operator -= (Pint &a, Pint b) {
	a = a - b;
}

Pint operator += (Pint &a, Pint b) {
	a = a + b;
}

Pint exp[MaxM], rev, pos; 
map<Pint, int> table; vector<pair<Pint, int> > vec;
int cnt[MaxM];

void modify(int x, int y) {
	while(x != 1) {
		int z = d[x];
		if(cnt[z]) {
			pos -= exp[z] * cnt[z];
			rev -= exp[z] * (3 - cnt[z]); 
		}
		cnt[z] = (cnt[z] + y + 3) % 3;
		if(cnt[z]) {
			pos += exp[z] * cnt[z];
			rev += exp[z] * (3 - cnt[z]); 
		}
		x /= z; 
	}
}

vector<int> vis; int siz[MaxN], hug[MaxN]; 
void dfs(int x, int fa = 0) {
	vis.emplace_back(x); 
	siz[x] = 1; hug[x] = 0;
	for(auto y : e[x]) 
		if(y != fa) {
			dfs(y, x);
			siz[x] += siz[y];
			cmax(hug[x], siz[y]); 
		}
}  

int make(int x, int fa, int dt = 1) {
	int z = a[x]; 
	modify(z, 1);
	vec.emplace_back(make_pair(pos, dt));
	int ans = -1;
	if(table.count(rev)) 
		cmax(ans, dt + table[rev] + 1);
	for(auto y : e[x])
		if(y != fa) 
			cmax(ans, make(y, x, dt + 1));
	modify(z, -1);
	return ans;
}

int decomp(int x) {
	int ans = -1;
	table.clear(); vis.clear();
	dfs(x, x);
	int N = vis.size(), cent = x;
	for(auto x : vis) 
		if(hug[x] <= N/2 && (N - siz[x]) <= N/2) {
			cent = x; break; 
		} 
	modify(a[cent], -1); table[pos] = 0;
	if(pos == make_pair(0, 0)) ans = 1;
	
	for(auto y : e[cent]) {
		cmax(ans, make(y, cent));
		for(auto p : vec) 
			cmax(table[p.fir], p.sec);
		vec.clear();
	}
	
	modify(a[cent], 1);
	
	for(auto y : e[cent]) {
		for(int i = 0; i < e[y].size(); i++) {
			if(e[y][i] == cent) {
				swap(e[y][i], e[y].back()); 
				e[y].pop_back();
				break;
			}
		}
		cmax(ans, decomp(y));
	} 
	return ans;
}
void solve() {
	int i;
	n = inp();
	for(i = 1; i <= n; i++) a[i] = inp();
	for(i = 1; i <= n; i++) e[i].clear();
	
	for(i = 1; i < n; i++) {
		int u = inp(), v = inp();
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	
	printf("%d\n", decomp(1));
}
int main() {
	int T = inp();
	prime_init();
	exp[0] = make_pair(1, 1);
	for(int i = 1; i < MaxM; i++) exp[i] = exp[i - 1] * base;
	
	while(T--) 
		solve();
	return 0;
}



