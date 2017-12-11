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

const int MaxN = 101234;

int T, n, a[MaxN], b[MaxN], ps[MaxN][2];
vector<int> t1, t2;
int main() {
	int i;
	T = read();
	while(T--) {
		n = read(); assert(n);
		memset(b, 0, sizeof(b));
		memset(ps, 0, sizeof(ps));
		for(i = 1; i <= n; i++) {
			a[i] = read();
			if(!ps[a[i]][0]) ps[a[i]][0] = i;
			else ps[a[i]][1] = i;
		}
		if(n > 2) {
			for(i = 1; i <= 100000; i++) 
				if(ps[i][1])
					t2.push_back(i);
				else if(ps[i][0])
					t1.push_back(i);
			vector<int> t; 
			for(i = 0; i < t2.size(); i++) t.push_back(ps[t2[i]][0]), t.push_back(ps[t2[i]][1]);
			for(i = 0; i < t1.size(); i++) t.push_back(ps[t1[i]][0]);
			for(i = 0; i < t.size(); i++)
				b[t[i]] = a[t[(i + 2) % t.size()]];
		}else 
			if(n > 1) 
				b[1] = a[2], b[2] = a[1];
			else
				b[1] = a[1];
		int ham = 0;
		for(i = 1; i <= n; i++) ham += a[i] != b[i];
		printf("%d\n", ham);
		for(i = 1; i <= n; i++) printf("%d ", b[i]); puts("");
		t1.clear(); t2.clear();
	}
	return 0;
}

