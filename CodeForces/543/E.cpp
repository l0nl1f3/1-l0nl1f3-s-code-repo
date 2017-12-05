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

const int MaxN = 201234;

int n, m, q; pair<int, int> p[MaxN]; 
 
int rot[MaxN];
void modify(int &p, int q, int l, int r, int a, int b) {
	
}

int query(int p, int l, int r, int a, int b) {
	
}

int main() {
	int i;
	n = read(); m = read(); 
	for(i = 1; i <= n; i++) p[i] = make_pair(-read(), i);
	sort(p + 1, p + n + 1);
	for(i = 1; i <= n; i++) {
		int t = p[i].sec;
		int l = max(1, t - m + 1);
		int r = min(n - m + 1, t);
		modify(rot[i], rot[i - 1], 1, n - m + 1, l, r);
	}
	q = read();
	
	int Lans = 0;
	while(q--) {
		int l = read(), r = read(), K = read() ^ Lans;
		printf("%d\n", Lans = m - query(rot[lower_bound(p + 1, p + n + 1, make_pair(-K, 0)) - p - 1], 1, n - m + 1, l, r)); 
	} 
	return 0;
}



