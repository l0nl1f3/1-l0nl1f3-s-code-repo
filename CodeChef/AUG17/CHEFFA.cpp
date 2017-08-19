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

const int MaxN = 66, MaxSp = MaxN << 1;
const int P = 1000000007; 
int n, a[MaxN];
int f[MaxSp][MaxSp][MaxSp];

int main() {
	int i, j, k, T = inp();
	while(T--){
		n = inp();
		memset(f, 0, sizeof(f));
		memset(a, 0, sizeof(a));
		for(i = 1; i <= n; i++) a[i] = inp();
		
		int m = MaxSp - 1;
		f[0][0][0] = 1;
		for(i = 0; i < m; i++)
			for(j = 0; j <= m; j++)
				for(k = 0; k <= m; k++)
					for(int l = 0; l <= a[i + 1] + k - j; l++)
						f[i + 1][l][j] = (f[i + 1][l][j] + f[i][j][k]) % P;
		int ans = 0;
		for(i = 0; i < m; i++)
			for(j = 0; j < m; j++)
				ans = (ans + f[m][i][j]) % P;
		cout << ans << endl;					 
	}
	return 0;
}


