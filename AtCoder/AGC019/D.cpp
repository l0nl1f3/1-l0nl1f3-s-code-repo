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

const int MaxN = 2333;

char a[MaxN], b[MaxN];
int n, ans = ~0U >> 1, x[MaxN], y[MaxN];
int A[MaxN], B[MaxN];

void solve() {
    int i, j;
    for(i = 0; i < n; i++) {
        for(A[i] = 0; b[(i + A[i]) % n] != '1'; ++A[i]);
        for(B[i] = 0; b[(i + B[i] + n) % n] != '1'; --B[i]);
    }
    for(int d = 0; d < n; d++) {
        for(i = 0; i < n; i++) x[i] = 0;
        for(i = j = 0; i < n; i++)
            if(a[i] != b[(i + d) % n]) {
                cmax(x[-B[i]], A[i] - d);
                ++j;
            }
        int L, R, res = 1e9;
        for(L = 0, R = n - 1; ~R; R--) cmin(res, L + R), cmax(L, x[R]);
        cmin(ans, 2 * res + d + j);
    }
}

int main() {
	int i;
	scanf("%s%s", a, b); n = strlen(a);
	if(*max_element(b, b + n) != '1') {
	    cout << (*max_element(a, a + n) != '1' ? 0 : -1) << endl;
	    return 0;
	}
	solve();
	reverse(a, a + n);
	reverse(b, b + n);
	solve();
	
	cout << ans << endl;
	return 0;
}



