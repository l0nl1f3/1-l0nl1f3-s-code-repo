#include<bits/stdc++.h>
using namespace std;
char o[101234];
int n,m,a[101234];
int main(){
	int i,j,k,ans=0;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		char zy[4];
		scanf("%s%d",zy,a+i);
		o[i]=zy[0];
	}
	for(k=0;(1<<k)<=m;k++);
	for(j=30;~j;j--){
		int p=0;
		for(i=1;i<=n;i++){
			if(o[i]=='A')p&=(a[i]>>j&1);
			if(o[i]=='X')p^=(a[i]>>j&1);
			if(o[i]=='O')p|=(a[i]>>j&1);
		}
		if(p)
			continue;
		p=1;
		for(i=1;i<=n;i++){
			if(o[i]=='A')p&=(a[i]>>j&1);
			if(o[i]=='X')p^=(a[i]>>j&1);
			if(o[i]=='O')p|=(a[i]>>j&1);
		}
		if(p&&(ans|(1<<j))<=m)
			ans|=(1<<j);
	}
	for(i=1;i<=n;i++){
		if(o[i]=='A')ans&=a[i];
		if(o[i]=='X')ans^=a[i];
		if(o[i]=='O')ans|=a[i];
	} 
	cout<<ans;
} 
