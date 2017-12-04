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

const int MaxN = 101234;
int ch[MaxN][2], fa[MaxN], siz[MaxN],  val[MaxN], pyn, root;

int child(int x) {
	return ch[fa[x]][1] == x;
}

int update(int x) {
	siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + 1;
}

int rot(int x) {
	int y = fa[x], o = child(x);
	if(fa[y]) ch[fa[y]][child(y)] = x;
	if(ch[x][o ^ 1]) fa[ch[x][o ^ 1]] = y;
	ch[y][o] = ch[x][o ^ 1]; ch[x][o ^ 1] = y;
	fa[x] = fa[y]; fa[y] = x;
	update(x); update(y);
}

int splay(int x, int y = 0) {
	for(; fa[x] != y; rot(x))
		if(fa[fa[x]] != y)
			if(child(x) ^ child(fa[x]))
				rot(x);
			else
				rot(fa[x]);
	if(!y) root = x;
}

void insert(int &p, int f, int x) {
	if(!p) {
		siz[p = ++pyn] = 1;
		fa[p] = f; val[p] = x;
		return;
	}
	insert(ch[p][x > val[p]], p, x);
	update(p);
}

int find(int p, int x) {
	if(!p) return 0;
	if(x > val[p])
		return find(ch[p][1], x);
	int res = find(ch[p][0], x);
	return res ? res : p;
	/*
	if(val[p] == x) return p;
	return find(ch[p][x > val[p]], x);
	*/
}

int kth(int p, int K) {
	if(siz[ch[p][0]] == K - 1) return val[p]; 
	if(siz[ch[p][0]] >= K)
		return kth(ch[p][0], K);
	else
		return kth(ch[p][1], K - siz[ch[p][0]] - 1);
}

int Rank(int x) {
	x = find(root, x);
	splay(x); 
	return siz[ch[x][0]];
}

int far(int x, int o) {
	return ch[x][o] ? far(ch[x][o], o) : x;
}

void del(int x) {
	x = find(root, x);
	splay(x);
	int L = far(ch[x][0], 1);
	int R = far(ch[x][1], 0);
	splay(L); splay(R, L);
	ch[R][0] = 0; 
	update(L); update(R);
}

int pre(int x) {
	insert(root, 0, x);
	int y = find(root, x);
	splay(y);
	int L = far(ch[y][0], 1); del(x);
	return val[L];
}

int suc(int x) {
	insert(root, 0, x + 1);
	int y = find(root, x + 1);
	splay(y);
	int R = far(ch[y][1], 0); del(x + 1);
	return val[R];
}

int main() {
	int i;
	int n = read();
	insert(root, 0, 2e9);
	insert(root, 0, -2e9);
	while(n--) {
		int op = read(), x = read();
		if(op == 1) insert(root, 1, x);
		if(op == 2) del(x);
		if(op == 3) printf("%d\n", Rank(x));
		if(op == 4) printf("%d\n", kth(root, x + 1));
		if(op == 5) printf("%d\n", pre(x));
		if(op == 6) printf("%d\n", suc(x));
	}
	
	return 0;
}



