#include<map>
#include<stack>
#include<queue>
#include<cstdio>
#include<string>
#include<bitset>
#include<vector>
#include<cstring>
#include<complex>
#include<iostream>
#include<assert.h>
#include<algorithm>
using namespace std;
#define fi first
#define se second
#define il inline
#define pb push_back
#define ll long long
#define gc getchar()
#define inf 1001001001
#define Ri register int
#define Pii pair<int,int>
#define gmax(a,b) (a)=max((a),(b))
#define gmin(a,b) (a)=min((a),(b))
#define infll 1001001001001001001LL
#define dbg(vari) cerr<<#vari<<" = "<<(vari)<<endl
#define FO(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
il int read(){bool f=true;Ri x=0;char ch;while(!isdigit(ch=gc))if(ch=='-')f=false;while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=gc;}return f?x:-x;}
#define gi read()
#define N 123456
ll n,B,m;ll p,q,mul[N],lum[N],res[N];char a[N];
map<ll,int>mp;ll pm[N];
struct Q{int l,r,t;}b[N];
bool cmp(Q a,Q b){ll L=a.l/B,R=b.l/B;return L<R||(L==R&&a.r<b.r);}
int main(){
	FO(qaq);
	cin>>p;q=1;
	scanf("%s",a+1);n=strlen(a+1);m=gi;
	for(int i=1;i<=m;i++)b[i].l=gi,b[i].r=gi+1,b[i].t=i;
	if(p!=2&&p!=5){
		B=sqrt(n);
		for(int i=n;i;i--)(q=q*10%p),lum[i]=mul[i]=(mul[i+1]+(a[i]-'0')*q)%p;
		sort(b+1,b+m+1,cmp);sort(lum+1,lum+n+1);
		for(int i=1;i<=n+1;i++)mp[lum[i]]=i;
		for(int i=1;i<=n+1;i++)mul[i]=mp[mul[i]];
		int l=1,r=0;ll ans=0;
		for(int i=1,L,R;i<=m;i++){
			L=b[i].l,R=b[i].r;
			while(l<L)ans-=--pm[mul[l++]];
			while(l>L)ans+=pm[mul[--l]]++;
			while(r<R)ans+=pm[mul[++r]]++;
			while(r>R)ans-=--pm[mul[r--]];
			res[b[i].t]=ans;
		}
		for(int i=1;i<=m;i++)printf("%lld\n",res[i]);
	}else{
		for(int i=1;i<=n;i++){
			mul[i]=mul[i-1];lum[i]=lum[i-1];
			if((a[i]-'0')%p==0)mul[i]++,lum[i]+=i;	
		}
		for(int i=1,L,R;i<=m;i++){L=b[i].l,R=b[i].r-1;printf("%lld\n",lum[R]-lum[L-1]-(L-1)*(mul[R]-mul[L-1]));}
	}
	return 0;
}

