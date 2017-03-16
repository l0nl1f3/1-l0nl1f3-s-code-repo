#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <map>
#include <vector>
using namespace std;
 
typedef long long ll;
 
inline int read() {
	int r = 0;
	static char c;
	do c = getchar(); while (c < '0' || c > '9');
	while (c >= '0' && c <= '9') r = r * 10 + (int)(c - '0'), c = getchar();
	return r;
}
 
const int mod = (int)1e9 + 7;
 
#define N 100000
#define SQRTN 1300
int n, m, a[N + 1], cnt[N + 1], T;
bool big[N + 1];
 
inline int node(int x) {
	static map <int, int> h;
	static int cnt = 0;
	if (h.find(x) != h.end()) return h[x];
	return h[x] = ++cnt;
}
 
inline int rectify(int x) {
	if (x < 0) x += mod;
	if (x >= mod) x -= mod;
	return x;
}
 
inline void add(int &x, int y) {
	x += y;
	if (x >= mod) x -= mod;
}
 
namespace Small {
	vector <int> pos[N + 1];
	int cnt[N + 1];
	
	int arr[N + 1];
	
	inline void modify(int x, int d) {
		d = rectify(d);
		for (; x > 0; x -= x & -x)
			add(arr[x], d);
	}
	
	inline void modify(int l, int r, int d) {
		if (l > r) return ;
		modify(r, d);
		modify(l - 1, -d);
	}
	
	inline int query(int x) {
		int r = 0;
		for (; x <= n; x += x & -x)
			add(r, arr[x]);
		return r;
	}
	
	int main() {
		int ret = 0;
		for (int i = 1; i <= n; ++i) {
			if (big[a[i]]) continue;
			int cur = 0;
			++cnt[a[i]], pos[a[i]].push_back(i);
			for (int j = pos[a[i]].size() - 2; j >= 0; --j) {
				int l = pos[a[i]][j], r = pos[a[i]][j + 1];
				int x = cnt[a[i]] - j - 1;
				modify(l + 1, r - 1, x * (cnt[a[i]] - x) - (x - 1) * (cnt[a[i]] - x));
				add(cur, query(l));
			}
			add(ret, cur);
		}
		return ret;
	}
}
 
namespace Big {
	int cnt[SQRTN + 1], col[N + 1], rev[N + 1], left[SQRTN + 1][SQRTN + 1];
	
	int main() {
		int tot = 0, ret = 0;
		for (int i = 1; i <= m; ++i)
			if (big[i]) col[i] = ++tot, rev[tot] = i;
		for (int i = 1; i <= n; ++i) {
			if (!big[a[i]]) continue;
			for (int j = 1; j <= tot; ++j) {
				if (j == col[a[i]]) continue;
				int right = ::cnt[rev[j]] - cnt[j];
				ret = (ret + (ll)left[j][col[a[i]]] * right) % mod;
			}
			++cnt[col[a[i]]];
			for (int j = 1; j <= tot; ++j)
				add(left[col[a[i]]][j], cnt[j]);
		}
		return ret;
	}
}
 
namespace BigSmall {	
	vector <int> pos[N + 1];
	int seq[N + 1], b[N + 1], sum[N + 1], pre[N + 1];
	
	int main() {
		int ret = 0;
		for (int i = 1; i <= n; ++i)
			pos[a[i]].push_back(i);
		for (int x = 1; x <= m; ++x) {
			if (!big[x]) continue;
			for (int i = 1; i <= n; ++i)
				seq[i] = seq[i - 1] + (a[i] == x);
			for (int y = 1; y <= m; ++y) {
				if (big[y]) continue;
				int len = 0, last = 0;
				for (int j = 0; j < pos[y].size(); ++j) {
					b[++len] = seq[pos[y][j]] - seq[last];
					last = pos[y][j];
				}
				b[++len] = seq[n] - seq[last];
				for (int i = 1; i <= len; ++i) {
					sum[i] = sum[i - 1], add(sum[i], b[i]);
					pre[i] = (pre[i - 1] + (ll)i * b[i]) % mod;
				}
				for (int i = 2; i < len; ++i) {
					int left = ((ll)sum[i - 1] * i - pre[i - 1]) % mod;
					int right = rectify((pre[len] - pre[i] - (ll)i * (sum[len] - sum[i])) % mod);
					ret = (ret + ((ll)left * (len - i) + (ll)right * (i - 1)) % mod * b[i]) % mod;
				}
			}
		}
		return ret;
	}
}
 
int main(int argc, char *argv[]) {
	freopen("arc.in","r",stdin);	
	n = read();
	for (int i = 1, x; i <= n; ++i)
		a[i] = node(read()), ++cnt[a[i]];
	T = min(n, (int)(sqrt((double)n / log2((double)n)) * 1.7) + 1);
	m = *max_element(a + 1, a + n + 1);
	for (int i = 1; i <= m; ++i)
		big[i] = cnt[a[i]]>T;
	
	int ans = Small::main();
	cerr<<ans<<endl;
	add(ans, Big::main());
	cerr<<ans<<endl;
	add(ans, BigSmall::main());
	printf("%d\n", ans);
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
 

