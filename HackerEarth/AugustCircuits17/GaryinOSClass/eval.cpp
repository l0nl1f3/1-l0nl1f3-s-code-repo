//#include <bits/stdc++.h>
#include "testlib.h"

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

const int MaxN = 1001234;

int n, m, K, a[MaxN], b[MaxN], c[MaxN]; 
int main(int argc, char * argv[]) {
	int i;
	registerTestlibCmd(argc, argv);
	
	n = inf.readInt(1, 100000, "N");
	m = inf.readInt(1, 1000000, "M");
	for(i = 1; i <= n; i++) {
		a[i] = inf.readInt(1, 1000000, "a[i]");
	}
	
	K = ouf.readInt(1, m, "K");
	
	LL F = 0; int used = 0;
	for(i = 1; i <= m/K; i++) {
		int p = ouf.readInt(0, n, "p");
		used += p; 
		LL v = 0; 
		while(p--) {
			int x = ouf.readInt(1, n, "x");
			if(b[x]) quitf(_wa, "duplicate saved");
			v += a[x]; b[x] = 1;
			if(v > K) quitf(_wa, "out bounded");
		}
		F += K - v;
	}
	
	string s = ""; LL sc = (LL) K * K + F * F;
	
	while(sc) s += ('0' + sc % 10), sc /= 10; 
	
	
	string t = "";
	while(used) t += ('0' + used % 10), used /= 10;
	
	reverse(s.begin(), s.end());
	
	s += " and used ";
	
	reverse(t.begin(), t.end());
	s += t;
	
	quitf(_ok, s.c_str());
 	return 0;
}



