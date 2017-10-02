#include <bits/stdc++.h>

using namespace std;

const int MaxN = 1001234;

vector<int> e[MaxN], buc[MaxN];
int n, K, pos[MaxN], col[MaxN]; 

int getint() {
	int x = 0, f = 1; char ch;
	for(ch = getchar(); !isdigit(ch); ch = getchar())
		if(ch == '-') f = -1;
	for(; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	return x * f;
}

int ans[MaxN];

void dfs(int x, int fa) {
	int p = col[x];
	if(buc[p].size() < K) ans[x] = -1; else ans[x] = buc[p][buc[p].size() - K];
	buc[p].push_back(x);
	for(auto y : e[x]) {
		if(y == fa) continue;
		dfs(y, x);
	}
	buc[p].pop_back();
}

int main() {
	int i;
	n = getint(); K = getint();
	for(i = 1; i <= n; i++) col[i] = getint();
	for(i = 1; i < n; i++) {
		int u = getint(), v = getint();
		e[u].push_back(v);
		e[v].push_back(u);
	}
	
	dfs(1, 0);
	for(i = 1; i <= n; i++) {
		printf("%d ", ans[i]);
	}	
}
