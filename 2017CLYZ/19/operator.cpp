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
#define mp make_pair
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
#define N 501234
#define L 18
#define S0 11000000
int T,n,sn,ch[S0][2],s[S0],f[N],root[N],S[N];
void insert(int& ny,int x,int v){
    ny=++T;int y=ny;s[y]=s[x]+1;
    for(int i=L,c;~i;i--){
        ch[y][0]=ch[x][0];ch[y][1]=ch[x][1];
        s[ch[y][c=v>>i&1]=++T]=s[ch[x][c]]+1;
        y=ch[y][c];x=ch[x][c];
    }
}
int querymx(int y,int x,int v){
    int ans=0;
    for(int i=L,c;~i;i--){
        if(s[ch[y][(c=v>>i&1)^1]]-s[ch[x][c^1]])ans|=(1<<i),c^=1;
        x=ch[x][c];y=ch[y][c];
    }
    return ans;
}
int query(int y,int x,int v){
    int ans=0;
    for(int i=L,c;~i;i--){
        if(c=v>>i&1)ans+=s[ch[y][0]]-s[ch[x][0]];
        x=ch[x][c];y=ch[y][c];
    }
    return ans;
}
int kth(int y,int x,int k){
    int ans=0;
    for(int i=L;~i;i--){
        int k2=s[ch[y][0]]-s[ch[x][0]];
        if(k<=k2) x=ch[x][0],y=ch[y][0];
        else ans|=(1<<i),k-=k2,x=ch[x][1],y=ch[y][1];
    }
    return ans;
}
int main(){
    int p=0;
    for(int T=gi,l,r,x,op;T--;){
        op=gi;
        if(op==0)insert(root[++n],root[p],read()),f[n]=p,S[++sn]=p=n;
        else if(op==2)for(int i=gi;i--;p=f[p],sn--);
  	    else{
            l=gi,r=gi,x=gi;
            if(op==1) printf("%d\n",x^querymx(root[S[r]],root[S[l-1]],x));
            if(op==3) printf("%d\n",query(root[S[r]],root[S[l-1]],x+1));
            if(op==4) printf("%d\n",kth(root[S[r]],root[S[l-1]],x));
        }
    }
    return 0;
}
