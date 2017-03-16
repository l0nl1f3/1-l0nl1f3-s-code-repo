#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
const int inf = 2e9 + 9;
const int MaxN = 1e5 + 5;
int n, a[MaxN][17], preMin[MaxN], sufMax[MaxN], que[MaxN], ql, qr, pow[17], log[MaxN];
ll m, g[MaxN], b[MaxN];
inline int Max(int l, int r) {
	int k = log[r - l + 1];
	return max(a[l][k], a[r - pow[k] + 1][k]);
}
ll calc(int pre, int i) {
	return g[pre] + Max(pre + 1, i);
}
bool check(ll x) {
	g[0] = 0; que[ql = qr = 0] = 0;
	for (int i = 1; i <= n; ++i) {
		while (ql <= qr && b[i] - b[que[ql]] > x) ++ql;
		if (ql > qr) return false;
		while (ql < qr && calc(que[ql], i) >= calc(que[ql + 1], i)) ++ql;
		g[i] = calc(que[ql], i);
		if (preMin[i] > sufMax[i + 1]) que[++qr] = i;
	}
	return g[n] <= m;
}
void RMQ() {
	for (int k = 1; k <= 16; ++k)
		for (int i = 1; i <= n; ++i)
			if (i + pow[k] - 1 <= n) 
				a[i][k] = max(a[i][k - 1], a[i + pow[k - 1]][k - 1]);
}
int main() {
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	scanf("%d%I64d", &n, &m);
	log[0] = -1; for (int i = 1; i <= n; ++i) log[i] = log[i >> 1] + 1;
	pow[0] = 1;  for (int i = 1; i <= 16; ++i) pow[i] = pow[i - 1] << 1;
	for (int i = 1; i <= n; ++i) scanf("%d%I64d", &a[i][0], &b[i]);
	RMQ();
	
	preMin[0] = inf + 1; for (int i = 1; i <= n; ++i) preMin[i] = min(preMin[i - 1], (int)b[i]);
	sufMax[n + 1] = 0;   for (int i = n; i >= 1; --i) sufMax[i] = max(sufMax[i + 1], a[i][0]);
	for (int i = 1; i <= n; ++i) b[i] += b[i - 1];
	
	ll l = 1, r = 2e14, res;
	while (l <= r) {
		ll mid = l + r >> 1;
		if (check(mid)) res = mid, r = mid - 1;
		else l = mid + 1;
	}
	
	printf("%I64d\n", res);

}