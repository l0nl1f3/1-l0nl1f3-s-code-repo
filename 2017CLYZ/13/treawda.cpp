#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<string>
#include<cassert>
#include<cmath>
#include<vector>
#include<queue>
#include<stack>
#include<map>
#include<sstream>
#include<climits>
#define X first
#define Y second
#define DB double
#define lc now<<1
#define rc now<<1|1
#define MP make_pair
#define LL long long
#define pb push_back
#define sqr(_) ((_)*(_))
#define INF 0x3f3f3f3f
#define pii pair<int,int>
#define pdd pair<DB,DB>
#define ull unsigned LL
#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define zqf 998244353
using namespace std;
template<typename T>void Read(T& x)
{
    x=0;int flag=0,sgn=1;char c;
    while(c=getchar())
    {
        if(c=='-')sgn=-1;
        else if(c>='0'&&c<='9')x*=10,x+=c-'0',flag=1;
        else if(flag)break;
    }
    x*=sgn;
}
const int MAXN=2100;
int first[MAXN],next[MAXN],to[MAXN],e,n,k;
LL w[MAXN],a[MAXN];
LL ksm(LL x,LL K)
{
    LL res=1,d=x;
    while(K)
    {
        if(K&1)
            res=(res*d)%zqf;
        d=(d*d)%zqf;
        K>>=1;
    }
    return res;
}
LL dp[MAXN][MAXN],aa[MAXN],b[MAXN],c[MAXN],ans=0,fac[MAXN],facinv[MAXN],lover[MAXN];
void add(int u,int v,LL l)
{cerr<<"l="<<l<<endl;
    ++e;next[e]=first[u];first[u]=e;to[e]=v;w[e]=l;
    ++e;next[e]=first[v];first[v]=e;to[e]=u;w[e]=l;
}
struct FFT
{
    int N,rev[MAXN],size,STEP,inv;
    LL ohm[MAXN];
    void init(int size)
    {
        for(N=1,STEP=0;N<size;N<<=1,STEP++);
        memset(rev,0,sizeof(rev));
        for(int i=0;i<N;i++)
            for(int j=STEP;j>=0;j--)
                if((1<<j)&i)
                    rev[i]|=(1<<(STEP-j-1));//STEP-j-1!
        inv=ksm(N,zqf-2);
        ohm[0]=1;
        ohm[1]=ksm(3,(zqf-1)/N);cerr<<"g="<<ohm[1]<<endl;
        for(int i=2;i<=N;i++)
            ohm[i]=ohm[i-1]*ohm[1]%zqf;
    }
    void ntt(LL A[],int flag)
    {
        for(int i=0;i<N;i++)
            if(i<rev[i])
                swap(A[i],A[rev[i]]);
        for(int k=1;k<N;k<<=1)
            for(int i=0;i<N;i+=(k<<1))
                for(int j=0;j<k;j++)
                {
                    LL x=A[i+j],
                       y=A[i+j+k]*(flag==1?ohm[N/(k<<1)*j]:ohm[N-N/(k<<1)*j])%zqf;
                    A[i+j]=(x+y)%zqf;
                    A[i+j+k]=(x-y+zqf)%zqf;
                }
        if(flag==-1)
            for(int i=0;i<N;i++)
                A[i]=(A[i]*inv)%zqf;
    }
    void mul(LL A[],LL B[],LL C[])
    {
        ntt(A,1);
        ntt(B,1);
        for(int i=0;i<N;i++)
            C[i]=A[i]*B[i]%zqf;
		for(int i=0;i<N;i++)cout<<C[i]<<' ';puts("!@!");
        ntt(C,-1);
    }
}NTT;
void DFS(int u,int f,int fp)
{
    dp[u][0]=1;
    for(int i=1;i<=k;i++)
        dp[u][i]=(dp[u][i-1]*aa[u])%zqf;
    for(int i=first[u];i!=-1;i=next[i])
    {
        int v=to[i];
        if(v==f)continue;
        DFS(v,u,w[i]);
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        for(int j=0;j<=k;j++)
        {
            a[j]=facinv[j]*dp[v][j]%zqf;
            b[j]=facinv[j]*dp[u][j]%zqf;
        }
        NTT.mul(b,a,c);
        for(int j=0;j<=k;j++)
        {
            dp[u][j]=((1-w[i]+zqf)*dp[u][j]%zqf+(w[i]*fac[j]%zqf*c[j])%zqf)%zqf;
        }
    }
    cerr<<u<<","<<dp[u][1]<<endl;
    ans=(ans+dp[u][k]*(1-fp+zqf)%zqf)%zqf;
}
int main()
{
    freopen("tree.in","r",stdin);
    freopen("tree.out","w",stdout);
    memset(first,-1,sizeof(first));
    Read(n),Read(k);
    NTT.init(2*k+1);
    fac[0]=1;
    for(int i=1;i<=k;i++)
    {
        fac[i]=(fac[i-1]*i)%zqf;
        facinv[i]=ksm(fac[i],zqf-2);
    }
    facinv[0]=ksm(fac[0],zqf-2);
    for(int i=1;i<=n;i++)
        Read(aa[i]);
    for(int i=1;i<n;i++)
    {
        LL a,b,u,v;
        Read(u),Read(v),Read(a),Read(b);
        add(u,v,a*ksm(b,zqf-2)%zqf);
    }
    DFS(1,-1,0);
    cout<<ans<<endl;
}
