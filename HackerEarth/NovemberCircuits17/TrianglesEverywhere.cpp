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
 
const int MaxN = 1001234, P = 1000000007;
 
int f[MaxN], T;
int main() {
	int i;
	T = read();
	f[0] = 1;
	for(i = 1; i < MaxN; i++) f[i] = (f[i - 1] * 3ll + 2) % P; 
	while(T--) {
		i = read();
		printf("%d\n", f[i]);
	}
	return 0;
}
