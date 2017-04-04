#include<bits/stdc++.h>
using namespace std;
#define p 19940417
#define i6 3323403
#define ll long long
int pfh(int r){return (ll)(r+1)*(r+r+1)%p*r%p*i6%p;}
int sum(int m,int n){
	int res=0;
	for(int i=1,j;i<=m;i=j+1){
		j=min(m,n/(n/i));
		res=(res+(ll)(n/i)*(j-i+1)%p*(i+j)%p*(p+1)/2%p)%p;
		if(res<0)res+=p; 
	}
	return res;
}
int main(){
	int n,m,i,j,k,q;
	cin>>n>>m;if(n<m)swap(n,m);
	q=((ll)n*n-sum(n,n))%p*(((ll)m*m-sum(m,m))%p)%p;
	q=((q-(ll)m*m%p*n%p+(ll)sum(m,n)*m%p)%p+(ll)sum(m,m)*n%p)%p; 
	if(q<0)q+=p;
	for(i=1;i<=m;i=j+1){
		j=min(n/(n/i),m/(m/i));j=min(m,j); 
		q=(q-(ll)(n/i)*(m/i)%p*(pfh(j)-pfh(i-1)+p)%p)%p;
		if(q<0)q+=p; 
	}
	return printf("%d",q),0;
}
