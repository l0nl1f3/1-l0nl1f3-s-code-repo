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

const int MaxN = 101234;
int n, d; LL a[MaxN], ans;

int main() {
	int i, j, T = inp();
	while(T--) {
		n = inp(); d = inp(); LL sum = 0; 
		for(i = 1; i <= n; i++) sum += (a[i] = inp());
		
		if(sum % n != 0) {
			puts("-1");
			continue;
		}	
		
		ans = 0; sum /= n;
		for(i = 1; i + d <= n; i++) {
			LL mov = a[i] - sum;
			a[i + d] += mov;
			a[i] -= mov;
			ans += (mov > 0 ? mov : - mov);
		}
		
		int chk = 1;
		for(i = 1; i <= n; i++) if(a[i] != sum) chk = 0;
		if(!chk) puts("-1");
		else cout << ans << endl;
	}
	return 0;
}


