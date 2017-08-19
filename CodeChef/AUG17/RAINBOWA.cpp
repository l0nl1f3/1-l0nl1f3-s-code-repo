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

const int MaxN = 233;
int n, a[MaxN];

int main() {
	int i, j, T  = inp();
	while(T--) {
		n = inp();
		memset(a, 0, sizeof(a));
		
		for(i = 1; i <= n; i++)
			a[i] = inp();
		int bd = 1, chk = 1;
		for(i = 1, j = n; i <= j; i++, j--){
			int L = 1, R = 1;
			if(a[i] != bd || a[j] != bd) chk = 0; 
			
			while(i + 1 < j && a[i + 1] == a[i]) ++i, ++L;
			while(j - 1 > i && a[j - 1] == a[j]) --j, ++R;
			
			++bd;
			
			if(L != R)
				chk = 0;
			if(bd == 7) break;
		}
		if(i + 1 >= j) chk = 0; 
		for(i = i + 1; i < j; i++) if(a[i] != 7) chk = 0; 
		if(chk && bd == 7) puts("yes"); else puts("no");
	}
	return 0;
}

