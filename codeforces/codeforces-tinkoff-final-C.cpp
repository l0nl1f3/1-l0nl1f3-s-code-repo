#include<bits/stdc++.h>
using namespace std;
int a[27],b[27],c[301234];
char as[301234],bs[301234];
int main(){
	int n,m,i,j,k,x,y;
	scanf("%s%s",as+1,bs+1);
	n=strlen(as+1);
	for(i=1;i<=n;i++)a[as[i]-'a']++,b[bs[i]-'a']++;
	j=0;k=25;y=2; 
	for(i=1;i<=n;i++){
		while(j<26&&!a[j])j++;
		while(k>=0&&!b[k])k--;
		if(y==2&&j>=k){
			if((i&1)^(n&1))y=1;
		}else y=0;
		if((i^y)&1)	
			--a[c[i]=j];
		else
			--b[c[i]=k];
	}
	for(i=1;i<=n;i++)cout<<char(c[i]+'a'); 
}
