#include<bits/stdc++.h>

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
int ck(int x){
	int a = 0, b = 0;
	for(int i = 1; i <= 3; i++) a += x%10, x /= 10;
	for(int i = 1; i <= 3; i++) b += x%10, x /= 10;
	return a == b;
}
int main() {
	int i;
	cin >> i;
	for(i++; !ck(i); i++);
	cout << i;
	return 0;
}



