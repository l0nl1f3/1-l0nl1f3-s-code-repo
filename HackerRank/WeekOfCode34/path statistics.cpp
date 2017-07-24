#include<bits/stdc++.h>
using namespace std;
#define SZ 666666
#define P 20
int n,m,a[SZ],fst[SZ],vb[SZ],nxt[SZ],as[SZ],M=0,fa[SZ];
void ad_de(int a,int b) {++M; nxt[M]=fst[a]; fst[a]=M; vb[M]=b;}
void adde(int a,int b) {ad_de(a,b); ad_de(b,a);}
int cc=0,st[SZ],ed[SZ],dfx[SZ];
void dfs(int x)
{
    st[x]=++cc; dfx[cc]=x;
    for(int e=fst[x];e;e=nxt[e])
    {
        int b=vb[e]; if(b==fa[x]) continue;
        fa[b]=x; dfs(b);
    }
    ed[x]=++cc; dfx[cc]=x;
}
typedef pair<int,int> pii;
int cc_=0,app[SZ],dep[SZ],lo2[SZ];
pii pp[SZ],minn[SZ][P];
void dfs_(int x)
{
    ++cc_; app[x]=cc_; pp[cc_]=pii(dep[x],x);
    for(int e=fst[x];e;e=nxt[e])
    {
        int b=vb[e]; if(b==fa[x]) continue;
        dep[b]=dep[x]+1; dfs_(b);
        pp[++cc_]=pii(dep[x],x);
    }
}
void build()
{
    for(int i=1;i<=cc_;i++) minn[i][0]=pp[i];
    for(int i=1;i<=cc_;i++)
    {
        int g=0;
        while((1<<g)<=i) ++g;
        lo2[i]=g-1;
    }
    for(int p=1;p<P;p++)
    {
        for(int i=1;i<=cc_;i++)
        {
            if(i+(1<<p)-1>cc_) break;
            minn[i][p]=min(minn[i][p-1],minn[i+(1<<(p-1))][p-1]);
        }
    }
}
int lca(int a,int b)
{
    a=app[a]; b=app[b];
    if(a>b) swap(a,b);
    int l2=lo2[b-a+1];
    return min(minn[a][l2],minn[b-(1<<l2)+1][l2]).second;
}
int bs,qn=0;
struct query {int l,r,m,k,id;} qs[SZ];
bool operator < (query a,query b)
{
    if(a.l/bs!=b.l/bs) return a.l/bs<b.l/bs;
    else return (a.l/bs)&1 ? a.r<b.r : a.r > b.r;
}
#define Addq(l_,r_,m_,k_,id_) ++qn, qs[qn].l=l_, qs[qn].r=r_, qs[qn].m=m_, qs[qn].k=k_	, qs[qn].id=id_;
int cov[SZ],coa[SZ];
int ans=0,anss[SZ];
 
const int MaxN = 501234;
 
vector<int>id[SZ], idM[SZ]; int cnt = 0, pos[SZ];
struct bit {
	int bit[MaxN];
	void erase(int a, int b){
	//	printf("erase %d\n", id[b][a]);
		for(int r = id[b][a]; r <= n; r += r & -r){
			bit[r]--;
		}
	}
	void insert(int a, int b){
	//	printf("insert %d\n", id[b][a]);
		for(int r = id[b][a]; r <= n; r += r & -r){ 
			bit[r]++;
		} 
	}
	int sum(int r){
		int ans = 0;
		for(;r;r -= r & -r)
			ans += bit[r];
		return ans;
	}
	int kth(int k){
		int l = 1, r = n, o, ans;
		while(l <= r){
			o = (l + r)/2;
			if(sum(o) >= k)
				ans = o, r = o - 1;
			else 
				l = o + 1; 
		}
	//	printf("%d %d\n", ans, pos[ans]);
		return pos[ans];
	}
}T; 
void edt(int q,int k)
{
	int p = a[q];
	
	if(coa[p]) T.erase(coa[p],p);
    coa[p]-=cov[q]&1;
	cov[q]+=k;
	coa[p]+=cov[q]&1;
	if(coa[p]) T.insert(coa[p],p); 
	/*
	ans-=(bool)coa[a[p]];
    coa[a[p]]-=cov[p]&1;
    cov[p]+=k;
    coa[a[p]]+=cov[p]&1;
    ans+=(bool)coa[a[p]];
    */
}
int inp() {
	int x = 0, f = 1;char ch;
	for(ch = getchar(); !isdigit(ch); ch = getchar())
		if(ch == '-') f = -1;
	for(; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	return x * f;
}
int ct[MaxN]; pii tp[MaxN]; int tn;
int main()
{
	n = inp(); m = inp();
	//bs=sqrt(n)+1;
    bs = n/sqrt(m/3.0);
	for(int i=1;i<=n;i++) as[i]=a[i] = inp();
    sort(as+1,as+1+n); int nn=unique(as+1,as+1+n)-as-1;
    for(int i=1;i<=n;i++) a[i]=lower_bound(as+1,as+1+nn,a[i])-as;
    for(int i=1;i<=nn;i++)id[i].push_back(0);
	for(int i = 1; i <= n; i++) tp[++tn] = make_pair(++ct[a[i]], a[i]),id[a[i]].push_back(i);
	sort(tp + 1, tp + tn + 1);
	for(int i = tn; i; i--)
		id[tp[i].second][tp[i].first]  = ++cnt, pos[cnt] = tp[i].second ;
	for(int i=1;i<n;i++)
    {
        int a,b;
        a = inp(); b = inp();
        adde(a,b);
    }
    dfs(1); dfs_(1); build();
    for(int i=1;i<=m;i++)
    {
        int a,b,p,k;
        a = inp(); b = inp(); k = inp();
        p=lca(a,b);
        if(st[a]>st[b]) swap(a,b);
        if(p==a) Addq(st[a],st[b],0,k,i)
        else Addq(ed[a],st[b],p,k,i)
    }
    sort(qs+1,qs+1+qn);
    int l=1,r=0;
    for(int i=1;i<=qn;i++)
    {
    	
        int ql=qs[i].l,qr=qs[i].r;
        while(l<ql) edt(dfx[l++],-1);
        while(l>ql) edt(dfx[--l],1);
        while(r>qr) edt(dfx[r--],-1);
        while(r<qr) edt(dfx[++r],1);
        if(qs[i].m) edt(qs[i].m,1);
        anss[qs[i].id]=T.kth(qs[i].k);
		if(qs[i].m) edt(qs[i].m,-1);
    }
    for(int i=1;i<=m;i++) printf("%d\n",as[anss[i]]);
}
