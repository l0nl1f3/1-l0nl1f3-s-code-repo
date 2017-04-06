#include<bits/stdc++.h>
using namespace std;
int s[88888],sn;
int main(){
	int i,j;long long k=0;
	for(scanf("%d",&i),s[0]=1e9;i--;s[++sn]=j){
		scanf("%d",&j);
		while(sn&&j>=s[sn])sn--;k+=sn;
	}	
	return printf("%lld\n",k),0;
} 
