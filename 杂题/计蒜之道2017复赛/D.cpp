#include<bits/stdc++.h>
using namespace std;
template<typename T>
inline bool cmin(T &a,const T &b){
	return a>b?a=b,1:0;
}
template<typename T>
inline bool cmax(T &a,const T &b){
	return a<b?a=b,1:0;
}
#define M 2000000
#define N 1000000
#define ll long long
struct edge{
	int to,nxt,v;
}e[M];int n,m,m1,m2,cnt,lst[N];
void ins(int a,int b,int c=0){
	e[++cnt]=(edge){b,lst[a],c};lst[a]=cnt;
}
#include<ext/pb_ds/priority_queue.hpp>

#define pa pair<ll,int>
using namespace __gnu_pbds;
typedef __gnu_pbds::priority_queue<pa,greater<pa>,pairing_heap_tag > heap;
heap::point_iterator id[N];
ll dis[N];
#define llinf 1e16
ll dijkstra(int s,int t){    
	heap q;
	memset(dis,0x3f,sizeof(dis));
    dis[s]=0;id[s]=q.push(make_pair(0,s));
    while(!q.empty()){
        int now=q.top().second;q.pop();
        for(int i=lst[now];i;i=e[i].nxt)
            if(e[i].v+dis[now]<dis[e[i].to]){
                dis[e[i].to]=e[i].v+dis[now];
                if(id[e[i].to]!=0)
                    q.modify(id[e[i].to],make_pair(dis[e[i].to],e[i].to));
                else id[e[i].to]=q.push(make_pair(dis[e[i].to],e[i].to));
            }
    }
    return dis[t]>=dis[0]?-1:dis[t];
}
int main(){
	int i,j,k,x,y,z;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++){
		scanf("%d",&k);
		for(j=1;j<=k;j++){
			scanf("%d",&x);
			ins(x,n+i+n);
			ins(i+n,x);
		}
	}
	scanf("%d",&m1);
	for(i=1;i<=m1;i++){
		scanf("%d%d%d",&x,&y,&z);
		ins(x,y,z);
		ins(y,x,z);
	}
	scanf("%d",&m2);
	for(i=1;i<=m2;i++){
		scanf("%d%d%d",&x,&y,&z);
		ins(x+n+n,y+n,z);
		ins(y+n+n,x+n,z);
	}
	scanf("%d%d",&x,&y);
	cout<<dijkstra(x,y);
	return 0;
}


