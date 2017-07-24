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

const int MaxN = 101234;
int n, x, y, z, a[MaxN], b[MaxN], c[MaxN], rk[MaxN];
LL ans = 0;
bool cmp(int x, int y){
	return b[x] - c[x] > b[y] - c[y];
}

priority_queue<int> q; LL f[MaxN], g[MaxN];

int main() {
	int i, j, _i;
	x = inp(); y = inp(); z = inp();
	for(n = (x + y + z), i = 1; i <= n; i++)
		a[i] = inp(), b[i] = inp(), c[i] = inp();
	for(i = 1; i <= n; i++) rk[i] = i; sort(rk + 1, rk + n + 1, cmp);
	
	for(_i = 1; i = rk[_i], _i <= y; _i++) q.push(a[i] - b[i]), ans += b[i] - a[i];
	f[y] = ans;
	for(_i = y + 1; i = rk[_i], _i <= n; _i++){
		if((j = a[i] - b[i]) <= q.top()){
			ans += q.top() - j;
			q.pop(); q.push(j);
		}
		f[_i] = ans;
	} 	
	for(i = 1; i <= (n >> 1); i++) swap(rk[i], rk[n - i + 1]);
	
	ans = 0;
	while(!q.empty()) q.pop();
	for(_i = 1; i = rk[_i], _i <= z; _i++) q.push(a[i] - c[i]), ans += c[i] - a[i];
	g[z] = ans; 
	for(_i = z + 1; i = rk[_i], _i <= n; _i++){
		if((j = a[i] - c[i]) <= q.top()){
			ans += q.top() - j;
			q.pop(); q.push(j);
		}
		g[_i] = ans;
	} 
	ans = -1e14;	
	for(i = y; i <= x + y; i++) cmax(ans, f[i] + g[n - i]);
	for(i = 1; i <= n; i++) ans += a[i];
	cout << ans;
	return 0;
}



