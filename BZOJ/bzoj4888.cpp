#include<bits/stdc++.h>
#define N 101234
using namespace std;
int n,a[N],s[N],bit[2201234],bin[N];
void mdf(int r){
	for(++r;r<=2201233;r+=r&-r)bit[r]^=1;
}
int qry(int r){
	int res=0;
	for(++r;r;r-=r&-r)res^=bit[r];
	return res;
} 
int main(){
	int i,j,p,q=0;
	for(bin[0]=i=1;i<=30;i++)bin[i]=bin[i-1]<<1;
	for(scanf("%d",&n),i=1;i<=n;i++)scanf("%d",a+i);
	for(p=0;p<=20;p++){
		memset(bit,0,sizeof(bit));
		for(i=1;i<=n;i++)s[i]=(s[i-1]+a[i])&(bin[p+1]-1);
		int ans=0;
		for(i=1;i<=n;i++){
			mdf(s[i-1]);
			int r=s[i]-bin[p],l=s[i]+1-bin[p+1];
			l=(l%bin[p+1]+bin[p+1])%bin[p+1];
			r=(r%bin[p+1]+bin[p+1])%bin[p+1];
			if(l<=r)ans^=qry(r)^qry(l-1);
			else ans^=qry(bin[p+1]-1)^qry(l-1)^qry(r);
		}
		if(ans)q|=bin[p];
	}
	printf("%d\n",q);
	return 0;
}
