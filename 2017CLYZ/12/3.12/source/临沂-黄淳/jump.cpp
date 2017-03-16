#include <cstdio>
#include <cstring>
#define MAXN 1000000005

int T, x, y;

inline int read() {
	char ch = getchar();  int res = 0, flag = 1;
	while(ch < '0' || ch > '9') {if(ch == '-') flag = -1; ch = getchar();}
	while(ch <= '9' && ch >= '0') {res = res * 10 + ch - '0'; ch = getchar();}
	return res;
}

inline int max(int x, int y) {
	return (x > y ? x : y);
}

inline int abs(int x) {
	return (x > 0 ? x : -x);
}

int main() {
	freopen("jump.in", "r", stdin);
	freopen("jump.out", "w", stdout);

	T = read();
	while(T --) {
		x = read(), y = read();
		long long ans = 0;
		if(!y || !x) {
			int res = abs(x == 0 ? y : x);
			if(res == 1) {
				ans = 3;
			} else {
				int tmp = res % 4;
				ans = (res / 4 << 1) + tmp;
			}
		} else if(abs(x) == abs(y)) {
			int res = abs(x), tmp = (res - 1) / 3;
			if(res == 2) ans = 4;
			else ans = (tmp + 1) << 1;
		} else {
			if(abs(x) == abs(y) * 2 || abs(x) * 2 == abs(y)) {
				int tmp = max(abs(x), abs(y));
				ans = tmp >> 1;
			} else {
				ans = 3;
			}
		}
		
		printf("%d\n", ans);
	} 

	return 0;
}
