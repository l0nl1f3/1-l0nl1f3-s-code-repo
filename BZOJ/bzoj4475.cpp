#include<bits/stdc++.h>
#define ll long long
int n,k,p=1000000007;
int f(int a,int n){
	int res=1;
	for(;n;n>>=1,a=(ll)a*a%p)
		if(n&1)res=(ll)res*a%p;
	return res;
}
int main(){
	std::cin>>n>>k;
	std::cout<<f(f(2,k),n);
}
