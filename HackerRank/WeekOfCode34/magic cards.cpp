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
const int MaxN = 1001234, MaxL = 22;

int n, m, q; LL f[MaxN][MaxL], Lans;
vector<int> x[MaxN]; LL chk[MaxN];
LL query(int l, int r){
	int i, j, k = r - l + 1;
	for(i = 0; i < (1 << k); i++) chk[i] = 0;
	for(i = 1; i <= m; i++){
		int s = 0;
		for(j = l; j <= r; j++)
			s = s << 1 | x[j][i];
		chk[s] += (LL) i * i;	
	}
	LL ans = 0;
	for(i = 0; i < (1 << k); i++) 
		cmax(ans, Lans - chk[i]);
	return ans;
}
int main() {
	int i, j, k;
	n = inp(); m = inp(); q = inp();
	for(i = 1; i <= n; i++){
		x[i].resize(m + 1);
		for(j = inp(); j; j --)
			x[i][inp()] = 1;
	}
	
	int L = floor(log(m)/log(2));
	for(i = 1; i <= m; i++) Lans += (LL) i * i; 
	
	for(i = 1; i<= n; i++)
		for(j = 1; j <= L && i + j - 1 <= n; j++){
			f[i][j] = query(i, i + j - 1);
		}
		
	for(i = 1; i <= q; i++){
		int l = inp(), r = inp();
		if(r - l + 1 > L) printf("%lld\n", Lans);
		else 
			printf("%lld\n", f[l][r - l + 1]);
	}
	return 0;
}



