//orz hn-008
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#define rint register int
using namespace std;
typedef long long ll;
int read()
{
    char c;
    int x=0,flag=1;
    while((c=getchar())&&(c<'0'||c>'9'))
        if(c=='-')
            flag=-1;
    do x=x*10+c-'0';
    while((c=getchar())&&c>='0'&&c<='9');
    return x*flag;
}
const int maxn=200100;
int n,m,p1,p2;
int v[maxn];
namespace smt
{
#define lrt (rt<<1)
#define rrt (lrt|1)
#define s sm[rt]
#define sl sm[lrt]
#define sr sm[rrt]
#define mid ((l+r)>>1)
    struct segment_tree
    {ll sum;}sm[maxn<<2];
    void maintain(int rt)
    {s.sum=sl.sum+sr.sum;}
    void build(int rt,int l,int r)
    {
        s.sum=0;
        if(l==r)
            return;
        build(lrt,l,mid);
        build(rrt,mid+1,r);
    }
    void alter(rint rt,rint l,rint r,const int &aim,const int &v)
    {
        if(l==r)
            return (void)(s.sum+=v);
        if(aim<=mid)
            alter(lrt,l,mid,aim,v);
        else
            alter(rrt,mid+1,r,aim,v);
        maintain(rt);
    }
    ll query(rint rt,rint l,rint r,const int &aiml,const int &aimr)
    {
        if(aiml<=l&&r<=aimr)
            return s.sum;
        ll sum=0;
        if(aiml<=mid)
            sum+=query(lrt,l,mid,aiml,aimr);
        if(aimr>mid)
            sum+=query(rrt,mid+1,r,aiml,aimr);
        return sum;
    }
#undef lrt
#undef rrt
#undef s
#undef sl
#undef sr
#undef mid
}
namespace treap
{
#define ls tr[rt].lc
#define rs tr[rt].rc
#define nl nodes.first
#define nr nodes.second
    int root,size;
    struct treap
    {int lc,rc,key,sz,v,pos,addv,cnt;ll sum;}tr[maxn];
    void init()
    {root=size=0;}
    int newnod(int p)
    {
        size++;
        tr[size].lc=tr[size].rc=0;
        tr[size].key=rand();
        tr[size].sz=1;
        tr[size].v=0;
        tr[size].pos=p;
        tr[size].addv=tr[size].cnt=tr[size].sum=0;
        return size;
    }
    void maintain(rint rt)
    {
        tr[rt].sz=tr[ls].sz+tr[rs].sz+1;
        tr[rt].sum=tr[ls].sum+tr[rs].sum+tr[rt].cnt;
    }
    void pushdown(rint rt)
    {
        if(tr[rt].addv!=0)
        {
            if(ls!=0)
            {
                tr[ls].addv+=tr[rt].addv;
                tr[ls].cnt+=tr[rt].addv;
                tr[ls].sum+=(ll)tr[rt].addv*tr[ls].sz;
            }
            if(rs!=0)
            {
                tr[rs].addv+=tr[rt].addv;
                tr[rs].cnt+=tr[rt].addv;
                tr[rs].sum+=(ll)tr[rt].addv*tr[rs].sz;
            }
            tr[rt].addv=0;
        }
    }
    int merge(rint lrt,rint rrt)
    {
        if(lrt==0||rrt==0)
            return lrt+rrt;
        int rt;
        if(tr[lrt].key<tr[rrt].key)
        {
            pushdown(rt=lrt);
            rs=merge(rs,rrt);
        }
        else
        {
            pushdown(rt=rrt);
            ls=merge(lrt,ls);
        }
        maintain(rt);
        return rt;
    }
    pair<int,int> splitv(rint rt,rint v)
    {
        if(rt==0)
            return make_pair(0,0);
        pushdown(rt);
        pair<int,int> nodes;
        if(tr[rt].pos>v)
        {
            nodes=splitv(rs,v);
            rs=nodes.first;
            nodes.first=rt;
        }
        else
        {
            nodes=splitv(ls,v);
            ls=nodes.second;
            nodes.second=rt;
        }
        maintain(rt);
        return nodes;
    }
    pair<int,int> split(rint rt,rint k)
    {
        if(rt==0)
            return make_pair(0,0);
        pushdown(rt);
        pair<int,int> nodes;
        if(tr[ls].sz+1<=k)
        {
            nodes=split(rs,k-tr[ls].sz-1);
            rs=nodes.first;
            nodes.first=rt;
        }
        else
        {
            nodes=split(ls,k);
            ls=nodes.second;
            nodes.second=rt;
        }
        maintain(rt);
        return nodes;
    }
    void alter(int &rt,int v,int k,int flag)
    {
        pair<int,int> nodes=split(root,k);
        if(flag==0&&nr!=0)
        {
            tr[nr].addv+=p1;
            tr[nr].cnt+=p1;
            tr[nr].sum+=(ll)p1*tr[nr].sz;
        }
        if(nl!=0)
        {
            tr[nl].addv+=p2;
            tr[nl].cnt+=p2;
            tr[nl].sum+=(ll)p2*tr[nl].sz;
        }
        rt=merge(nl,nr);
    }
    void travel(int rt)
    {
        pushdown(rt);
        if(ls!=0)
            travel(ls);
        if(rs!=0)
            travel(rs);
        int p=tr[rt].pos<0?-tr[rt].pos:tr[rt].pos;
        smt::alter(1,1,n,p,tr[rt].cnt);
    }
    void dec(int &rt,int k)
    {
        pair<int,int> nodes=split(root,k);
        if(nr!=0)
            travel(nr);
        root=nl;
    }
    void insert(int &rt,int p)
    {
        int cur=newnod(p);
        // size++;
        // tr[size].sz=1;
        // tr[size].key=rand();
        // tr[size].pos=p;
        rt=merge(rt,cur);
    }
    ll query(int &rt,int v)
    {
        pair<int,int> nodes=splitv(root,v);
        ll ans=tr[nr].sum;
        rt=merge(nl,nr);
        return ans;
    }
#undef ls
#undef rs
}
struct querys
{int l,r;}que[maxn];
bool operator < (const querys &a,const querys &b)
{return a.l>b.l;}
int head[maxn],cnt;
struct edge
{int next,to,id;}seg[maxn];
void add_seg(int u,int v,int id)
{
    seg[++cnt]=(edge){head[u],v,id};
    head[u]=cnt;
}
int st[maxn],top,rev[maxn];
int cmp(const int &a,const int &b)
{return v[a]>v[b];}
ll ans[maxn];
int main()
{
    n=read(),m=read(),p1=read(),p2=read();
    for(int i=1;i<=n;i++)
        v[i]=read(),rev[i]=-v[i];
    for(int i=1;i<=m;i++)
        que[i].l=read(),que[i].r=read();
    for(int i=1;i<=m;i++)
        add_seg(que[i].l,que[i].r,i);
    for(int i=n;i>=1;i--)
    {
        if(top>0)
        {
            int p=lower_bound(st+1,st+top+1,i,cmp)-st-1;
            // if(p>top) p--;
            treap::alter(treap::root,p1,p-1,0);
        }
        while(top>0&&v[i]>=v[st[top]])
            top--;
        treap::dec(treap::root,top);
        treap::insert(treap::root,i);
        st[++top]=i;
        for(int j=head[i];j!=0;j=seg[j].next)
        {
            ans[seg[j].id]+=smt::query(1,1,n,1,seg[j].to);
            ans[seg[j].id]+=treap::query(treap::root,seg[j].to);
        }
    }


    treap::init();
    smt::build(1,1,n);
    memset(st,top=0,sizeof st);
    memset(head,cnt=0,sizeof head);
    for(int i=1;i<=m;i++)
        add_seg(que[i].r,que[i].l,i);
    for(int i=1;i<=n;i++)
    {
        if(top>0)
        {
            int p=lower_bound(st+1,st+top+1,i,cmp)-st-1;
            // if(p>top) p--;
            treap::alter(treap::root,p1,p-1,1);
        }
        while(top>0&&v[i]>=v[st[top]])
            top--;
        treap::dec(treap::root,top);
        treap::insert(treap::root,-i);
        st[++top]=i;
        for(int j=head[i];j!=0;j=seg[j].next)
        {
            ans[seg[j].id]+=smt::query(1,1,n,seg[j].to,n);
            ans[seg[j].id]+=treap::query(treap::root,-seg[j].to);
        }
    }
    for(int i=1;i<=m;i++)
        printf("%lld\n",ans[i]);
    return 0;
}
