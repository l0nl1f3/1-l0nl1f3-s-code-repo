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

int n, a[1234], ans[1234];
map<int, int> s;
vector<int> v;
int main() {
	int i;
	n = read(); 
	for(i = 1; i <= n; i++) {
		a[i] = read();
		if(a[i] > 0)
			s[a[i]]++;
		if(a[i] < 0){
			if(s[-a[i]]) --s[-a[i]];
			else {
				if(v.size()) 
					ans[v.back()] = -a[i], v.pop_back();
				else 
					return puts("No"), 0;
			}
		}
		if(!a[i])
			v.push_back(i);
	}
	puts("Yes");
	for(i = 1; i <= n; i++) if(!a[i]) printf("%d ", max(ans[i], 1));
	return 0;
}

