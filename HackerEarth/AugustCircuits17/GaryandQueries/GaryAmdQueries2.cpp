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
const int S = sqrt(MaxN);
 
int n, q, a[MaxN];
LL sum[S + 1], bit[MaxN];
 
void bit_modify(int p, int d) {
	for(int i = MaxN - p; i < MaxN; i += i & -i)
		bit[i] += d;
}
 
LL bit_query(int p) {
	LL ans = 0;
	for(int i = MaxN - p; i; i -= i & -i)
		ans += bit[i];
	return ans;
}
 
void append(int p) {
	int y = inp(); 
	for(int i = 1; i <= S; i++) sum[i] += y/i - a[p]/i;
	
	if(a[p])
		bit_modify(a[p], -1);
	a[p] = y;
	if(a[p])
		bit_modify(a[p], 1);
}
 
int query(int p) {
	LL ans = 0; 
	if(p <= S) ans = sum[p];
	else 
		for(int i = p; i < MaxN; i += p) {
			ans += bit_query(i);
		}
	return ans;
}
 
int main() {
	int i;
	
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	n = inp(); q = inp();
	
	for(i = 1; i <= n; i++) 
		append(i);
	
	for(i = 1; i <= q; i++) {
		int op = inp(), x = inp();
		if(op == 1) 
			append(x);
		else 
			printf("%lld\n", query(x));
	}
	return 0;
}
