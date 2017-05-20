#include<bits/stdc++.h>
#define N 1001234
using namespace std;
char s[N],t[N];
int n,a,b,l,r,i,j,k,w[N],nxt[N];
int main(){
	scanf("%d%d%d%d%d",&n,&a,&b,&l,&r);
	for(i=2,w[1]=b;i<=n;i++)w[i]=(w[i-1]+a)%(n);
	for(i=1;i<=n;i++){
		if(l<=w[i]&&w[i]<=r){
			if(w[i]&1)s[i]='T';
			else s[i]='A';
		}else{
			if(w[i]&1)s[i]='C';
			else s[i]='G';
		}
	}scanf("%s",t+1);
	for(i=2,j=0;t[i];i++){
		while(j&&t[i]!=t[j+1])j=nxt[j];
		nxt[i]=(j+=(t[i]==t[j+1])); 
	}
	int m=strlen(t+1);
	for(i=1,j=k=0;s[i];i++){
		while(j&&t[j+1]!=s[i])j=nxt[j];
		if((j+=(t[j+1]==s[i]))==m)
			++k;
	}
	cout<<k;
	return 0;
}
