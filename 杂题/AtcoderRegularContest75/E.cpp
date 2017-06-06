#include<bits/stdc++.h>
using namespace std;
#define N 201234
#define ll long long
map<ll,int>id;
ll bit[N];
int n,k,a[N];ll s[N],sb[N],sd[N];
int main(){
	int i,j=n;
	ll ans=0;
	scanf("%d%d",&n,&k);
	for(i=1;i<=n;i++)scanf("%d",a+i),s[i]=s[i-1]+a[i];
	for(i=1;i<=n;i++)sb[i]=s[i]=sd[i]=s[i-1]+a[i]-k;
	sort(sb+1,sb+n+1);
	int ln=unique(sb+1,sb+n+1)-sb-1;
	for(i=1;i<=ln;i++)id[sb[i]]=i;
	for(i=1;i<=n;i++)s[i]=id[s[i]];
	for(i=1;i<=n;i++){
		for(j=s[i];j;j-=j&-j)ans+=bit[j];
		for(j=s[i];j<=ln;j+=j&-j)bit[j]++;
		ans+=sd[i]>=0; 
	}
	cout<<ans;
	return 0;
}
