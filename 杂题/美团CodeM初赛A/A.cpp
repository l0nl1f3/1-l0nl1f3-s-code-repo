#include<bits/stdc++.h>
#define FO(x) {freopen(#x".in","r",stdin);\
				freopen(#x".out","w",stdout);}
using namespace std;
typedef long long ll;
template<typename T>inline bool cmin(T &a,const T &b){	return a>b?a=b,1:0;}
template<typename T>inline bool cmax(T &a,const T &b){	return a<b?a=b,1:0;}
#define N 601234
int n;double u,v,c[N],d[N];
int main(){
	int i;
	scanf("%d%lf%lf",&n,&v,&u);
	for(i=1;i<=n;i++)scanf("%lf",c+i);
	for(i=1;i<=n;i++)scanf("%lf",d+i);
	double ans=0;
	for(i=1;i<=n;i++)
	for(int j=0;j<n;j++)ans+=u/(c[i]-d[i]*j-v);
	printf("%.3lf",ans); 
	return 0;
}	



