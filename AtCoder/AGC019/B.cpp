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

const int MaxN = 201234;
char a[MaxN]; int n;
int b[MaxN];
int main() {
	int i;
	scanf("%s", a + 1); n = strlen(a + 1); 
	LL ans = (LL) n * (n + 1) / 2;
	
	for(i = 1; i <= n; i++) 
		b[a[i] - 'a']++;
	for(i = 0; i < 26; i++) ans -= (LL) b[i] * (b[i] + 1)/2;
	cout << ans + 1;
	return 0;
}



