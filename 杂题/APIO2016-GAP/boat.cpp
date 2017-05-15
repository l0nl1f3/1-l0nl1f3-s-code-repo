#include<bits/stdc++.h>
#define p 1000000007
using namespace std;
//f[i][j]
//1~i school , school_{i-1} dispatch

int n,a[501],b[501]; 
vector<int>f;
int bit[1001234];
int qry(int r){
	int res=0;
	for(;r;r-=r&-r)res=(res+bit[r])%p;
	return res;
}
int mdf(int r,int d){
	for(;r<=f.size();r+=r&-r)
		bit[r]=(bit[r]+d)%p;
}
int main(){
	scanf("%d",&n);
	int i,j,k,x,y,z;
	for(i=1;i<=n;i++)scanf("%d%d",a+i,b+i);
	for(i=1;i<=n;i++)for(j=a[i];j<=b[i];j++)f.push_back(j);
	sort(f.begin(),f.end());
	f.erase(unique(f.begin(),f.end()),f.end());
	for(i=1;i<=n;i++){
		for(j=b[i];j>=a[i];j--){
			k=lower_bound(f.begin(),f.end(),j)-f.begin()+1;
			x=qry(k-1);
			mdf(k,(x+1)%p);
		}
	}
	printf("%d",qry(f.size()));
}
