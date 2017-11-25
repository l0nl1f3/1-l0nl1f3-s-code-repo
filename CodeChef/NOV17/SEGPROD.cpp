#include <bits/stdc++.h>
 
#define fir first
#define sec second
using namespace std;
typedef long long LL;
typedef unsigned long long u64;
 
template <typename T> inline bool cmin(T & a, const T & b) { return a > b ? a = b, 1 : 0;}
template <typename T> inline bool cmax(T & a, const T & b) { return a < b ? a = b, 1 : 0;}
namespace io{
	const int L = (1 << 26) + 1;
	
	char buf[L], *S , *T, c;
	 
	char getchar() {
		if(S == T) {
			T = (S = buf) + fread(buf, 1, L, stdin);
			return (S == T ? EOF : *S++);
		}
		return *S++;
	}
	
	int read() {
		int x = 0, f = 1; char ch;
		for(ch = getchar(); !isdigit(ch); ch = getchar())
			if(ch == '-') f = -1;
		for(; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
		return x * f;
	}
};
 
using io :: read;
 
const int MaxN = 1001000;
const int MaxL = 22;
 
int T, n, p, q, b[MaxN], a[MaxN];
 
int prf[MaxL][MaxN], val[MaxN];
 
void solve(int l, int r, int d) {
	if(l == r) 
		return;
	
	int mid = l + r >> 1;
	solve(l, mid, d + 1);
	solve(mid + 1, r, d + 1);
	
	val[mid] = d;
	prf[d][mid] = a[mid] ;
	for(int i = mid - 1; i >= l; i--)
		prf[d][i] = (LL) prf[d][i + 1] * a[i] % p;
		
	prf[d][mid + 1] = a[mid + 1];
	for(int i = mid + 2; i <= r; i++) {
		prf[d][i] = (LL) prf[d][i - 1] * a[i] % p;
	}
} 
 
int st[MaxL][MaxN], lg[MaxN];
 
int query(int l, int r) {
	if(l > r) swap(l, r); 
	if(l == r)	
		return a[r] ;
	
	int x = lg[r - l + 1];
	int dep = min(st[x][l], st[x][r - (1 << x) + 1]);
	return (LL) prf[dep][l] * (val[r] == dep ? 1 : prf[dep][r]) % p;
}
 
int main() {
	int i, j;
	T = read();
	for(i = 2; i < MaxN; i++) lg[i] = lg[i >> 1] + 1, val[i] = 1e7;
	while(T--) {
		n = read(); p = read(); q = read();
		for(i = 1; i <= n; i++)
			a[i] = read()%p;
			
		for(i = 0; i < (q >> 6) + 2; i++)
			b[i] = read();
		solve(1, n, 1);
		for(i = 1; i <= n; i++)
			st[0][i] = val[i];
		for(j = 1; (1 << j) <= n; j++) {
			int *st1 = st[j];
			int *st2 = st[j - 1];
			for(i = 1; i + (1 << j) - 1 <= n; i++) {
				st1[i] = min(st2[i], st2[i + (1 << j - 1)]);
			}
		}
	//	for(i = 0; i < q; i++) {
	//		int L = read(), R = read();
		//	printf("%d\n", query(L, R));
	//	}
		int last = 0;
		int L, R;
		for(i = 0; i < q; i++) {
			if(!(i&63)) {
				L = b[i>>6]; 
				R = b[(i>>6) + 1]; 
			}
			L = (L + last) % n;
			R = (R + last) % n;
	//		if(L > R) swap(L, R);
			last = query(L + 1, R + 1);
			last = last == p - 1 ? 0 : last + 1;
		}
		printf("%d\n", last);
		for(i = 1; i <= n; i++) val[i] = st[0][i] = 1e7;
	}
	return 0;
}  

