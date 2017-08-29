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

const int MaxN = 101234;
const int B = 223, P = 1000000007;

int n, T; char s[MaxN];
LL p[MaxN], hs[MaxN];

LL get(int l, int r) {
	LL h = (hs[r] - hs[l] * p[r - l]) % P;
	return h < 0 ? h + P : h;	
}

int lcp(int i, int j) {
	int l = 0, r = min(j - i, i);
	while(l != r) {
		int o = l + r + 1 >> 1;
		if(get(i - o, i) == get(j - o, j))
			l = o;
		else 
			r = o - 1;
	}
	return i - l + 1;
}

int lcs(int i, int j) {
	int l = 0, r = min(j - i - 1, n - j);
	while(l != r) {
		int o = l + r + 1 >> 1;
		if(get(i, i + o) == get(j, j + o))
			l = o;
		else 
			r = o - 1;
	}
	return i + l + 1;
}
// ºÃÏñÐ´·´ÁË‡å 

LL L[MaxN], R[MaxN];
void solve() {
	int i, j;
	memset(L, 0, sizeof(L));
	memset(R, 0, sizeof(R));
	
	scanf("%s", s + 1); n = strlen(s + 1);
	for(i = 1; i <= n; i++) hs[i] = (hs[i - 1] * B + s[i]) % P;
	for(i = 1; i <= (n >> 1); i++) 
		for(j = 1; j + i <= n; j += i) {
			int u = lcp(j, j + i);
			int v = lcs(j, j + i);
			if(u + i <= v) {
				++L[u]; --L[v - i + 1];
				++R[u + (i << 1) - 1];
				--R[v + i];
			} 
		}
	LL ans = 0;
	for(i = 1; i <= n; i++) {
		L[i] += L[i - 1];
		R[i] += R[i - 1];
		ans += L[i] * R[i - 1];
	}
	cout << ans << endl;
}
int main() {
	p[0] = 1;
	for(int i = 1; i < MaxN; i++) p[i] = p[i - 1] * B % P;
	
	T = inp(); 
	while(T--)  solve();
	return 0;
}



