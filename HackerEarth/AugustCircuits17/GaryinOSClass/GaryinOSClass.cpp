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

const int MaxN = 101234, MaxM = 1001234;
int n, m, K, a[MaxN];

namespace io {
	void output(int K, vector <int> v[]) {
		printf("%d\n", K);
		for(int i = 1; i <= m/K; i++, puts("")) {
			printf("%d ", v[i].size());
			for(auto atom : v[i])
				printf("%d ", atom);
		}
	}
}

vector <int> ans[MaxM];

namespace fool {
	int p[MaxN];
	int main() {
		K = m;
		int s = 0;
		
		for(int i = 1; i <= n; i++) p[i] = i;
		sort(p + 1, p + n + 1, [&] (int x, int y) {return a[x] < a[y]; });
		for(int i = 1; i <= n; i++) 
			if((s += a[p[i]]) <= m)
				ans[1].emplace_back(p[i]);
			else 
				break;
		io :: output(K, ans);
	}	
}

namespace Greedy {
	
	int p[MaxN], b[MaxN];
	LL s[MaxN];
	int emmm(int K, int op = 0) {
		int l, r, pc = 0;
		int N = upper_bound(b + 1, b + n + 1, K) - b - 1;
		int F = 0;
		
		for(l = 1, r = 0; l <= N; l = r + 1) {
			r = upper_bound(s + l, s + n + 1, s[l - 1] + K) - s - 1;
			F += K -(s[r] - s[l - 1]); 
			++pc;
			
			if(op) {
				for(int i = l; i <= r; i++)
					ans[pc].emplace_back(p[i]);
			}
			
			if(pc >= (m/K)) break;
		}
		
		F += K * (m/K - pc);
		
		return F;
	}
	int main() {
		int i;
		for(i = 1; i <= n; i++) p[i] = i;
		
		sort(p + 1, p + n + 1, [&] (int x, int y) {return a[x] < a[y]; });
		for(i = 1; i <= n; i++) b[i] = a[p[i]];
		for(i = 1; i <= n; i++) s[i] = s[i - 1] + b[i];
		
		int ansK = 0; LL ansF = LONG_LONG_MAX;
		for(K = a[p[1]]; K <= m; K++) {
			int F = emmm(K);
			if(cmin(ansF, (LL)K * K + (LL)F * F))
				ansK = K; 
		}
		
		emmm(ansK, 1);
		
		io :: output(ansK, ans);
//		}
		return 0;
	}
}

namespace Greedy2 {
	int rem[MaxM], p[MaxN], b[MaxN];
	
	struct info {
		int x;
		bool operator < (const info &b) const {
			return rem[this -> x] < rem[b.x];
		}
		info() {}
		info(int x) : x(x) {}
	};
		
	priority_queue<info> pq;
	
	int emmm(int K, int op = 0) {
		int i, j;
		for(i = 1; i <= m/K; i++) pq.push(info(i)), rem[i] = K;
		
		for(j = 1; j <= n; j++) {
			i = p[j];
			info y = pq.top(); 
			
			if(rem[y.x] < a[i]) continue;
			
			pq.pop();
			rem[y.x] -= a[i];
			if(op) ans[y.x].emplace_back(i);
			pq.push(y);
		}
		
		while(!pq.empty()) pq.pop();
		int F = 0;
		for(i = 1; i <= m/K; i++) F += rem[i];
		return F;
	}
	
	struct _info {
		int x, v;
		bool operator < (const _info &b) const {
			return this -> v < b.v || (this -> v == b.v && this -> x < b.x); 
		}
		_info() {}
		_info(int x, int v) : x(x), v(v) {}
	};
	
	set <_info> s;
	
	int ansK = 0; LL ansF = LONG_LONG_MAX;
	
	int pq_greedy() {
		for(K = *min_element(a + 1, a + n + 1); K <= m; K++) {
			if(clock() / (double)CLOCKS_PER_SEC >= 4.70) {
				break; 
			} 
			int kt = emmm(K);
			if(cmin(ansF, (LL) kt * kt + (LL) K * K))
				ansK = K;
		}		
		emmm(ansK, 1);
	}
	
	int vis[MaxN];
	void opt(vector<int> & vec) {
		sort(vec.begin(), vec.end(), [&] (int x, int y) {return a[x] > a[y]; });
		int mn = vec.size() - 1, g = ansK;
		for(auto x : vec) g -= a[x]; g += a[vec[mn]];
		for(set <_info> :: iterator t = s.begin(); t != s.end(); t++) {
			set <_info> :: iterator z = s.lower_bound(_info(0, g - t -> v)); 
			if(z != s.begin() && t -> v + z -> v >= a[vec[mn]]) {
				--z;
				vec.pop_back();
				vec.emplace_back(z -> x);
				vec.emplace_back(t -> x);
				s.erase(t); s.erase(z);
				return;
			}
		}
			
	}
	
	int main() {
		int i, j;
		for(i = 1; i <= n; i++) p[i] = i;
		sort(p + 1, p + n + 1, [&] (int x, int y) {return a[x] > a[y]; });
		
		pq_greedy();	
		
		for(i = 1; i <= m/ansK; i++) for(auto x : ans[i]) vis[x] = 1;
		for(i = 1; i <= n; i++) if(!vis[i]) s.insert(_info(i, a[i]));
		
		if((*max_element(a + 1, a + n + 1)) > 1000)
			for(i = 1; i <= m/ansK; i++) 
				opt(ans[i]);
		// emmm(ansK, 1);
		io :: output(ansK, ans);
	}
}


int main() {
	int i;
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	
	n = inp(); m = inp();
	for(i = 1; i <= n; i++) a[i] = inp();
	
	if(*max_element(a + 1, a + n + 1) <= 10)
		Greedy :: main();
	else {
		Greedy2 :: main();
	}
	
	return 0;
}



