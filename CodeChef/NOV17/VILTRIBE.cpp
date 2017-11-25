#include <bits/stdc++.h>
 
using namespace std;
 
const int MaxN = 101234;
 
int n, l[MaxN], r[MaxN]; char s[MaxN], a[MaxN], b[MaxN];
 
int main() {
	int T, i; scanf("%d", &T); while(T--) {
		scanf("%s", s + 1); int n = strlen(s + 1);
		a[0] = '.';
		for(i = 1; i <= n; i++) {
			if(s[i] == '.')
				a[i] = a[i - 1];
			else
				a[i] = s[i];
		}
		b[n + 1] = '.';
		for(i = n; i; i--) {
			if(s[i] == '.')
				b[i] = b[i + 1];
			else
				b[i] = s[i];
		}
		int ansa = 0, ansb = 0;
		for(i = 1; i <= n; i++) {
			if(a[i] == 'A') ansa += a[i] == b[i];
			if(a[i] == 'B') ansb += a[i] == b[i];
		}
		printf("%d %d\n", ansa, ansb);
	}
} 
