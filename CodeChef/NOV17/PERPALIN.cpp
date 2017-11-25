#include <bits/stdc++.h>
 
using namespace std;
 
const int MaxN = 101234;
 
int T, n, p;
char s[MaxN];
 
void solve() {
	if((~p & 1) && p == n) {
		if(p == 2) {
			puts("impossible");
			return;
		}else {
			s[1] = 'a';
			for(int i = 2; i < n; i++) s[i] = 'b';
			s[n] = 'a'; s[n + 1] = '\0'; puts(s + 1);
			return;
		}
	}
	if(p == 1 || p == 2)	{
		puts("impossible");
		return;
	}
	for(int i = 1; i <= p; i++) s[i] = i == (p + 1) / 2 || ((~p & 1) && i == p / 2 + 1)? 'a' : 'b'; s[p + 1] = '\0';
	for(int i = 1; i <= n / p; i++) printf("%s", s + 1); puts("");
}
int main() {
	cin >> T;
	while(T--) {
		cin >> n >> p;
		solve();
	}
} 
