#include <bits/stdc++.h>
#define right LASFAASFASG 
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

const int MaxN = 101234, MaxM = 3 * 3 + 1;
const int MaxNode = 201234;

int n, m, q;
LL down[MaxM][MaxN], right[MaxM][MaxN];

struct SegNode {
	LL d[MaxM][MaxM], tag[MaxM][MaxM], a[MaxM][MaxM], b[MaxM][MaxM];
	int siz;
}seg[MaxNode]; 


LL mask[60];
void make(SegNode & cur, int p) {
	int i, j, k;
	cur.siz = 1;
	memset(cur.d, 127/3, sizeof(cur.d));
	for(i = 0; i < m; i++) {
		cur.d[i][i + m] = cur.d[i + m][i] = right[i][p];
		cur.a[i][i + m] = cur.a[i + m][i] = mask[i];
		if(i == m - 1) continue;
		cur.d[i][i + 1] = cur.d[i + 1][i] = down[i][p];
		cur.a[i][i + 1] = cur.a[i + 1][i] = mask[i + m];
		cur.d[i + m][i + m + 1] = cur.d[i + m + 1][i + m] = down[i][p + 1];
		cur.a[i + m][i + m + 1] = cur.a[i + m + 1][i + m] = mask[i + m + m];
	}
	for(k = 0; k < m + m; k++)
		for(i = 0; i < m + m; i++)
			for(j = 0; j < m + m; j++)
				if(cmin(cur.d[i][j], cur.d[i][k] + cur.d[k][j]))
					cur.a[i][j] = cur.a[i][k] | cur.a[k][j];
}

SegNode add(SegNode a, SegNode b) {
	int i, j, k;
	pair<LL, pair<LL, LL> > pa[MaxM][MaxM];
	for(i = 0; i < m * 3; i++)
		for(j = 0; j < m * 3; j++) 
			pa[i][j] = make_pair((LL)1e18, make_pair(0, 0));
	
	for(i = 0; i < m + m; i++) 
		for(j = 0; j < m + m; j++) {
			pair<LL, LL> pt = make_pair(mask[i * (m + m) + j], 0);
			cmin(pa[i][j], make_pair(a.d[i][j], pt));
		}
	
	for(i = 0; i < m + m; i++)
		for(j = 0; j < m + m; j++) {
			pair<LL, LL> pt = make_pair(0, mask[i * (m + m) + j]);
			cmin(pa[i + m][j + m], make_pair(b.d[i][j], pt));
		}
		
	for(k = 0; k < m * 3; k++)
		for(i = 0; i < m * 3; i++)
			for(j = 0; j < m * 3; j++) {
				LL u = pa[i][k].sec.fir | pa[k][j].sec.fir;
				LL v = pa[i][k].sec.sec | pa[k][j].sec.sec;
				pair<LL, LL> pt = make_pair(u, v);
				cmin(pa[i][j], make_pair(pa[i][k].fir + pa[k][j].fir, pt));
			}
			
	SegNode cur; memset(&cur, 0, sizeof(cur));
	for(i = 0; i < m + m; i++)
		for(j = 0; j < m + m; j++) {
			pair<LL, pair<LL, LL> > pt = pa[i + m * (i >= m)][j + m * (j >= m)];
			cur.d[i][j] = pt.fir;
			cur.a[i][j] = pt.sec.fir;
			cur.b[i][j] = pt.sec.sec;
		}
	cur.siz = a.siz + b.siz;
	return cur;
}

void build(int p, int l, int r) {
	if(l == r) {
		make(seg[p], r);
		return;
	}
	build(p << 1, l, l + r >> 1);
	build(p << 1 | 1, (l + r >> 1) + 1, r);
	seg[p] = add(seg[p << 1], seg[p << 1 | 1]);
}

int main() {
	int i, j;
	m = inp(); n = inp() + 1; q = inp();
	
	memset(right, 127/3, sizeof(right));
	memset(down, 127/3, sizeof(down));
	for(i = 0; i < m - 1; i++)
		for(j = 2; j <= n; j++)
			scanf("%lld", down[i] + j);
	for(i = 0; i < m; i++)
		for(j = 2; j < n; j++)
			scanf("%lld", right[i] + j); 
	mask[0] = 1;
	for(i = 1; i < 60; i++) mask[i] = (mask[i - 1] << 1);		
	build(1, 1, n);
	
	for(i = 0; i < m + m; i++, puts(""))
		for(j = 0; j < m + m; j++) printf("%lld ", seg[1].d[i][j]);
	while(q--) {
		
	}
	return 0;
}



