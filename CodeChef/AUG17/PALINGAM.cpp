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
const int MaxN = 500;

int cA[MaxN], cB[MaxN];
char a[MaxN], b[MaxN];
int main() {
	int i, T;
	T = inp();
	while(T--){
		scanf("%s%s", a, b);
		int n = strlen(a);
		
		memset(cA, 0, sizeof(cA));
		memset(cB, 0, sizeof(cB));
		
		int chkA = 0, chkB = 0, Aw = 0;
		for(i = 0; i < n; i++) cA[a[i] - 'a']++;
		for(i = 0; i < n; i++) cB[b[i] - 'a']++;
		for(i = 0; i < 26; i++)
			if(!(cA[i] * cB[i]))
				if(cA[i]){
					chkA++;
					if(cA[i] > 1) Aw = 1; 
				}
				if(cB[i]) 
					chkB++;
					
		if(!chkA && !chkB) {
			puts("B"); 
			continue;
		}
		if(!chkA || !chkB) {
			if(chkA) puts("A");
			else puts("B");
			continue;
		}
		if(Aw) {
			puts("A");
			continue;
		}
		if(chkB > 1) {
			puts("B");
			continue;
		}
		puts("B");
	}
	return 0;
}



