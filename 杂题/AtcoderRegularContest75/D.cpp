#include<bits/stdc++.h>
using namespace std;
#define N 101234
#define ll long long
int n,i,h[N],a,b;
bool chk(ll o){
	int c=a-b;
	ll d=0;
	for(i=1;i<=n;i++){
		ll x=h[i]-o*b;	
		if(h[i]/b+3<o)x=0;
		d+=max((x+c-1)/c,0ll);
	}
	return d<=o;
}
int main(){
	int i,j,k=0;
	scanf("%d%d%d",&n,&a,&b);
	for(i=1;i<=n;i++)scanf("%d",h+i);
	ll l=1,r=0,o,ans;
	for(i=1;i<=n;i++)r+=h[i]/a+1;
	for(;l<=r;){
		o=(l+r)/2;
		if(chk(o)){
			ans=o;
			r=o-1;
		}else l=o+1;
	} 
	cout<<ans;
	return 0;
}
