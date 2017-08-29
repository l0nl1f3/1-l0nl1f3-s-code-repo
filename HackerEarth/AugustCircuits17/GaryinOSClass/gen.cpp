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

int random(int l, int r) {
	LL t = rand() * 233 + rand();
	t = t % (r - l);
	t = t + l;
	return t;
}
int main() {
	int i;
	freopen("input.txt", "w", stdout);
	
	int n = 1e5;
	int m = 1e6;
	
	cout << n << " " << m << endl;
	for(i = 1; i <= n; i++) {
		printf("%d ", random(1e3, 1e5)); 
	} 
	return 0;
}



