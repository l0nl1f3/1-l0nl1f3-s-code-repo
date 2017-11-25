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
 
int T, n, A;
string t[9] = {"", "a",
"ab",
"aab",
"aabb",
"aabbb",
"aaabbb",
"aaababb",
"aaababbb"};

int len[9] = {0, 1, 1, 2, 2, 3, 3, 3, 3};
void solve() {
	string ans; int p = 0;
	if(A == 1) {
		for(int i = 1; i <= n; i++) ans += 'a';
		p = n;
	}
	if(A == 2) {
		if(n <= 8) 
			p = len[n], ans = t[n];
		else {
			p = 4;
			string pr = "bbabaa"; 
			for(int i = 1; i <= n / 6; i++)
				ans += pr;
			for(int i = 0; i < n % 6; i++)
				ans += pr[i];
		}
	}
	if(A > 2) {
		for(int i = 1; i <= n; i++) ans += ('a' + (i - 1) % A);
		p = 1;
	} 
	cout << p << " " << ans << endl;
}
int main() {
	int i;
	cin >> T;
	while(T--) {
		cin >> n >> A;
		solve();
	}
	return 0;
}
