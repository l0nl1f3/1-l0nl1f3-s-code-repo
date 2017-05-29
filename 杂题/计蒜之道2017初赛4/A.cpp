#include<bits/stdc++.h>
using namespace std;
int n,m,k;
int d1,d2,dc[101],dr[101];
int main(){
	int i,j;
	scanf("%d%d%d",&n,&m,&k);
	for(i=1;i<=k;i++){
		int d;scanf("%d%d",&d,&j);
		if(!d)dc[++d1]=j;
		else dr[++d2]=j;
	}dc[++d1]=n+1;
	dr[++d2]=m+1;
	sort(dc+1,dc+d1+1);
	sort(dr+1,dr+d2+1);
	int ans=0;
	for(i=1;i<=d1;i++)
		for(j=1;j<=d2;j++){
			int x=dc[i]-dc[i-1]-1,y=dr[j]-dr[j-1]-1;
			ans+=x*y/2;
		} 
	cout<<ans;
	return 0;
}

