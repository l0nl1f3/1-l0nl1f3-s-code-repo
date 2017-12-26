#include <bits/stdc++.h>

#define fir first
#define sec second
#define MP make_pair
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

const int MaxN = 65;

int n; u64 b[MaxN], c;

void bitprint(u64 x) {
	for(int i = 0; i < n; i++) 
		cout << (x >> i & 1);	
}

namespace small {
	vector<pair<u64, u64> > a, b;
	int main() {
		int mid = n >> 1, i, j;
		for(i = 0; i < (1 << mid); i++) {
			u64 s = 0;
			for(j = 0; j < mid; j++) if(i >> j & 1) s += :: b[j];
			a.PB(MP(s, i));
		}
		mid = n - mid;
		for(i = 0; i < (1 << mid); i++) {
			u64 s = c;
			for(j = 0; j < mid; j++) if(i >> j & 1) s += (u64) -::b[j + (n >> 1)];
			b.PB(MP(s, i));
		}		
		sort(a.begin(), a.end());
		sort(b.begin(), b.end());
		for(i = j = 0; i < a.size(); i++) {
			for(; j < b.size() && b[j].fir < a[i].fir; j++);
			if(j < b.size() && b[j].fir == a[i].fir) {
				bitprint(a[i].sec | b[j].sec << (n >> 1));
				return 0;
			}
		}
	}
}

namespace big {
	u64 inv(u64 x) {
		u64 res = 0;
		for(int i = 0; i < 64; i++) {
			u64 j = (res | (1ull << i)) * x;
			if(i < 63) j &= (1ull << i + 1) - 1;
			if(j == 1) res |= (1ull << i);
		}
		return res;
	}
	u64 a[MaxN];
	int main() {
		int z = 0;
		for(u64 t = b[0]; ~t & 1; ++z, t >>= 1);
		u64 iv = inv(b[0] >> z);
		for(int i =  1; i < (1 << 65 - n - z); i++)
			for(int j = 0; j < 1 << z; j++) {
				u64 r = iv * i + (u64(j) << 64 - z);
				u64 C = c * r, ans = 0;
				for(int k = 0; k < n; k++) a[k] = b[k] * r;
				for(int k = n - 1; ~k; k--)
					if(C >= a[k]) C -= a[k], ans |= (1ull << k);
				if(!C) {
					bitprint(ans); return 0;
				}
			}
	}
}
int main() {
	int i;
	n = read();
	for(i = 0; i < n; i++) cin >> b[i]; cin >> c;
	if(n <= 44)
		small :: main();
	else 
		big :: main();
	return 0;
}
close
