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
const int MaxN = 101234;
char ch[MaxN]; int b[MaxN];

int main() {
	int i, T = inp();
	while(T--) {
		memset(b, 0, sizeof(b));
		scanf("%s", ch + 1); int n = strlen(ch + 1);
		for(i = 1; i <= n; i++) ++b[ch[i] - '0'];
		
		for(i = 'A'; i <= 'Z'; i++) {
			int p = i % 10, q = i/10;
			if(p != q) if(b[p] && b[q]) putchar(i);
			if(p == q) if(b[p] > 1) putchar(i);
		} 
		puts("");
	}
	return 0;
}



