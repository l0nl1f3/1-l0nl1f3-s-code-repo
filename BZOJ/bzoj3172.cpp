#include<map>
#include<stack>
#include<queue>
#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<complex>
#include<iostream>
#include<assert.h>
#include<algorithm>
using namespace std;
#define inf 1001001001
#define infll 1001001001001001001LL
#define ll long long
#define dbg(vari) cerr<<#vari<<" = "<<(vari)<<endl
#define gmax(a,b) (a)=max((a),(b))
#define gmin(a,b) (a)=min((a),(b))
#define Ri register int
#define gc getchar()
#define il inline
il int read(){
	bool f=true;Ri x=0;char ch;while(!isdigit(ch=gc))if(ch=='-')f=false;while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=gc;}return f?x:-x;
}
#define gi read()
#define ig read()
#define FO(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
#define N 1234567
int n,len;
char s[N];
int sa[N],tsa[N],rk[N],trk[N],sum[N],h[N];
int w[N][21];
int adr[333],len_s[333];
int lg[N];
inline void getsa(int j) {
	for (int i=2;i<=len;i++)lg[i]=lg[i>>1]+1; 
    for (int i=1;i<=len;i++) sum[i]=0;
    for (int i=1;i<=len;i++) sum[rk[i+j]]++;
    for (int i=1;i<=len;i++) sum[i]+=sum[i-1];
    for (int i=len;i;i--) tsa[sum[rk[i+j]]--]=i;
      
    for (int i=1;i<=len;i++) sum[i]=0;
    for (int i=1;i<=len;i++) sum[rk[i]]++;
    for (int i=1;i<=len;i++) sum[i]+=sum[i-1];
    for (int i=len;i;i--) sa[sum[rk[tsa[i]]]--]=tsa[i];
}
  
inline int query(int l,int r) {
    int j,i=lg[r-l+1];
    //for (i=0,j=1;(j<<1)<=r-l+1;j<<=1,i++) ;
    return min(w[l][i],w[r-(1<<i)+1][i]);
}
  
int main() {
    scanf("%d",&n); len=0;
    for (int i=1;i<=n;i++) {
        scanf("%s",s+len+1); 
        adr[i]=len+1;
        len=strlen(s+1);
        s[++len]='^';
        len_s[i]=len-adr[i];
    }
    for (int i=1;i<=len;i++) sum[s[i]]++;
    for (int i=1;i<=255;i++) sum[i]+=sum[i-1];
    for (int i=len;i;i--) sa[sum[s[i]]--]=i;
    rk[sa[1]]=1;
    for (int i=2,p=1;i<=len;i++) {
        if (s[sa[i]]!=s[sa[i-1]]) p++;
        rk[sa[i]]=p;
    }
    for (int j=1;j<=len;j<<=1) {
        getsa(j);
        trk[sa[1]]=1;
        for (int i=2,p=1;i<=len;i++) {
            if (rk[sa[i]]!=rk[sa[i-1]]||rk[sa[i]+j]!=rk[sa[i-1]+j]) p++;
            trk[sa[i]]=p;
        }
        for (int i=1;i<=len;i++) rk[i]=trk[i];
    }
    for (int i=1,j=0;i<=len;i++) {
        if (rk[i]==1) continue;
        while (i+j<=len&&sa[rk[i]-1]+j<=len&&s[i+j]==s[sa[rk[i]-1]+j]) j++;
        h[rk[i]]=j;
        if (j) j--;
    }
    memset(w,127,sizeof w);
    for (int i=1;i<=len;i++) w[i][0]=h[i];
    for (int j=1,k=1;j<21;j++,k<<=1)
        for (int i=1;i<=len;i++)
            if (i+k<=len) w[i][j]=min(w[i][j-1],w[i+k][j-1]);
    for (int i=1;i<=n;i++) {
        int l=1,r=rk[adr[i]],mid,left=rk[adr[i]],right=rk[adr[i]];
        while (l<=r) {
            mid=l+r>>1;
            if (query(mid+1,rk[adr[i]])>=len_s[i]) 
                left=mid,r=mid-1; else l=mid+1;
        }
        l=rk[adr[i]],r=len;
        while (l<=r) {
            mid=l+r>>1;
            if (query(rk[adr[i]]+1,mid)>=len_s[i])
                right=mid,l=mid+1; else r=mid-1;
        }
        printf("%d\n",right-left+1);
    }
    return 0;
}
