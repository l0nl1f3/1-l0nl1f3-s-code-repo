#include<bits/stdc++.h>
#define N 1601234
#define inf (1<<30)
 
using namespace std;
set<int>s;
int n,m,id[N],d[N],x[N],op[N],cnt=1,ctn=-1;
int find(int x){
    int l,r,o;
    for(l=1,r=n+1;r-l>1;d[o=(l+r)/2]<=x?l=o:r=o);
    return l;
}
struct Segment_Tree{
    int mn[N],ans[N];
    void build(int o,int l,int r){
        mn[o]=inf;ans[o]=0;
        if(l==r)return;
        build(o+o,l,(l+r)/2);
        build(o+o+1,(l+r)/2+1,r);
    }
    int query(int o,int l,int r,int v){
        if(l==r)return mn[o]<v;
        if(v<mn[o+o+1])return query(o+o,l,(l+r)/2,v);
        else return ans[o]+query(o+o+1,(l+r)/2+1,r,v);
    }
    void modify(int o,int l,int r,int p,int v){
        if(l==r){
            mn[o]=v;return;
        }
        if(p<=(l+r)/2)modify(o+o,l,(l+r)/2,p,v);
        else modify(o+o+1,(l+r)/2+1,r,p,v);
        ans[o]=query(o+o,l,(l+r)/2,mn[o+o+1]);
        mn[o]=min(mn[o+o],mn[o+o+1]);
    }
    int query(int o,int l,int r,int a,int b,int &v){
        if(a<=l&&r<=b){
            int res=query(o,l,r,v);
            v=min(mn[o],v);
            return res;
        }
        int res=0;
        if(b>(l+r)/2) res+=query(o+o+1,(l+r)/2+1,r,a,b,v);
        if(a<=(l+r)/2)res+=query(o+o,l,(l+r)/2,a,b,v);
        return res;
    }
}t1,t2;
int find_i(){
    return *s.begin();
}
int find_x(){
    set<int>::iterator it=s.end();it--;
    return *it;
}
void query(int x,int v){
    int res=0;
    int v1=v;if(x!=1)res+=t1.query(1,1,n,1,x-1,v1);
    int v2=v;if(x!=n)res+=t2.query(1,1,n,1,n-x,v2);
    printf("%d\n",res+1);
}
void modify(int x,int v){
    t1.modify(1,1,n,x,v);
    t2.modify(1,1,n,n-x+1,v);
}
int main(){
    int i,j,k;
    for(scanf("%d",&m),i=1;i<=m;i++){
        scanf("%d",op+i);
        if(op[i]==1)scanf("%d",x+i),d[++n]=x[i];
    }
    sort(d+1,d+n+1);
    for(t1.build(1,1,n),t2.build(1,1,n),
    i=1;i<=m;i++){
        if(op[i]==1){
            j=find(x[i]);
            id[j]=++cnt;
            query(j,id[j]);
            modify(j,id[j]);
            s.insert(j);
        }       
        if(op[i]==2){
            j=find_i();
            query(j,id[j]);
            id[j]=--ctn;
            modify(j,id[j]);
        }
        if(op[i]==3){
            j=find_x();
            query(j,id[j]);
            id[j]=--ctn;
            modify(j,id[j]);
        }
        if(op[i]==4){
            j=find_i();
            s.erase(j);
            query(j,id[j]);
            id[j]=inf;
            modify(j,id[j]);
        }
        if(op[i]==5){
            j=find_x();
            s.erase(j);
            query(j,id[j]);
            id[j]=inf;
            modify(j,id[j]);
        }
    }
     
    return 0;
} 
