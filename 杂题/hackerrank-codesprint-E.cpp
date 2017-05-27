#include<bits/stdc++.h>
#define N 101234
using namespace std;
int n,x,a[N],g;
bool cmp(int a,int b){return (a&-a)>(b&-b);}
int main(){
	int i,j,k;
	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%d",a+i);
	sort(a+1,a+n+1,cmp);
	for(i=1;i<=n;i++)
		if(!(a[i]&g))
			g|=(a[i]&-a[i]);
	cout<<g;
	return 0;
}
