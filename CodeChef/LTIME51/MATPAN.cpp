#include <bits/stdc++.h>
 
#define fir first
#define sec second
using namespace std;
typedef long long LL;
typedef unsigned long long u64;
 
template <typename T> inline bool cmin(T & a, const T & b) { return a > b ? a = b, 1 : 0;}
template <typename T> inline bool cmax(T & a, const T & b) { return a < b ? a = b, 1 : 0;}
int inp() {
	int x = 0, f = 1;char ch;
	for(ch = getchar(); !isdigit(ch); ch = getchar())
		if(ch == '-') f = -1;
	for(; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	return x * f;
}
 
const int MaxN = 51234;
int T; char s[MaxN]; int c[MaxN], b[27];
int main() {
	int i;
	cin >> T;
	while(T--) {
		for(i = 0; i < 26; i++) c[i] = inp();
		scanf("%s", s + 1); int n = strlen(s + 1);
		memset(b, 0, sizeof(b));
		for(i = 1; i <= n; i++) b[s[i] - 'a']++;
		int ans = 0;
		for(i = 0; i < 26; i++) if(!b[i]) ans += c[i]; 
		cout << ans << endl;
	}
	return 0;
}
 
 
 
