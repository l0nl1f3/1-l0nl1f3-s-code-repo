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

const int MaxNode = 4001234;

int ch[MaxNode][2], fa[MaxNode], trin;
string s; int n; vector<int> ed[MaxNode];

void append(string s, int k) {
	int p = 0, i;
	for(i = 0; i < s.size(); i++) {
		if(!ch[p][s[i] - '0']) {
			ch[p][s[i] - '0'] = ++trin;
			fa[trin] = p;
		}
		p = ch[p][s[i] - '0'];
	}
	ed[p].emplace_back(k);
}

vector<int> e[MaxNode];

void insert(int a, int b) {
	e[a].emplace_back(b);
}

int dfn[MaxNode], low[MaxNode], ind, st[MaxNode], sn, ins[MaxNode], bel[MaxNode], scc;
void dfs(int x) {
	dfn[x] = low[x] = ++ind;
	ins[st[++sn] = x] = 1;
	for(auto y : e[x]) {
		if(!dfn[y]) {
			dfs(y); 
			cmin(low[x], low[y]);
		}else if(ins[y]) 
			cmin(low[x], dfn[y]);
	}
	if(dfn[x] == low[x]) {
		int v = -1; ++scc;
		while(sn && v != x) {
			ins[v = st[sn--]] = 0;
			bel[v] = scc;
		}
	}
}

string S[501234];

int main() {
	freopen("binary.in", "r", stdin);
	freopen("binary.out", "w", stdout);
	int i, j; n = read();
	for(i = 1; i <= n; i++) {
		cin >> s; S[i] = s; int pos = -1;
		for(j = 0; j < s.size(); j++) 
			if(s[j] == '?') {
				pos = j;
				break;
			}
		if(pos != -1) {
			s[pos] = '0';
			append(s, i - 1 << 1);
			s[pos] = '1';
			append(s, (i - 1 << 1) + 1);
		} else {
			append(s, i - 1 << 1);
			append(s, (i - 1 << 1) + 1);
		}
	}
	for(i = 1; i <= trin; i++) {
		insert(fa[i] + n * 2, i + n * 2);
		insert(trin + 1 + i + n * 2, trin + 1 + fa[i] + n * 2);
	}
	
	int u = 2 * (n + trin) + 1;
	for(i = 1; i <= trin; i++) {
		#define x ed[i][j]
		for(j = 0; j < ed[i].size(); j++) {
			insert(x, i + n * 2);
			insert(fa[i] + n * 2, x ^ 1);
			insert(x, trin + 1 + fa[i] + n * 2);
			insert(trin + 1 + i + n * 2, x ^ 1);
		}
		
		for(j = 0; j < ed[i].size(); j++) {
			insert(x, ++u);
			if(j) {
				insert(u - 1, u);
				insert(u - 1, x ^ 1);
			}
		}
		for(j = 0; j < ed[i].size(); j++) {
			insert(++u, x ^ 1);
			if(j) {
				insert(u, u - 1);
				insert(x, u - 1);
			}
		}
		#undef x
	}
	for(i = 0; i <= u; i++) if(!dfn[i]) dfs(i);
	for(i = 1; i <= n; i++) if(bel[i - 1 << 1] == bel[(i - 1 << 1) + 1]) return puts("NO"), 0;
	puts("YES");
	for(i = 1; i <= n; i++) {
		int pos = -1;
		for(j = 0; j < S[i].size(); j++) 
			if(S[i][j] == '?') {
				if(bel[i - 1 << 1] < bel[(i - 1 << 1) + 1])
					S[i][j] = '0';	
				else
					S[i][j] = '1';
			}
	}
	for(i = 1; i <= n; i++) cout << S[i] << endl;
	return 0;
}

