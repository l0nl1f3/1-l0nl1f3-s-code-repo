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

const int MaxN = 233;

int h, w, a[MaxN]; string s[MaxN];
int main() {
	int i, j;
	cin >> h >> w;
	for(i = 0; i < h; i++) cin >> s[i];
	for(i = 0; i < h; i++) {
		for(j = 0; j < w; j++) a[s[i][j] - 'a'] ++;
	}
	
	int cnt = 0, cnt1 = 0;
	for(i = 0; i < 26; i++) {
		if(a[i] % 4 == 2) cnt++;
		else {
			if(a[i] % 4 == 0) continue;
			if(h % 2 == 0 || w % 2 == 0) {
				if(a[i] % 2 != 0)
					return puts("No"), 0;
			} 
				else
					if(a[i] % 2 != 0) 
						if(++cnt1 > 1) return puts("No"), 0;	
		}
	}
	
	int t = 0;
	if(h % 2 == 1) t += w; if(w % 2 == 1) t += h;
	if(h % 2 == 1 && w % 2 == 1) t --;
	t /= 2;
	if(h % 2 == 0 && w % 2 == 0 && cnt) puts("No");
	else if(cnt > t) puts("No");
	else puts("Yes");
	return 0;
}



