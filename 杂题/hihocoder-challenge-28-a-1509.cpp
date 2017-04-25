#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a[100],f[100],n,i,j,k;
int main(){
	cin>>n;
	for(i=1;i<=n;i++)cin>>a[i];
	for(i=2;i<=n;i++){
		ll x=a[i-1],y=a[i];
		for(j=59;~j;j--){
			if((x>>j&1)^(y>>j&1)){
				f[j]=1;
				break;
			}
		}
	}
	for(i=0,j=1;i<=59;i++)j<<=!f[i];
	cout<<j;
	return 0; 
}
