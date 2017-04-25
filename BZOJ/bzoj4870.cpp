#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,p,k,r,a[101],b[101],c[101];
int main(){
	cin>>n>>p>>k>>r;
	a[0]++;a[k-1]++;
	b[0]=1;
	for(ll i=(ll)n*k;i;i>>=1){
		if(i&1){
			memset(c,0,sizeof(c));
			for(int i=0;i<k;i++)
				for(int j=0;j<k;j++)
					c[(i+j)%k]=(c[(i+j)%k]+(ll)a[i]*b[j])%p;
			for(int i=0;i<k;i++)b[i]=c[i];
		}
		memset(c,0,sizeof(c));
		for(int i=0;i<k;i++)
			for(int j=0;j<k;j++)
				c[(i+j)%k]=(c[(i+j)%k]+(ll)a[i]*a[j])%p;
		for(int i=0;i<k;i++)a[i]=c[i];
	}
	cout<<b[r];
} 
