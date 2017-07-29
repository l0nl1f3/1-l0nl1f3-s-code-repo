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
const int MaxN = 123;
double a[MaxN];int n;
int main() {
	int i;
	while(scanf("%d", &n) != EOF){
		int a = n - 1, b = 1, c = 0, d = 0;
		for(i = 1; i <= 10; i++){
			b *= 10; c ++;
			if(a > b - c) d = c;
		}
		cout << n + d << endl; 
	}
	return 0;
}



