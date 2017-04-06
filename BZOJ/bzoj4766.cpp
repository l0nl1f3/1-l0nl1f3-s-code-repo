#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,p;
ll fmul(ll n,ll m){
	ll res=0;
	for(;m;m>>=1,n=(n+n)%p)
		if(m&1)res=(res+n)%p;
	return res; 
}
ll fpow(ll n,ll m){
	ll res=1;
	for(;m;m>>=1,n=fmul(n,n))
		if(m&1)res=fmul(res,n)%p;
	return res; 
}
int main(){
	cin>>n>>m>>p;
	cout<<fmul(fpow(n,m-1),fpow(m,n-1));
}
