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
const int MaxN = 1001234;
int n, a[MaxN], b[MaxN], as[MaxN], bs[MaxN];
int main() {
	int i;
	n = inp();
	for(i = 1; i <= n; i++) as[a[i] = inp()] = i;
	for(i = 1; i <= n; i++) bs[b[i] = inp()] = i;
	for(int d = MaxN - 1; d; d--){
		int x = 0, y = 0, L = MaxN / d * d;
		for(x = L; x > 0 && !as[x]; x -= d);
		for(y = L; y > 0 && !bs[y]; y -= d);
		if(x && y){
			cout << x + y << endl;
			return 0;
		}
	}
	return 0;
}



