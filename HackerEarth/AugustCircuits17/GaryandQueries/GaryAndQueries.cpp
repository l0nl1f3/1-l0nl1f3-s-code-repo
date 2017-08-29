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

const int MaxN = 501234;

int n, q, a[MaxN];
int m, bs, bel[MaxN], L[MaxN], R[MaxN]; LL tag[MaxN], s[MaxN];

#define mdf(l, r, x) \
	s[l] += x; s[r + 1] -= x;\
	tag[bel[l]] += x; tag[bel[r + 1]] -= x;
	
void modify(int x, int d) {
	int i, j;
	for(i = 1; i <= x; i = j + 1) {
		j = x/(x/i);
		int v = d * x/i;
		mdf(i, j, v);
	}
}

void append(int p) {
	if(a[p]) 
		modify(a[p], -1);
	a[p] = inp();
	if(a[p])
		modify(a[p], 1);
}

int query(int p) {
	int i;
	LL ans = 0;
	for(i = 1; i < bel[p]; i++) ans += tag[i];
	for(i = L[bel[p]]; i <= p; i++) ans += s[i];
	return ans;
}

int main() {
	int i;
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	n = inp(); q = inp();
	
	bs = sqrt(n)/2;
	for(i = 1; i <= n; i++) {
		bel[i] = (i - 1)/bs + 1;
		if(bel[i] != bel[i  - 1]) {
			R[bel[i - 1]] = i - 1;
			L[bel[i]] = i;
		}
	}
	m = bel[n]; R[m] = n;
	
	for(i = 1; i <= n; i++) 
		append(i);
	
	for(i = 1; i <= q; i++) {
		int op = inp(), x = inp();
		if(op == 1) 
			append(x);
		else 
			printf("%d\n", query(x));
		
	}
	return 0;
}



