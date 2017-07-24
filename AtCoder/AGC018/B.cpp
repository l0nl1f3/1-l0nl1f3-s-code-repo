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
const int MaxN = 400;
int n, m, a[MaxN][MaxN], l[MaxN], del[MaxN], cnt[MaxN]; 
int main() {
	int i, j;
	n = inp(); m = inp();
	for(i = 1; i <= n; i++)
		for(j = 1; j <= m; j++)
			a[i][j] = inp();
	
	for(i = 1; i <= n; i++) l[i] = 1;
	
	int ans = ~0U >> 1;
	for(i = 1; i <= m; i++) {
		memset(cnt, 0, sizeof(cnt));
		for(j = 1; j <= n; j++) cnt[a[j][l[j]]]++;
		int res = 0, k = 0;
		for(j = 1; j <= m; j++) if(cnt[j] > cnt[k]) k = j;
		cmin(ans, cnt[k]); del[k] = 1;
		for(j = 1; j <= n; j++){
			while(del[a[j][l[j]]]) ++l[j];	
			if(l[j] > m) break;
		}
		if(l[j] > m) break;
	}
	cout << ans << endl;
	return 0;
}



