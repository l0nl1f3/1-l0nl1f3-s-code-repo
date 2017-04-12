#include<bits/stdc++.h>
#define pb push_back
#define ll long long
#define infll 1001001001001001001LL
#define N 101234
using namespace std;
int k,m,d,A,n,t[N],b[N];ll f[N];vector<int>v;
struct SegT{
	ll mx[N*10];
	void ST(){for(int i=1;i<N*10;i++)mx[i]=-infll;}
	void cha(int x,int l,int r,int p,ll d){
		mx[x]=max(mx[x],d);
		if(l==r)return;
		else{
			if(p<=(l+r)/2)cha(x+x,l,(l+r)/2,p,d);
			else cha(x+x+1,(l+r)/2+1,r,p,d);
		}
	} 
	ll que(int x,int l,int r,int p,int q){
		if(p>r||q<l)return -infll;
		if(p<=l&&r<=q)return mx[x];
		return max(que(x+x,l,(l+r)/2,p,q),que(x+x+1,(l+r)/2+1,r,p,q));
	}
}zkw; 
int main(){
	scanf("%d%d%d%d%d",&k,&m,&d,&A,&n);
	v.pb(k%d);v.pb(m%d);
	t[0]=k;t[n+1]=m; 
	for(int i=1;i<=n;i++){
		scanf("%d%d",t+i,b+i); 
		v.pb(t[i]%d);
		//v.pb(b[i]%d);
	}
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	
	int p=v.size();zkw.ST();
	for(int i=0,j;i<=n+1;i++){
		j=lower_bound(v.begin(),v.end(),t[i]%d)-v.begin()+1;
		ll k=(ll)t[i]/d*A;
		if(i){
			ll a,b;
			a=zkw.que(1,1,p,j,p)-k;
			b=j-1?zkw.que(1,1,p,1,j-1)-k-A:-infll;
			f[i]=max(a,b)+::b[i]; 
		}
		zkw.cha(1,1,p,j,f[i]+k);
	}
	cout<<f[n+1]; 
	return 0;
}
	
