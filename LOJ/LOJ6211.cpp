#include <bits/stdc++.h>

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

const int MaxN = 8000005;

bitset <MaxN> a, b; char s[MaxN];

int main() {
	int i;
	while(scanf("%s", s) != EOF) {
		int n = strlen(s);
		for(i = 0; i < n; i++) a[i] = (s[i] - '0');
		int l = 0, r = n - 1;
		while(l < r) {
			for(i = 0; (1 << i) < r - l + 1; i++); i--;
			b = a ^ (a >> (1 << i));
			if(b._Find_first() >= (n - l - (1 << i))) 
				r = l + (1 << i) - 1;
			else 
				l = l + (1 << i), a = b;
		}
		
		if(l >= n - 1) puts("-1"); else printf("%d\n", l + 1); 
	}
	return 0;
}



