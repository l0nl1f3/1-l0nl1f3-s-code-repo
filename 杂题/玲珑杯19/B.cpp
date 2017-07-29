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
const int MaxN = 201234;
int a[MaxN];  

int qmax(int l, int r){
	int i = l;
	for(l; l <= r; l++)
		if(a[l] > a[i]) i = l;
	return i;			
}

int qmin(int l, int r){
	int i = l;
	for(l; l <= r; l++)
		if(a[l] < a[i]) i = l;
	return i;			
}

int n, K;
int main() {  
	int i, j, k, x, y, sum = 0;
	n = inp(); K = inp() + 1;
	x = y = 1;
	for(i = 1, j = 1; j <= n; j++){
      	scanf("%d",&a[j]);  
      	if(a[j]>a[x]) for(x = j; a[j] - a[y] >= K; i = y + 1, y = qmin(i , j)); 
        else if(a[j]<a[y])
					  for(y = j; a[x] - a[j] >= K; i = x + 1, x = qmax(i, j));  
        sum += j - i + 1;  
    }  
    cout << sum << endl;
  	return 0;  
}  


