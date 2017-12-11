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

const int MaxN = 123;
int T, n, m; char s[MaxN][MaxN];
int main() {
	int i, j;
	T = read();
	while(T--) {
		n = read(); m = read();
		int ans1 = 0, ans2 = 0;
		for(i = 1; i <= n; i++) {
			scanf("%s", s[i] + 1);
			for(j = 1; j <= m; j++) {
				int o = (s[i][j] == 'G');
				int p = (i + j) & 1;
				if(o != p)
					ans1 += p ? 5 : 3;
			    else {
			    	p = !p;
			    	ans2 += p ? 5 : 3; 
				}
			}
		}
		cout << min(ans1, ans2) << endl;
	}
	return 0;
}

