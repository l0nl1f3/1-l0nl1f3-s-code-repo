#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
const int N=100005,M=1166760,E=760745;
int n,m,i,j,k,x,y,z,d[N],a[N],u[E],v[E];ll A;
inline void read(int&a){char c;while(!(((c=getchar())>='0')&&(c<='9')));a=c-'0';while(((c=getchar())>='0')&&(c<='9'))(a*=10)+=c-'0';}
namespace Triple{
	int g[N],v[E],w[E],nxt[E],ed,st[N],en[N],m,q[M],val[M],tmp[N];
	inline void add(int x,int y){
		if(d[x]>d[y])swap(x,y);
		v[++ed]=y;nxt[ed]=g[x];g[x]=ed;
	}
	void solve(){
		for(i=1;i<=n;i++)if(g[i]){
			st[i]=m+1;
			for(j=g[i];j;j=nxt[j])tmp[q[++m]=v[j]]=w[j];
			en[i]=m;
			sort(q+st[i],q+m+1);
			for(j=st[i];j<=m;j++)val[j]=tmp[q[j]];
		}
		for(i=1;i<=n;i++)
			for(j=g[i];j;j=nxt[j]){
				k=v[j],x=st[i],y=st[k];
				while(x<=en[i]&&y<=en[k])if(q[x]==q[y]){
				  z=q[x];
				  A+=max(max(a[k],a[z]),a[i]);
				  x++,y++;
				}else q[x]<q[y]?x++:y++;
		}
	}
}
int main(){
	read(n);read(m);
	for(i=1;i<=n;i++)read(a[i]);
	for(i=1;i<=m;i++){
		read(u[i]);read(v[i]);
		d[u[i]]++;d[v[i]]++;
	}
	for(i=1;i<=m;i++)
	Triple::add(u[i],v[i]);
	Triple::solve();
	printf("%lld",A);
}
