#include<bits/stdc++.h>
using namespace std;
template<typename T>
inline bool cmin(T &a,const T &b){
	return a>b?a=b,1:0;
}
template<typename T>
inline bool cmax(T &a,const T &b){
	return a<b?a=b,1:0;
}
#define N 101234
int prf[N],suf[N],n,a[N],b[N];
int main(){
	int i;
	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%d",b+i);
	for(i=1;i<=n;i++)scanf("%d",a+i);
	prf[0]=suf[n+1]=~0U>>1;
	for(i=1;i<=n;i++)(prf[i]=min(prf[i-1],a[i]));
	for(i=n;i;i--)(suf[i]=min(suf[i+1],a[i]));
	int ans=~0U>>1;
	for(i=1;i<=n;i++)cmin(ans,b[i]+min(prf[i-1],suf[i+1]));
	cout<<ans;
	return 0;
}

