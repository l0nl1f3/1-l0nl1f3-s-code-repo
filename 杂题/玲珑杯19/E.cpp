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
const int MaxN = 1234;
int n, a[MaxN], b[MaxN], O[MaxN];

int op(int a, int b, char op){
	if(b == 2) return a;
	if(op == 1) return a & b;
	if(op == 2) return a | b;
	if(op == 3) return a ^ b;
	return a;
}
const int MaxH = 20;
double f[MaxN][MaxH], p[MaxN];

int main() {
	int i, j;
	
	n = inp();
	for(i = 1; i <= n + 1; i++)	a[i] = inp();
	for(i = 2; i <= n + 1; i++) {
		char ch = getchar();
		while(ch != '&' && ch != '|' && ch != '^') ch = getchar();
		if(ch == '&') O[i] = 1;
		if(ch == '|') O[i] = 2;
		if(ch == '^') O[i] = 3; 
	}
	for(i = 2; i <= n + 1; i++) scanf("%lf", p + i);
	
	double ans = 0.0;
	for(i = 1; i <= n + 1; i++){
		for(j = 0; j < 20; j++){
			int o = (a[i] >> j) & 1;
			f[i][j] = f[i - 1][j] * p[i] + 
			op(o, 0, O[i]) * (1 - f[i - 1][j]) * (1 - p[i]) + 
			op(o, 1, O[i]) * f[i - 1][j] * (1 - p[i]);
		}
	}
	for(i = 0; i < 20; i++) ans += (1 << i) * f[n + 1][i];
	printf("%.6lf\n", ans);
	return 0;
}



