#include <bits/stdc++.h>

#define fir first
#define sec second
using namespace std;
typedef long long LL;
typedef unsigned long long u64;

template <typename T> inline bool cmin(T & a, const T & b) { return a > b ? a = b, 1 : 0;}
template <typename T> inline bool cmax(T & a, const T & b) { return a < b ? a = b, 1 : 0;}
int inp() {
	int x = 0, f = 1;char ch;
	for(ch = getchar(); !isdigit(ch); ch = getchar())
		if(ch == '-') f = -1;
	for(; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	return x * f;
}

const int MaxN = 1234;
int n, y[MaxN], d[MaxN];

int main() {
	int i, j, k;
	
	cin >> n;
	for(i = 1; i <= n; i++) cin >> y[i];
	for(i = 1; i <= n; i++) 
		for(j = i; j <= n; j++) {
			int A = y[i] - y[j];
			int B = i - j;
			int cnt = 0;
			int pre = 0, prey = 0, chk = 1;
			
			for(k = 1; k <= n; k++) {
				int C = y[k] - y[i];
				int D = k - i;
				if((LL) A * D != (LL) C * B) {
					if(!pre) pre = k, prey = y[pre];
					else {
						int C = y[k] - prey; 
						int D = k - pre;
						if((LL) A * D != (LL) B * C) {
							chk = 0; break;
						}
					}
				}
			}
			
			if(chk && pre) {
				puts("Yes"); 
				return 0;
			}
		}
	puts("No");
	return 0;
}



