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

const int MaxN = 511234, MaxM = 511234, MaxC = 26;

int n, ch[MaxM][MaxC], d[MaxM], id[MaxN], pc = 1; 

char s[MaxN];

void insert(int o, char * s) {
	int L = strlen(s), i, p = 1;
	for(i = L - 1; ~i; i--){
		if(!ch[p][s[i] - 'a'])
				ch[p][s[i] - 'a'] = ++pc;
		p = ch[p][s[i] - 'a'];
	}
	d[p]++; id[p] = o;
} 

int siz[MaxM], fa[MaxM];
vector<int> e[MaxM];

bool cmp(int i, int j) {
	return siz[i] < siz[j];
}

void dfs(int x, int fat) {
	if(d[x]) {
		fa[id[x]] = fat;
		e[fat].emplace_back(id[x]);
		fat = id[x];
	}
	
	for(int i = 0; i < 26; i++)
		if(ch[x][i]) dfs(ch[x][i], fat);
}

void dfs2(int x) {
	siz[x] = 1; 
	for(auto b : e[x]) {
		dfs2(b); 
		siz[x] += siz[b];
	}
	sort(e[x].begin(), e[x].end(), cmp);
}

int dfn[MaxM], t;
void dfs3(int x) {
	if(x) dfn[x] = ++t;
	for(auto b : e[x]) 
		dfs3(b); 
}

int main() {
	int i, j;
	n = inp();
	for(i = 1; i <= n; i++) {
		scanf("%s", s);
		insert(i, s);
	}

	dfs(1, 0);
	dfs2(0);
	dfs3(0);
	
	LL ans = 0;
	for(i = 1; i <= n; i++)
		ans += dfn[i] - dfn[fa[i]];
	cout << ans;
	
	return 0;
}



