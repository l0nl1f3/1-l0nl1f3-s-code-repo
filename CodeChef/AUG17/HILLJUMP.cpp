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

const int MaxN = 101234, MaxB = 300, Lim = 100;

int n, m, q, L[MaxN], R[MaxN], bel[MaxN];
int s[MaxN], sn, suc[MaxN], len[MaxN], far[MaxN];

LL a[MaxN], h[MaxN];

int jump() {
	int p, K;
	p = inp(); K = inp();
	
	for(;;) {
		if(suc[p] == p) return p;
		p = suc[p];
		if(! --K) return p;
		if(K > len[p]) 
			K -= len[p], p = far[p];
		else {
			for(; K--; p = suc[p]); return p;
		}
	}
}
void reb(int x) {
	int i, np; LL p = h[x];
	for(i = L[x]; i <= R[x]; i++) {
		while(np = s[sn], (sn && a[np] < a[i]))			
			suc[np] = i, --sn;
		s[++sn] = i;
	}
	
	for(i = R[x] + 1; i <= n && i <= R[x] + Lim; i++)
		while(np = s[sn], (sn && a[np] + p < a[i] + h[bel[i]]))
			suc[np] = i, --sn;
	for(; sn; suc[s[sn--]] = n + Lim + 1);
	
	for(i = L[x]; i <= R[x]; i++) 
		if(i + Lim < suc[i]) suc[i] = i;
		
	for(i = R[x]; i >= L[x]; i--) {
		int o = (suc[i] <= R[x] && suc[i] != i);
		far[i] = o ? far[suc[i]] : i;
		len[i] = o ? len[suc[i]] + 1 : 0;
	}
}
void modify() {
	int l, r, x, i;
	l = inp(); r = inp(); x = inp();
	
	int A = bel[l], B = bel[r];
	
	if(A == B) {
		for(i = l; i <= r; i++) a[i] += x;
		reb(B); reb(B - 1);
		return;
	}
	
	for(i = l; i <= R[A]; i++) a[i] += x;
	for(i = L[B]; i <= r; i++) a[i] += x;
	for(i = A + 1; i < B; i++) h[i] += x;
	reb(A); if(A > 1) reb(A - 1); 
	reb(B); if(B > 1) reb(B - 1); 
}

int main() {
	int i;
	n = inp(); q = inp();
	for(i = 1; i <= n; i++) a[i] = inp();
	for(i = 1; i <= n; i++) {
		bel[i] = (i - 1) / MaxB + 1;
		if(bel[i] != bel[i - 1]) {
			R[bel[i - 1]] = i - 1;
			L[bel[i]] = i;
		}
	}
	m = bel[n]; R[m] = n;
	for(i = 1; i <= m; i++)  reb(i);
	
	while(q--) {
		if(inp() == 1) 
			printf("%d\n", jump());
		else 
			modify();
	}
	return 0;
}



