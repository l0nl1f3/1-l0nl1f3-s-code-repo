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

const int MaxN = 1001234 * 30;

int n, q, x[2][MaxN];

// x[1][...] positive
// x[0][...] negative

const int M = 33554432;
int T[M << 1]; 

void modify(int p, int d) {
	for(T[p += M] = d, p >>= 1; p; p >>= 1) 
		T[p] = T[p << 1] + T[p << 1 | 1];
}

int query(int l, int r) {
	int res = 0;
	for(l += M - 1, r += M + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
		if(~l & 1) res += T[l ^ 1];
		if(r & 1) res += T[r ^ 1];
	}
	return res;
}

int modify() {
	int a = read(), b = read();
	int o = (a > 0); a = abs(a);
	
	int L, R; L = R = b;
	for(int j = 30; j >= 0; j--) {
		if(a >> j & 1) {
			int i;
			for(i = b + j; x[o][i]; x[o][i++] = 0);
			x[o][i] = 1; cmax(R, i);
		}
	} 
	for(int i = L; i <= R; i++)
		modify(i, x[1][i] ^ x[0][i]);
}

int query() {
	int a = read(), b = 0;
	int L = 0, R = a - 1, i = a;
	while(L <= R) {
		int mid = L + R >> 1;
		if(query(mid, a - 1) == 0)
			i = mid, R = mid - 1;
		else
			L = mid + 1;
	} 

//	for(int i = 0; i <= 15; i++) cout << x[1][i]; cout << endl;
//	for(int i = 0; i <= 15; i++) cout << x[0][i]; cout << endl;
//	cout << i << endl;
	/*
	for(int i = a - 1; i >= 0; i--)
		if(x[1][i] != x[0][i])
			
	*/
	if(i) {
		i--;
		if(x[1][i] > x[0][i])
			return x[1][a] ^ x[0][a];
		else
			return x[1][a] == x[0][a];
	}
	
	return x[1][a] ^ x[0][a];	
}

int main() {
	q = read(); read(); read(); read();
	while(q--) 
		if(read() == 1)
			modify();
		else
			printf("%d\n", query());
	return 0;
}


