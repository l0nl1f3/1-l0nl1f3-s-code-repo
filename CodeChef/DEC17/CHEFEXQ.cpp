#include<bits/stdc++.h>
#define fir first
#define sec second
using namespace std;
typedef long long ll;
template<typename T>inline bool cmin(T &a,const T &b){ return a>b?a=b,1:0;}
template<typename T>inline bool cmax(T &a,const T &b){ return a<b?a=b,1:0;}
#define N 1001234
#define B 330
int n,ln,block,a[N];
int h[B][B],tag[N];   
int hm[B][N];vector<int>has[B];
int p[N],sz[N],L[N],R[N],bn; 
void Set(int p,int l,int r,int x){
	int i;
	for(auto z:has[p])hm[p][z]=0;has[p].clear();
	for(i=l;i<=r;i++)
		h[p][i]^=x;
	for(i=1;i<=sz[p];i++){
		h[p][i]^=tag[p];
		if(!hm[p][h[p][i]])
			has[p].push_back(h[p][i]);	
		hm[p][h[p][i]]++;
	}
	tag[p]=0;
}
void mdf(int l,int r,int x){
	int a,b,i;a=p[l];b=p[r];
	if(a==b){
		Set(a,l-L[a]+1,r-L[a]+1,x);
		return;
	}
	for(i=a+1;i<=b;i++)
		tag[i]^=x;
	Set(a,l-L[a]+1,sz[a],x);
}
int qry(int r,int x){
	int i,q=p[r],res=0;
	for(i=1;i<q;i++)
		res+=hm[i][x^tag[i]];
	for(i=1;i<=r-L[q]+1;i++)
		res+=((h[q][i]^tag[q])==x);
	return res; 
}
int main(){
	int i,j,k,q;
	scanf("%d%d",&n, &q);
	for(i=1;i<=n;i++)scanf("%d",a+i);
	block=sqrt(n)*1.6;
	for(i=1;i<=n;i++)
		p[i]=(i-1)/block+1;
	bn=(n-1)/block+1;
	for(i=1;i<=bn;i++)
		L[i]=(i-1)*block+1,R[i]=min(L[i]+block-1,n),sz[i]=R[i]-L[i]+1;
	int x=0;
	for(i=1;j=p[i],i<=n;i++){
		x^=a[i];
		h[j][i-L[j]+1]=x;
		if(!hm[j][x]++)
			has[j].push_back(x);
	}
	for(i=1;i<=q;i++){
		int op,i,x;
		scanf("%d%d%d", &op, &i, &x);
		if(op == 1) {
			mdf(i, n, a[i] ^ x);
			a[i] = x;			
		}else
			printf("%d\n", qry(i, x));
	}
	return 0;
}
