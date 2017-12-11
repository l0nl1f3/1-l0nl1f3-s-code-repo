#include <bits/stdc++.h>

#define fir first
#define sec second
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

#define Pii pair<int, int> 
#define P4 pair<Pii, Pii>
#define x1 fir.fir
#define y1 fir.sec
#define x2 sec.fir
#define y2 sec.sec
#define MP(x, y, z, w) make_pair(make_pair(x, y), make_pair(z, w))

int a, b, n, sga, sgb;
vector<P4> ans;

void solve() {
	sga = a > 0; if(!sga) sga = -1, a = -a;
	sgb = b > 0; if(!sgb) sgb = -1, b = -b;
	ans.clear();
	int x, y, rev; x = y = rev = 0;
	while(1) {
		if(a >= x + n && b >= y + n) {
			ans.emplace_back(MP(x + n - 1, y + n - 1, x, y));
			x += n - 1; y += n - 1;
			if(a > x + n - 1 && a - x > b - y) 
				++x, rev = 1;
			else
				++y, rev = 0;
			continue; 
		}
		if(a >= x + n) {
			ans.emplace_back(MP(x + n - 1, y + n - 1, x, y));
			x +=  n; rev = 1; continue;
		}
		if(b >= y + n) {
			ans.emplace_back(MP(x, y, x + n - 1, y + n - 1));
			y += n; rev = 0; continue;
		}
		if(!rev) 
			ans.emplace_back(MP(a, y + n - 1, a - n + 1, y));
		else
			ans.emplace_back(MP(x, b - n + 1, x + n -1, b));
		break;	
	}
	printf("%d\n", ans.size());
	for(auto x : ans) 
		printf("%d %d %d %d\n", x.x1 * sga, x.y1 * sgb, x.x2 * sga, x.y2 * sgb);
}
int main() {
	int T;
	cin >> T;
	while(T--) {
		cin >> a >> b >> n;
		solve();
	}
	return 0;
}

