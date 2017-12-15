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

const int Min = -32768, Max = 32767;
 
char s[2333];
int main() {
	int i;
	vector<pair<int, int> > a;
	while(scanf(" %[^\r\n]", s) == 1) {
		int l, r;
		if(sscanf(s, "x <= %d", &r) == 1) 
			l = Min;
		else 
			if(sscanf(s, "x >= %d && x <= %d ", &l, &r) == 1) 
				r = Max;
		if(l <= r) {
			a.emplace_back(make_pair(l, 0));
			a.emplace_back(make_pair(r + 1, 1));
		}
	}	
	sort(a.begin(), a.end());
	int m = 0, l = Min, chk = 0;
	for(auto x : a) {
		if(!x.sec) {
			if((++m) == 1) 
				l = x.fir;
		}else {
			if(!--m) {
				if(chk) puts(" ||"); chk = 1;
				if(l == Min && x.fir == Max + 1) printf("true");
				else if(l == Min) printf("x <= %d", x.fir - 1);
				else if(x.fir == Max + 1) printf("x >= %d", l);
				else printf("x >= %d && x <= %d", l, x.fir - 1);
			}
		}
	}
	if(!chk) puts("false");
	return 0;
}

