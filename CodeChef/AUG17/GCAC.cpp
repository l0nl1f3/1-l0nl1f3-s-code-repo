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
const int MaxN = 1234;
int T, n, m;
int q[MaxN][MaxN], os[MaxN], mjo[MaxN], chk[MaxN], ms[MaxN];

int main() {
	int i, j, T = inp();
	while(T--) {
		memset(chk, 0, sizeof(chk));
		n = inp(); m = inp();
		for(i = 1; i <= n; i++) ms[i] = inp();
		for(i = 1; i <= m; i++) os[i] = inp(), mjo[i] = inp();
		for(i = 1; i <= n; i++) {
			char ch[MaxN]; scanf("%s", ch + 1);
			for(j = 1; j <= m; j++) q[i][j] = ch[j] - '0';
		}
		
		LL ans = 0, can = 0;
		for(i = 1; i <= n; i++) {
			int cp = 0, cv = 0;
			for(j = 1; j <= m; j++)
				if(q[i][j]) 
					if(os[j] >= ms[i] && mjo[j]  > chk[j])
						if(os[j] > cv) 
							cv = os[j], cp = j;
			if(cp) {
				++can;
				chk[cp]++;
				ans += cv;
			}
		}
		
		int dot = 0;
		for(i = 1; i <= m; i++)
			dot += !chk[i];
		cout << can << " " << ans << " " << dot << endl;
	}
	return 0;
}



