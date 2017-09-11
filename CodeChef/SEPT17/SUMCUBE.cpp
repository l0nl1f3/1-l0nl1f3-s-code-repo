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
 
const int MaxN = 101234;
const int P = 1000000007;
 
int exp(int a, int n) {
	int res = 1;
	for(; n; n >>= 1) {
		if(n & 1)
			res = (LL) res * a % P;
		a = (LL) a * a % P;
	}
	return res;
}
 
int n, m, K, deg[MaxN], u[MaxN], v[MaxN]; 
vector<int> e[MaxN];
 
int run_1() {
	int ans = (LL) m * exp(2, n - 2) % P;
	cout << ans << endl; 
	return ans;
}
 
int run_2() {
	int i, j, ans = 0;
	
	int wayA = 0; 
	
	//for(i = 1; i <= n; i++) cout << deg[i] << " "; cout << endl;
	// 1 - 2 - 3 
	for(i = 1; i <= m; i++) {
		int x = u[i], y = v[i];
		wayA += ((deg[x] - 1) + (deg[y] - 1)) % P;
		wayA %= P;
	} 
 
	int wayB = (LL) m * (m - 1) % P;
	
	wayB = (wayB - wayA + P) % P;
	
	ans += (LL) wayA * exp(2, n - 3) % P; ans %= P;
	ans += (LL) wayB * exp(2, n - 4) % P; ans %= P;
	ans += (LL) m * exp(2, n - 2) % P; ans %= P;
	
	cout << ans << endl;
	
	return ans;
	/*
	int t = 0;
	for(i = 1; i <= m; i++) {
		for(j = 1; j <= m; j++) {
			int s = 0;
			for(s; s < (1 << n); s++) {
				int c1 = (s >> (u[i] - 1)) & 1;
				int c2 = (s >> (v[i] - 1)) & 1;
				int c3 = (s >> (u[j] - 1)) & 1;
				int c4 = (s >> (v[j] - 1)) & 1;
				if(c1 && c2 && c3 && c4) {
					ans++;
				}
			}
			if(u[i] == u[j] || v[i] == v[j] || u[i] == v[j] || u[j] == v[i]) {
			}else 
				++t;
		}
	}
	
	cout << t << endl; 
	*/
}
 
vector<pair<int, int> > tob;

namespace triple_count {
	LL ans = 0; 
	int deg[MaxN];
	
	map <pair<int, int>, int> us;
	int build(vector<pair<int, int> > tob) {
		int i, j;
		memset(deg, 0, sizeof(deg));
		us.clear();
		for(i = 0; i < tob.size(); i++) {
			deg[tob[i].fir]++, deg[tob[i].sec]++;
			us[tob[i]] = 1;
			us[make_pair(tob[i].sec, tob[i].fir)] = 1;
		}
		
		ans = 0;
		for(i = 0; i < tob.size(); i++) {
			int x = tob[i].fir, y = tob[i].sec;
			if(deg[x] > deg[y]) swap(x, y);
			for(auto t : e[x]) 
				if(us.count(make_pair(t, y)))
					++ans;
		}	
		
		ans *= 2; ans %= P;
		
		return ans;
	}
}
void run_3() {
	int ans = 0, i, j, k;
	int way1 = 2 * m;
	
	int way2 = 0;
	for(i = 1; i <= n; i++) {
		way2 += (LL) deg[i] * (deg[i] - 1) % P;
		way2 %= P;
	}
	
	tob.clear();
	int way3 = 0;
	for(i = 1; i <= m; i++) tob.emplace_back(make_pair(u[i], v[i]));
	way3 = triple_count :: build(tob);
	
	int way4 = 0;
	for(i = 1; i <= n; i++) {
		way4 += (LL) deg[i] * (deg[i] - 1) % P * (deg[i] - 2) % P;
		way4 %= P; 
	}
	
	int way5 = 0;
	
	for(i = 1; i <= m; i++) {
		int x = u[i], y = v[i];
		way5 += (LL) (deg[x] - 1) * (deg[y] - 1) % P;
		way5 %= P; 
	}
	
	(way5 *= 2) %= P; 
	way5 = (way5 - way3 + P) % P;
	
	int way6 = 2 * m + 4;
	way6 = (LL) way6 * way2 % P;
	(way6 += 2 * way3 % P) %= P;
	
	for(i = 1; i <= n; i++) {
		way6 = (way6 - (LL) 2 * deg[i] * deg[i] % P * (deg[i] - 1) % P) % P;
		if(way6 < 0) way6 += P;
	}
	
	for(i = 1; i <= m; i++) {
		int x = u[i], y = v[i];
		int sub = (LL) deg[y] * (deg[x] - 1) * 4 % P;
		(sub += (LL) (deg[y] - 1) * deg[x] % P * 4 % P) %= P; 
		way6 = (way6 - sub + P) % P; 
	}
	
	int em = 0;
	for(i = 1; i <= m; i++) {
		int x = u[i], y = v[i];
		em += (LL) 2 * (0ll + m - deg[x] - deg[y] + 1) % P;
		em %= P; 
	}
	
	em *= 2; em %= P;
	
	int way7 = (LL) m * m % P * m % P * 8 % P;
	(way7 -= 4ll * way1 % P) %= P;
	(way7 -= 24ll * way2 % P) %= P;
	(way7 -= 8ll * way3 % P) %= P;
	(way7 -= 8ll * way4 % P) %= P;
	(way7 -= 6ll * em % P) %= P;
	(way7 -= 24ll * way5 % P) %= P;
	(way7 -= 12ll * way6 % P) %= P;
	
	ans += (LL) exp(2, n) * way1 % P; ans %= P;
	ans += (LL) exp(2, n - 3) * 24 % P * way2 % P; ans %= P;
	ans += (LL) exp(2, n - 3) * 8 % P * way3 % P; ans %= P;	
	ans += (LL) exp(2, n - 4) * 8 % P * way4 % P; ans %= P;
	ans += (LL) exp(2, n - 4) * 6 % P * em % P; ans %= P;
	ans += (LL) exp(2, n - 4) * 24 % P * way5 % P; ans %= P;
	ans += (LL) exp(2, n - 5) * 12 % P * way6 % P; ans %= P;
	ans += (LL) exp(2, n - 6) * way7 % P; ans %= P;
	
	ans = (LL) ans * exp(8, P - 2) % P;
	cout << (ans + P) % P << endl;
}
 
set <int> eG[MaxN];

void force() {
	int ans = 0;
	for(int s = 0; s < (1 << n); s++) {
		int t = 0;
		for(int i = 0; i < n; i++) 
			if(s >> i & 1)
				for(int j = i + 1; j < n; j++)
					if(s >> j & 1)
						if(eG[i + 1].count(j + 1))
							++t;
		ans += exp(t, K); ans %= P;
	}
	for(int i = 1; i <= n; i++) eG[i].clear();
	cout << ans << endl;
}
void solve() {
	int i;
	memset(deg, 0, sizeof(deg));
	for(i = 1; i <= n; i++) e[i].clear();
	
	n = inp(); m = inp(); K = inp();
	for(i = 1; i <= m; i++) {
		int u = inp(), v = inp();
		::u[i] = u; ::v[i] = v;
		deg[u]++;
		deg[v]++;
		e[u].push_back(v);
		e[v].push_back(u);
		if(n <= 10) eG[u].insert(v), eG[v].insert(u);
	}
	if(n <= 10) force();
	else {
		if(K == 1) run_1();
		if(K == 2) run_2();
		if(K == 3) run_3();
	} 
}
 
int main() {
	int T = inp();
	while(T--) solve();
	return 0;
}
