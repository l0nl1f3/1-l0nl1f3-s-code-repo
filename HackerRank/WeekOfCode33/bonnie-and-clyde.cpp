#include<bits/stdc++.h>
using namespace std;
#define N 201234
#define M 401234
struct edge{  
 int u,v,n;  
}e1[M],e2[M];  
int f1[N],f2[N],cnt,cnt2;  
int n,m,q,tu,tv;  
void ins1(int u,int v){  
	e1[cnt].u=u,e1[cnt].v=v,e1[cnt].n=f1[u],f1[u]=cnt++;  
}  
void ins2(int u,int v){  
//printf("%d -> %d\n",u,v);
	e2[cnt2].u=u,e2[cnt2].v=v,e2[cnt2].n=f2[u],f2[u]=cnt2++;  
}  
int fa[N];  
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}  
void merge(int x,int y){fa[find(x)]=find(y);}  
int sum[N],tsum[N],dis[N];  
int lca_f[M],lca_b[M],lca_p[N],rid;  
int dminv[M][20],dminid[M][20];  
void dp(int u,int f,int dd,int tot){  
	dis[u]=dd,tsum[u]=tot+sum[u];  
	lca_f[++rid]=u,lca_b[rid]=dd,lca_p[u]=rid;  
	for(int i=f2[u];i!=-1;i=e2[i].n){  
		int v=e2[i].v;  
		if(v==f)continue;  
		dp(v,u,dd+1,tot+sum[u]);  
		lca_f[++rid]=u,lca_b[rid]=dd;  
	}  
}  
void makermq(){  
	rid=0;  
	dp(0,-1,0,0);  
	for(int i=1;i<=rid;i++)dminv[i][0]=lca_b[i],dminid[i][0]=i;  
	int maxj=(int)(log(rid+1.0)/log(2.0));  
	for(int j=1;j<=maxj;j++){  
		int maxi=rid+1-(1<<j);  
		for(int i=1;i<=maxi;i++){  
			if(dminv[i][j-1]<dminv[i+(1<<(j-1))][j-1]){  
				dminv[i][j]=dminv[i][j-1];  
				dminid[i][j]=dminid[i][j-1];  
			}else{  
				dminv[i][j]=dminv[i+(1<<(j-1))][j-1];  
				dminid[i][j]=dminid[i+(1<<(j-1))][j-1];  
			}  
		}  
	}  
}  
int lca(int x,int y){  
	if(lca_p[x]>lca_p[y])std::swap(x,y);  
	x=lca_p[x],y=lca_p[y];  
	int k=(int)(log(y-x+1.0)/log(2.0));  
	int xx=dminv[x][k]<dminv[y+1-(1<<k)][k]?dminid[x][k]:dminid[y+1-(1<<k)][k];  
	return lca_f[xx];  
}  
int dist(int x,int y){
	return dis[x]+dis[y]-2*dis[lca(x,y)];
}
int dfn[N],low[N],cid[N],stk[N],col[N],top,ind,cls,tmp;  
int cal[N];  
void dfs_cutpnt(int u,int f,int root){  
	dfn[u]=low[u]=++ind;  
	int cnt=0;  
	int flag=0;  
	for(int i=f1[u];i!=-1;i=e1[i].n){  
		int v=e1[i].v;  
		if(v==f&&!flag){flag=1;continue;}  
		if(!dfn[v]){  
			cnt++;  
			dfs_cutpnt(v,u,root);  
			if(low[v]<low[u])low[u]=low[v];  
			if(u==root&&cnt>1&&cid[u]==0)cid[u]=++cls,sum[cls]=1;  
			else if(u!=root&&low[v]>=dfn[u]&&cid[u]==0)cid[u]=++cls,sum[cls]=1;  
		}else if(dfn[v]<low[u])low[u]=dfn[v];  
	}  
}  
void dfs_tarjan(int u,int f){  
 low[u]=dfn[u]=++ind;  
 stk[++top]=u;  
 int flag=0;  
 for(int i=f1[u];i!=-1;i=e1[i].n){  
     int v=e1[i].v;  
     if(v==f&&!flag){flag=1;continue;}  
     if(!dfn[v]){  
         dfs_tarjan(v,u);  
         if(low[v]<low[u])low[u]=low[v];  
         if(low[v]>=dfn[u]){  
             sum[++cls]=1,col[u]=cls;  
             do{  
                 tmp=stk[top--],col[tmp]=cls,++sum[cls];  
                 if(cid[tmp]){ins2(cid[tmp],cls);ins2(cls,cid[tmp]);merge(cid[tmp],cls);}  
             }while(tmp!=v);  
             if(cid[u]){ins2(cid[u],cls);ins2(cls,cid[u]);merge(cid[u],cls);}  
         }  
     }else if(dfn[v]<low[u])low[u]=dfn[v];  
 }  
}  
int size;  
void makegraph(){  
 for(int i=0;i<n;i++)dfs_cutpnt(i,-1,i);
      memset(dfn,0,sizeof dfn);  
     memset(low,0,sizeof low);  
     memset(col,0,sizeof col);   
	 
     top=ind=0;   
 for(int i=0;i<n;i++)dfs_tarjan(i,-1);  
 for(int i=1;i<=cls;i++){  
     if(cal[find(i)]==0){  
         cal[find(i)]=1;  
         ins2(0,i);  
     }  
 }  
}  
int main(){  
	int i,j;
 	scanf("%d%d%d",&n,&m,&q);  
	memset(f1,-1,sizeof f1);  
	memset(f2,-1,sizeof f2);  
	for(i=0;i<=2*n;i++)fa[i]=i;  
	for(i=0;i<m;i++){  
		scanf("%d%d",&tu,&tv); --tu;--tv;
		ins1(tu,tv);  
		ins1(tv,tu);  
	}  
	makegraph();  
	makermq();  
	//for(i=0;i<n;i++)printf("%d ",cid[i]);puts("");
	//for(i=0;i<n;i++)printf("%d ",col[i]);puts("");
	//for(i=0;i<n;i++)printf("%d ",fa[i]);
	while(q--){  
		int i,j,k;
		scanf("%d%d%d",&i,&j,&k);  
		i--;j--;k--;
		i=cid[i]?cid[i]:col[i];  
		j=cid[j]?cid[j]:col[j];  
		k=cid[k]?cid[k]:col[k];
		
		if(find(i)!=find(j)||find(j)!=find(k)){
			puts("NO");continue;
		}
		
		//i=col[i];j=col[j];k=col[k];
		int ik=lca(i,k),jk=lca(j,k),ij=lca(i,j);
		if(ik!=k&&jk!=k){
			puts("NO");
		}else{
			if(ik==k^jk==k)
				puts("YES");
			else if(ij==k)puts("YES");
			else puts("NO");
		}	
	}  
	return 0;  
}  
