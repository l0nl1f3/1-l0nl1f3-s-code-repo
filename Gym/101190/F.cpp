#include <bits/stdc++.h>

#define fir first
#define sec second
#define MP make_pair

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

const int MaxN = 1001234;

int n; char s[MaxN]; double g[2], f[MaxN];

int main() {
    freopen("foreign.in", "r", stdin);
    freopen("foreign.out", "w", stdout);
    
	int i, j, k;
	scanf("%s", s + 1); n = strlen(s + 1);
	for(i = n; i; i--) {
		int c = s[i] == 'C'; g[c ^ 1] += (n - i + 1);
		f[i] = (f[i + 1] + g[c]) / (n - i + 1);
		f[i] += f[i + 1];
	} 
	printf("%.10lf\n", f[1] - f[2]);
	return 0;
}

