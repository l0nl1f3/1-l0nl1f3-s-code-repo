# include <math.h>
# include <stdio.h>
# include <string.h>
# include <algorithm>
// # include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
const int M = 5e5 + 10;
const int mod = 1e9+7;

# define FO_OPEN 1
# define RG register
# define ST static

namespace CommonMath {
	inline int gmin(int a, int b) {
		return a<b?a:b;
	}
	inline int gmax(int a, int b) {
		return a>b?a:b;
	}
	inline int gabs(int a) {
		return a>0?a:-a;
	}
}

using namespace CommonMath;

int x, y;

int g[] = {3, 2, 3, 4, 3, 4};
inline int getnum1(int s) {
	// 5-3, 6-2, 7-3, 8-4, 9-3, 10-4
	// 11-5, 12-4, 13-5, 14-6, 15-5, 16-6
	int id1 = (s-5)/6, id2 = (s-5)%6;
	return g[id2] + id1*2;
}

int h[] = {3, 2, 3, 4};
int h2[] = {2, 3, 4, 3};
inline int getnum2(int x, int y) {
	// make x
	int id1 = (x-3)/4, id2 = (x-3)%4;
	if(y&1) return h2[id2] + id1*2;
	else return h[id2] + id1*2;
}

int main() {
	FO_OPEN ? freopen("jump.in", "r", stdin), freopen("jump.out", "w", stdout) : 0;
	
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &x, &y);
		x = abs(x), y = abs(y);
		if(x == 0 && y == 0) {
			puts("0");
			continue;
		}
		double slop = atan2(y, x);
		if(0.5 <= slop && slop <= 2) {
			// x, x-1, x, x+1
			if(x == 1 && y == 1) {
				puts("2");
				continue;
			}
			if((x == 1 && y == 2) || (x == 2 && y == 1)) {
				puts("1");
				continue;
			}
			if(x == 2 && y == 2) {
				puts("4");
				continue;
			}
			printf("%d\n", getnum1(x+y));
		} else {
			if(x < y) swap(x, y);
			if(x == 1 && y == 0) {
				puts("3");
				continue;
			}
			if(x == 2 && y == 0) {
				puts("2");
				continue;
			}
			printf("%d\n", getnum2(x, y));
		}
	}
	return 0;
}




