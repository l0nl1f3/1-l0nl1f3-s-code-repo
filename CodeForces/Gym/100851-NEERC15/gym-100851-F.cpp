#include<bits/stdc++.h>
#define FO(x) {freopen(#x".in","r",stdin);\
				freopen(#x".out","w",stdout);}
#define fir first
#define sec second
using namespace std;
typedef long long ll;
template<typename T>inline bool cmin(T &a,const T &b){ return a>b?a=b,1:0;}
template<typename T>inline bool cmax(T &a,const T &b){ return a<b?a=b,1:0;}
#define N 1234
#define M 2001234
#define inf 1e9
int n,w,x[N],y[N],d[N];
struct edge{int to,nxt,v;}e[M];int cnt,lst[N],dis[N];
void ins(int a,int b,int c){e[++cnt]=(edge){b,lst[a],c};lst[a]=cnt;}
void lnk(int a,int b,int c){ins(a,b,c);ins(b,a,c);}
void me(){memset(lst,0,sizeof(lst));cnt=0;} 
#include<ext/pb_ds/priority_queue.hpp>
namespace Dijkstra{
	#define pa pair<ll,int>
	#define mpa make_pair
	using namespace __gnu_pbds;
	typedef __gnu_pbds::priority_queue<pa,greater<pa>,pairing_heap_tag > heap;
	heap::point_iterator id[N];bool v[N];
	int dijkstra(int s,int t){
	    heap q;int i,b;
	    for(i=0;i<=n+1;i++)dis[i]=inf,id[i]=0;
	    dis[s]=0;id[s]=q.push(make_pair(0,s));
		while(!q.empty()){
			int c=q.top().second;q.pop();
	        for(i=lst[c],b;b=e[i].to,i;i=e[i].nxt){
				if(cmin(dis[b],dis[c]+e[i].v))
	                if(id[b]!=0)
	                    q.modify(id[b],mpa(dis[b],b));
	                else 
						id[b]=q.push(mpa(dis[b],b));
			}
	    }
	    return dis[t];
	}
}
using Dijkstra::dijkstra;
bool chk(double o){
	me();int i,j;
	for(i=1;i<=n;i++)
		if(x[i]<=o)lnk(0,i,0);
		else if(x[i]<=o+o)lnk(0,i,1);
	for(i=1;i<=n;i++)
		for(j=i+1;j<=n;j++){
			double d=sqrt((ll)(y[i]-y[j])*(y[i]-y[j])+(ll)(x[i]-x[j])*(x[i]-x[j]));
			if(d<=o)lnk(i,j,0);
			else if(d<=o+o)lnk(i,j,1);
		}
	for(i=1;i<=n;i++){
		if(w-x[i]<=o)lnk(i,n+1,0);
		else if(w-x[i]<=o+o)lnk(i,n+1,1);
	}
	return dijkstra(0,n+1)<=1;
}
int main(){
	FO(froggy);
	int i,j,k;
	scanf("%d%d",&w,&n);
	for(i=1;i<=n;i++)scanf("%d%d",x+i,y+i);
	double l=0,r=1e9;
	for(int _=0;_<=50;_++){
		double o=(l+r)/2;
		if(chk(o)){
			r=o;
		}
		else l=o;
	}
	chk(r);
	for(i=0;i<=n+1;i++)d[i]=dis[i];
	dijkstra(n+1,0);
	x[n+1]=w;
	for(i=0;i<=n+1;i++)
		for(j=lst[i];j;j=e[j].nxt){
			k=e[j].to;
			if(e[j].v==1&&d[i]+dis[k]+1==d[n+1]){
				if(i!=n+1&&k!=n+1&&i&&k)printf("%lf %lf\n",(x[i]+x[k])/2.0,(y[i]+y[k])/2.0);
				else printf("%lf %lf\n",(x[i]+x[k])/2.0,0.0+y[i]+y[k]);
				return 0;
			}
		}
	printf("%d %d",x[1],y[1]);
	return 0;
}


