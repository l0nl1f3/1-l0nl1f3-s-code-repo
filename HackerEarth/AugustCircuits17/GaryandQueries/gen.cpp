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

int n, q;
int main() {
	int i;
	freopen("input.txt", "w", stdout);
	int n = 5e5;
	int q = 5e5;
	printf("%d %d\n", n, q);
	for(i = 1; i <= n; i++) printf("%d ", (int)5e5 - rand() % 233);
	for(i = 1; i <= q; i++) {
		int op = 1 + (i & 1);
		int x = n - rand() % 233; 
		printf("%d %d", op, x);
		if(op == 1) printf(" %d", (int)5e5 - rand() % 233);
		puts("");
	}
	return 0;
}



