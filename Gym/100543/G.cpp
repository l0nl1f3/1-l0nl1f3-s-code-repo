#include <bits/stdc++.h>

#define fi first
#define se second
#define mp make_pair
#define pb push_back

using namespace std;
typedef long long LL;
typedef unsigned long long u64;

template <typename T> inline bool cmin(T & a, const T & b) { return a > b ? a = b, 1 : 0;}
template <typename T> inline bool cmax(T & a, const T & b) { return a < b ? a = b, 1 : 0;}
int read() {
	int x = 0, f = 1;char ch;
	for (ch = getchar(); !isdigit(ch); ch = getchar())
		if (ch == '-') f = -1;
	for (; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	return x * f;
}

const int MaxN = 101234;

int dec(char x) {
	if(x == 'A') return 0;
	if(x == 'G') return 1;
	if(x == 'T') return 2;
	if(x == 'C') return 3;
}

int n; char s[MaxN];

int ch[MaxN][4], len[MaxN], nxt[MaxN], fail[MaxN], lst, tn;

void clear(int x) {
	ch[x][0] = ch[x][1] = ch[x][2] = ch[x][3] = 0;
}

void build(int n, char s[]) {
	tn = lst = 1; fail[0] = fail[1] = 1;
	len[1] = -1; clear(0); clear(1);
	
	for (int i = 1; i <= n; i++) {
		int p = lst;
		while (s[i - len[p] - 1] != s[i]) p = fail[p];
		int c = dec(s[i]);
		if (!ch[p][c]) {
			int np = ++tn, q; clear(np);
			len[np] = len[p] + 2;
			for (q = fail[p]; s[i - len[q] - 1] != s[i]; q = fail[q]);
			nxt[np] = fail[np] = ch[q][c]; ch[p][c] = np;
		}
		lst = ch[p][c];
	}
}

int pos[MaxN], f[MaxN];

void solve() {
	scanf("%s", s + 1); n = strlen(s + 1);
	build(n, s);
	
	for (int i = 2; i <= tn; i++) pos[i - 1] = i;
	sort(pos + 1, pos + tn, [&] (int x, int y) {return len[x] < len[y]; });
	for (int i = tn - 1; i; i--) {
		int p = pos[i];
		while(len[nxt[p]] > len[p] / 2) 
			nxt[p] = fail[nxt[p]];
		if(len[nxt[p]] < len[nxt[fail[p]]])
			nxt[fail[p]] = nxt[p];
	}	
	
	int ans = n;
	
	for (int i = 0; i <= tn; i++) f[i] = len[i];
	for (int i = 1; i < tn; i++) {
		int p = pos[i];
		cmin(f[p], f[fail[p]] + len[p] - len[fail[p]]);
		if(len[p] & 1) continue;
		cmin(f[p], f[nxt[p]] + len[p] / 2 - len[nxt[p]] + 1);
		for (int c = 0; c < 4; c++)
			cmin(f[ch[p][c]], f[p] + 1);
		cmin(ans, n - len[p] + f[p]);
	}
	cout << ans << endl;
}

int main() {
	int T = read();
	while(T--) solve(); 
	return 0;
}




