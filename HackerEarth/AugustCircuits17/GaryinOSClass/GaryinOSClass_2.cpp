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
 
const int MaxN = 101234, MaxM = 1001234;
int n, m, K, a[MaxN];
 
namespace io {
	void output(int K, vector <int> v[]) {
		printf("%d\n", K);
		for(int i = 1; i <= m/K; i++, puts("")) {
			printf("%d ", v[i].size());
			for(auto atom : v[i])
				printf("%d ", atom);
		}
	}
}
 
vector <int> ans[MaxM];
 
int main() {
	int i;
	
	n = inp(); m = inp();
	for(i = 1; i <= n; i++) a[i] = inp();
	return 0;
}
