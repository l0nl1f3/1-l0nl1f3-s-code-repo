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

pair<int, int> s[3]; int a, b, c;
vector<tuple<int, int, int> > v;	

void build1(int a, int b, int c) {
	for(int i = 0; i < a; i++) c--, v.emplace_back(0, i, 0);
	for(int i = 1; i < b; i++) c--, v.emplace_back(i, 0, 0);
	for(int i = 1; i < a && c; i++)
		for(int j = 1; j < b && c; j++)
			c--, v.emplace_back(j, i, 0);
}

void build2(int a, int b, int c) {
	for(int i = c; i < a; i++) v.emplace_back(0, i, 0);
	for(int i = c; i < b; i++) v.emplace_back(i, 0, 0);
	for(int i = 1; i < c; i++) v.emplace_back(i, c - i, 0);
}

int main() {
	cin >> s[0].fir >> s[1].fir >> s[2].fir;
	s[0].sec = 0; s[1].sec = 1; s[2].sec = 2;
	sort(s, s + 3);
	a = s[0].fir; b = s[1].fir, c = s[2].fir;
	if(c > a * b) return puts("-1"), 0;
	if(c >= a + b - 1)
		build1(a, b, c);
	else 
		build2(a, b, a + b - 1 - c);
	printf("%d\n", v.size());
	int p[3];
	for(auto i : v) {
		int x[3];
		tie(x[0], x[1], x[2]) = i;
		int ans[3];
		for(int i = 0; i < 3; i++) ans[s[i].sec] = x[i];
		printf("%d %d %d\n", ans[2], ans[1], ans[0]);
	}
	return 0;
}

