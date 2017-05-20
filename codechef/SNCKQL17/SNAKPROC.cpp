#include<bits/stdc++.h>
using namespace std;
int T,n;
char s[666];
int main(){
	int i,j=0;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		scanf("%s",s+1);
		int f=1;
		for(i=1,j=0;i<=n;i++){
			if(s[i]=='H'){
				if(j)f=0;
				++j;
			}
			if(s[i]=='T'){
				if(!j)f=0;
				--j;
			}
		}
		if(j)f=0;
		puts(f?"Valid":"Invalid");
	}
	return 0;
} 
