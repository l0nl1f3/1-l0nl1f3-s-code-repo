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

const int MaxH = 4567, U = 3010;

int n, a[MaxH][MaxH], b[MaxH][MaxH];

int main() {
	int i, j;
	n = read();
	for(i = 1; i <= n; i++) {
		char s[3]; scanf("%s", s); char c = s[0];
		int x = read(), y = read(), A = read();
		x += (U >> 1); y += (U >> 1); x -= (A >> 1);
		if(c == 'A') 
			 cmax(a[x][y - (A >> 1)], A);
		else 
			cmax(b[x][y], A);
	}
	int ans = 0;
	for(i = 1; i < MaxH - 1; i++)
		for(j = 1; j < MaxH - 1; j++) {
			cmax(a[i][j], max(a[i - 1][j] - 1, max(a[i - 1][j - 1] - 1, a[i][j - 1] - 1)));
			cmax(b[i][j], max(b[i - 1][j] - 1, max(b[i - 1][j - 1] - 2, b[i - 1][j + 1] - 2)));
			if(a[i][j - 1] > 0) ans += 4;
			else 
				ans += (b[i][j - 1] > 0) + (b[i][j] > 0) + (b[i][j - 1] > 1 || b[i][j] > 1) + (b	[i - 1][j - 1] > 1 || b[i - 1][j] > 1);
		}
	printf("%.2lf\n", ans / 4.0);
 	return 0;
}

