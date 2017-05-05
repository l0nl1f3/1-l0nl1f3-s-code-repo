#include<bits/stdc++.h>
using namespace std;
#define N 1001234
char s[N];
int main(){
	int i,j,k;
	scanf("%s",s);
	for(j=k=0,i=strlen(s)-1;~i;i--){
		if(s[i]=='a')
			j+=k,k+=k;
		else k++;
		j=j%1000000007;
		k=k%1000000007;
	}
	cout<<j;
	return 0;
}
