#include <bits/stdc++.h>

#define fir first
#define sec second
using namespace std;
typedef long long LL;
typedef double db;

template <typename T> inline bool cmin(T & a, const T & b) { return a > b ? a = b, 1 : 0;}
template <typename T> inline bool cmax(T & a, const T & b) { return a < b ? a = b, 1 : 0;}
int inp() {
	int x = 0, f = 1;char ch;
	for(ch = getchar(); !isdigit(ch); ch = getchar())
		if(ch == '-') f = -1;
	for(; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	return x * f;
}

const int MaxN = 70;
db X; int n, m;

typedef db mat[MaxN][MaxN];
mat a, b, c, t;

void mul(mat a, mat b, mat c){
	int i, j, k;
	for(i = 0; i < (n << 1); i++)
		for(j = 0; j < (n << 1); j++){
			t[i][j] = 0;
			for(k = 0; k < (n << 1); k++)
				t[i][j] = (t[i][j] + a[i][k] * b[k][j]);
		}
	for(i = 0; i < (n << 1); i++)
		for(j = 0; j < (n << 1); j++)
			c[i][j] = t[i][j];
}
void exp(mat a, int N){
	int i, j, k;
	for(i = 0; i < (n << 1); i++)
		for(j = 0; j < (n << 1); j++)
			c[i][j] = (i == j);
	for(; N; N >>= 1){
		if(N & 1)
			mul(c, a, c);
		mul(a, a, a);
	} 
}

int main() {
	int i, j, k, T = inp();
	
	while(T--){
		cin >> n >> m >> X;
		double x = sin(X), y = cos(X);
		if(n > m) {
			puts("0"); 
			continue;
		}
		for(i = 0; i < (n << 1); i++)
			for(j = 0; j < (n << 1); j++)
				b[i][j] = 0;
		for(i = 0; i < (n << 1); i += 2){
			b[i][i] = 2 * y;
			b[i][i + 1] = -1;
			b[i][i + 2] = x;
			b[i + 1][i] = 1;
		}
		
		exp(b, m - 1);
		
		db ans = x * c[0][(n - 1)  << 1];
		
		printf("%.20lf\n", ans);
	}
	return 0;
}



