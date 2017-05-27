#include<bits/stdc++.h>
using namespace std;
#define N 301234
int n,k,b,m,h[N],p[N];
char s[N];
int main(){
	int i,j,k,ans=0;
	scanf("%s",s+1);n=strlen(s+1);
	scanf("%d%d%d",&k,&b,&m);
	for(i=p[0]=h[0]=1;i<=n;i++)
		p[i]=p[i-1]*b%m,
		h[i]=(h[i-1]*b+(s[i]-'0'))%m;
	//a_1*k^3+a_2*k^2+a_3*k+a_4
	//h_1=a_1
	//h_2=a_1*b+a_2
	//h_3=a_1*b^2+a_2*b+a_3 
	for(i=1;i+k-1<=n;i++){
		int l=i,r=i+k-1;
		ans=ans+(h[r]-h[l-1]*p[r-l+1]%m+m)%m;		
	}
	cout<<ans;
	return 0;
}
