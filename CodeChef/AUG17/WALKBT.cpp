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

const int MaxN = 401234, MaxM = 40 * MaxN;

int n, q, cnt, fake; LL ex;

int get_op() {
	char op[3]; scanf("%s", op);
	return (op[0] == '?') + 1;
}
const int seed = 23;
int pc, rot[MaxN << 1], ls[MaxM], rs[MaxM], v[MaxM];

const int P1 = 1e9 + 9;
const int P2 = 1e9 + 7;

LL sum1[MaxM], sum2[MaxM], pr1[MaxN], pr2[MaxN]; 

int s[MaxN];

void modify(int &x, int y, int l, int r, int p) {
	x = ++pc;

	if(l == r) {
		sum1[x] = (s[n - p + 1] ? pr1[n - p + 1] : 0);
		sum2[x] = (s[n - p + 1] ? pr2[n - p + 1] : 0);
		
		v[x] = s[n - p + 1];
		return;
	}
	ls[x] = ls[y]; rs[x] = rs[y];
	
	if(p <= l + r >> 1) 
		modify(ls[x], ls[y], l, l + r >> 1, p);
	else 
		modify(rs[x], rs[y], (l + r >> 1) + 1, r, p);
		
	sum1[x] = (sum1[ls[x]] + sum1[rs[x]]) % P1;
	sum2[x] = (sum2[ls[x]] + sum2[rs[x]]) % P2;
}
int equal(int x, int y, int l, int r) {
	LL u1 = sum1[x], v1 = sum1[y];
	LL u2 = sum2[x], v2 = sum2[y];
	
	if(l == r) return u1 == v1 && u2 == v2;
	
	u1 = sum1[ls[x]]; v1 = sum1[ls[y]];
	u2 = sum2[ls[x]]; v2 = sum2[ls[y]];
	if(u1 == v1 && u2 == v2) 
		return (l + r >> 1) - l + 1 + equal(rs[x], rs[y], (l + r >> 1) + 1, r);
	else 
		return equal(ls[x], ls[y], l, l + r >> 1);
}

int chk(int x, int l, int r, int p) {
	if(l == r) return v[x];
	if(p <= l + r >> 1)
		return chk(ls[x], l, l + r >> 1, p);
	else 
		return chk(rs[x], (l + r >> 1) + 1, r, p);
}

struct atom { int rot;};

set<atom>st;
bool operator < (atom a, atom b) {
	int u = a.rot, v = b.rot;
	int lcp = equal(rot[u], rot[v], 1, n);
	if(lcp == n) return u < v;
	else return chk(rot[u], 1, n, lcp + 1) < chk(rot[v], 1, n, lcp + 1);
}

void and_one() {
	int p = inp() + 1, lcp, i; 
	++cnt;
	while(p <= n && s[p]){
		s[p] = 0;
		modify(rot[fake + 1], rot[fake], 1, n, n - p + 1); 
		++p; ++fake;
	}

	if(p <= n) {
		s[p] = 1;
		modify(rot[fake + 1], rot[fake], 1, n, n - p + 1); ++fake;
	}	
	atom ins; ins.rot = fake;
	set<atom> :: iterator nxt = st.upper_bound(ins);
	
	if(nxt != st.begin()) {
		set <atom> :: iterator pre = --st.upper_bound(ins);
		ex += equal(rot[ins.rot], rot[pre -> rot], 1, n);
		
		if(nxt != st.end()) 
			ex -= equal(rot[pre -> rot], rot[nxt -> rot], 1, n);
	}
	
	if(nxt != st.end())
		ex += equal(rot[ins.rot], rot[nxt -> rot], 1, n);
	
	st.insert(ins);
}

LL query() {
	return (LL)	cnt * n - ex + 1;
}

void solve() {
	int i, j, k;
	cnt = fake = ex = 0;
	n = inp(); q = inp();
	while(q--) 
		if(get_op() == 1)
			and_one();
		else 
			printf("%lld\n", query());
}

int main() {
	int T = inp(), i;
	for(pr1[0] = 1, i = 1; i < MaxN; i++) pr1[i] = (LL) pr1[i - 1] * seed % P1;
	for(pr2[0] = 1, i = 1; i < MaxN; i++) pr2[i] = (LL) pr2[i - 1] * seed % P2;
	
	while(T--) {
		pc = 0;
		st.clear();
		memset(s, 0, sizeof(s));
		solve();
	}
	return 0;
}



