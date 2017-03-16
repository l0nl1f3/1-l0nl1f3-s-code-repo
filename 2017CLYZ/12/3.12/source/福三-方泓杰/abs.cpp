# include <stdio.h>
# include <string.h>
# include <algorithm>
// # include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
const int M = 10 + 10;
const int mod = 998244353;
int inv2;

# define FO_OPEN 1
# define RG register
# define ST static

namespace CommonMath {
	inline int gmin(int a, int b) {
		return a<b?a:b;
	}
	inline int gmax(int a, int b) {
		return a>b?a:b;
	}
	inline int gabs(int a) {
		return a>0?a:-a;
	}
}

using namespace CommonMath;

inline int pwr(int x, int y) {
	int ret = 1;
	while(y) {
		if(y&1) ret = 1ll * ret * x % mod;
		x = 1ll * x * x % mod;
		y >>= 1;
	}
	return ret;
}

int n;
int l[M], r[M];

int main() {
	FO_OPEN ? freopen("abs.in", "r", stdin), freopen("abs.out", "w", stdout) : 0;
	scanf("%d", &n);
	for (int i=1; i<=n; ++i) 
		scanf("%d%d", l+i, r+i);
	inv2 = pwr(2, mod-2);
	if(n == 1) {
		if(l[1]*r[1] >= 0) {
			int ans;
			ans = 1ll*inv2*gabs(l[1]+r[1]) % mod;
			printf("%d\n", ans);
		} else {
			int al = -l[1], bl = r[1], tl = al + bl, tln = pwr(tl, mod-2);
			int as = 1ll * al * tln % mod,
				bs = 1ll * bl * tln % mod;
			int at = 1ll * al * inv2 % mod,
				bt = 1ll * bl * inv2 % mod;
			int ans = 1ll * at * as % mod + 1ll * bt * bs % mod;
			ans = ans % mod;
			printf("%d\n", ans);
		}
	}
	return 0;
}




