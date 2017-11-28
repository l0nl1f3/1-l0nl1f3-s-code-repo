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
 
const int MaxN = 101234, MaxL = 21;
 
int n, a[MaxN]; LL K;
 
struct Trie {
	int cnt[MaxN * MaxL * 16];
	void clear() {
		memset(cnt, 0, sizeof(cnt));
	}
	void insert(int x) {
		int p = 1;
		for(int i = MaxL - 1; ~i; i--)
			cnt[p = (p << 1 | (x >> i & 1))]++;
	}
	
	int query(int x, int y) { // count x ^ a[i] >= y 
		int p = 1; int ans = 0;
		for(int i = MaxL - 1; ~i; i--) {
			int a = x >> i & 1;
			int b = y >> i & 1;
			if(a > b) ans += cnt[p << 1];
			if(!a && !b) ans += cnt[p << 1 | 1];
			p = p << 1 | (a ^ b);
		}
		return ans + cnt[p];
	}
}T;
 
LL chk(int x) {
	int i, j; LL t = 0;
	/*
	for(i = 0; i <= n; i++)
		for(j = i + 1; j <= n; j++)
			if((a[i] ^ a[j]) >= x) t++;
	return t;
	*/
	 
	T.clear(); T.insert(0);
	for(i = 1; i <= n; i++) {
		t += T.query(a[i], x);
		T.insert(a[i]);
	}
	return t;
}
 
int main() {
	int i;
	n = read(); cin >> K;
	for(i = 1; i <= n; i++) a[i] = a[i - 1] ^ read();
	int L = 0, R = (1 << 20) - 1, ans = 0;
	while(L <= R) {
		int mid = L + R >> 1;
		if(chk(mid) >= K) 
			ans = mid, L = mid + 1;
		else
			R = mid - 1;
	}	
	cout << ans;
	
	return 0;
}
