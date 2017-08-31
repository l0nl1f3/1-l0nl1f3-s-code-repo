#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

const int P = 1000000007;
const int MaxN = 401234, MaxK = 12;

int n, q, a[MaxN];


int exp(int a, int n) {
	int res = 1;
	for(; n; n >>= 1) {
		if(n & 1) 
			res = (LL) res * a % P;
		a = (LL) a * a % P;
	}
	return res;
}

int seg[MaxN][MaxK], tag[MaxN], en[MaxN], to[MaxN], c[MaxK][MaxK];

void push_up(int p) {
	for(int o = 0; o <= 10; o++)
		seg[p][o] = (seg[p << 1][o] + seg[p << 1 | 1][o]) % P;
}

void put(int q, int p, int l, int r) {
	// push q to p
	// assert(!tag[q] || !en[q]);
	if(en[q]) {
		en[p] = 1; to[p] = to[q]; tag[p] = 0;
		for(int o = 0; o <= 10; o++) {
			int s = exp(to[p], o);
			seg[p][o] = (LL) s * (r - l + 1) % P;
		}
	} 
	
	if(tag[q]) {
		(tag[p] += tag[q]) %= P; 
		
		int x = tag[q], xp[20];
		xp[0] = 1;
		for(int o = 1; o <= 10; o++) xp[o] = (LL) xp[o - 1] * x % P;
		
		for(int o = 10; ~o; o--) {
			int t = 0;
			for(int i = 0; i <= o; i++) {
				int A = seg[p][i];
				int B = (LL) xp[o - i] * c[o][i] % P;
				t = (t + (LL) A * B) % P;
			}
			seg[p][o] = t;
		}
	}
	
}
void push_down(int p, int l, int r) {
	if(l ^ r) {
		put(p, p << 1, l, l + r >> 1);
		put(p, p << 1 | 1, (l + r >> 1) + 1, r);
	} 
	en[p] = 0; tag[p] = 0;
}
void build(int p, int l, int r) {
	if(l == r) {
		for(int o = 0; o <= 10; o++)
			seg[p][o] = exp(a[r], o);
		return;
	}
	build(p << 1, l, l + r >> 1);
	build(p << 1 | 1, (l + r >> 1) + 1, r);
	push_up(p);
}

void modify(int p, int l, int r, int a, int b, int d) {
	if(b < l || a > r) return;
	if(a <= l && r <= b) {
//		push_down(p, l, r);
		tag[p] = (tag[p] + d) % P;	
		
		int x = d, xp[20];
		xp[0] = 1;
		for(int o = 1; o <= 10; o++) xp[o] = (LL) xp[o - 1] * x % P;
		
		for(int o = 10; ~o; o--) {
			int t = 0;
			for(int i = 0; i <= o; i++) {
				int A = seg[p][i];
				int B = (LL) xp[o - i]* c[o][i] % P;
				t = (t + (LL) A * B) % P;
			}
			seg[p][o] = t;
		}
		return;
	}
	push_down(p, l, r);
	modify(p << 1, l, l + r >> 1, a, b, d);
	modify(p << 1 | 1, (l + r >> 1) + 1, r, a, b, d);
	push_up(p);
}

void cover(int p, int l, int r, int a, int b, int d) {
	if(b < l || a > r) return;
	if(a <= l && r <= b) {
		//push_down(p, l, r);
		tag[p] = 0;
		en[p] = 1;
		to[p] = d;
		int dp = 1;
		for(int o = 0; o <= 10; o++) {
			seg[p][o] = (LL) (r - l + 1) * dp % P;
			dp = (LL) dp * d % P;
		}
		return;
	}
	push_down(p, l, r);
	cover(p << 1, l, l + r >> 1, a, b, d);
	cover(p << 1 | 1, (l + r >> 1) + 1, r, a, b, d);
	push_up(p);
}

int query(int p, int l, int r, int a, int b, int k) {
	if(b < l || a > r) return 0;
	if(a <= l && r <= b){
//		push_down(p, l, r);
		return seg[p][k];
	} 
	
	push_down(p, l, r);
	
	return (query(p << 1, l, l + r >> 1, a, b, k) + query(p << 1 | 1, (l + r >> 1) + 1, r, a, b, k)) % P;
}

int main() {
	int i, j;
	scanf("%d%d", &n, &q);
	for(i = 1; i <= n; i++) scanf("%d", a + i);
	c[0][0] = 1;
	for(i = 1; i < MaxK; i++){
		c[i][0] = 1; c[i][i] = 1;
		for(j = 1; j < i; j++) 
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
	}
	
	build(1, 1, n);
	while(q--) {
		int op, l, r, x;
		scanf("%d%d%d%d", &op, &l, &r, &x);
		if(op == 1) {
			modify(1, 1, n, l, r, x);
		}
		
		if(op == 2) {
			cover(1, 1, n, l, r, x);
		}
		
		if(op == 3) 
		{
			printf("%d\n", query(1, 1, n, l, r, x));
		}
	//	for(i = 1; i <= n; i++) printf("%d ", query(1, 1, n, i, i, 1)); puts(""); 
	}	
	return 0;
}
