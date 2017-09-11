#include <bits/stdc++.h>

#define fir first
#define sec second
using namespace std;
typedef long long LL;
typedef unsigned long long u64;

template <typename T> inline bool cmin(T & a, const T & b) { return a > b ? a = b, 1 : 0;}
template <typename T> inline bool cmax(T & a, const T & b) { return a < b ? a = b, 1 : 0;}
int inp() {
	int x = 0, f = 1;char ch;
	for(ch = getchar(); !isdigit(ch); ch = getchar())
		if(ch == '-') f = -1;
	for(; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	return x * f;
}

const int MaxN = 123;
int T, n; char ch[MaxN][MaxN];

void solve() {
	int i, j;
	n = inp(); int cnt = 0;
	for(i = 1; i <= n; i++) {
		scanf("%s", ch[i] + 1);
		for(j = 1; j <= n; j++) {
			int c = ch[i][j] - '0';
			cnt += c;
		}
	}
	
	cout << max(cnt - 95, 0) << endl;
	cnt = max(cnt - 95, 0);
	if(!cnt) return;
	for(i = 1; i <= n; i++) {
		for(j = 1; j <= n; j++) {
			int c = ch[i][j] - '0';
			cnt -= c;
			if(c) {
				printf("%d %d %d %d %d %d %d %d %d\n", 0, 1, 0, 1, 0, 1, j, i, i);
			}
			if(cnt == 0) return;
		}
	}
}
int main() {
	int T = inp();
	while(T--)	solve();
	return 0;
}



