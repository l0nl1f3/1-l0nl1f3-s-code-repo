/**************************************************************
    Problem: 4542
    User: WerKeyTom_FTD
    Language: C++
    Result: Accepted
    Time:2576 ms
    Memory:5124 kb
****************************************************************/
 
#include<cstdio>
#include<algorithm>
#include<cmath>

#define FO(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
#define fo(i,a,b) for(i=a;i<=b;i++)
#define fd(i,a,b) for(i=a;i>=b;i--)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
int belong[maxn],s[maxn],cnt[maxn],ans[maxn];
ll num[maxn],b[maxn];
struct dong{
    int l,r,id;
} ask[maxn];
bool operator <(dong a,dong b){
    if (belong[a.l]<belong[b.l]) return 1;
    else if (belong[a.l]==belong[b.l]&&a.r<b.r) return 1;
    else return 0;
}
int i,j,k,l,r,n,m,c,now;
ll t,p,q;
char ch;
ll qsc(ll x,ll y){
    if (!y) return 0;
    ll t=qsc(x,y/2);
    t=(t+t)%p;
    if (y%2) t=(t+x)%p;
    return t;
}
ll qsm(ll x,int y){
    if (!y) return 1;
    ll t=qsm(x,y/2);
    t=qsc(t,t);
    if (y%2) t=qsc(t,x);
    return t;
}
void gcd(ll a,ll b,ll &x,ll &y){
    if (!b){
        x=1;
        y=0;
        return;
    }
    else{
        gcd(b,a%b,x,y);
        swap(x,y);
        y-=x*(a/b);
    }
}
ll getny(ll a,ll b){
    ll x,y;
    gcd(a,b,x,y);
    x=(x%b+b)%b;
    return x;
}
int main(){
    FO(qaq);
	scanf("%lld",&p);
    ch=getchar();
    while (ch<'0'||ch>'9') ch=getchar();
    s[n=1]=ch-'0';
    while (1){
        ch=getchar();
        if (ch<'0'||ch>'9') break;
        s[++n]=ch-'0';
    }
    c=floor(sqrt(n));
    fo(i,1,n) belong[i]=(i-1)/c+1;
    scanf("%d",&m);
    fo(i,1,m) scanf("%d%d",&ask[i].l,&ask[i].r),ask[i].id=i;
    //printf("%d\n",clock());
    sort(ask+1,ask+m+1);
    if (p!=2&&p!=5){
        q=getny(10,p);
        t=qsm(q,n);
        fd(i,n,1){
            b[i]=num[i]=(ll)(num[i+1]+(ll)s[i]*t%p)%p;
            t=t*10%p;
        }
        sort(b+1,b+n+2);
        l=unique(b+1,b+n+2)-b-1;
        fo(i,1,n+1) num[i]=lower_bound(b+1,b+l+1,num[i])-b;
    }
    //printf("%d\n",clock());
    l=r=1;
    cnt[num[1]]++;
    cnt[num[2]]++;
    if (p==2&&s[1]%2==0) now++,t++;
    else if (p==5&&s[1]%5==0) now++,t++;
    else if (p!=2&&p!=5&&s[1]%p==0) now++;
    fo(i,1,m){
        while (l<ask[i].l){
            if (p==2){
                now-=t;
                if (s[l]%2==0) t--;
            }
            else if (p==5){
                now-=t;
                if (s[l]%5==0) t--;
            }
            else{
                cnt[num[l]]--;
                now-=cnt[num[l]];
            }
            l++;
        }
        while (l>ask[i].l){
            l--;
            if (p==2){
                if (s[l]%2==0) t++;
                now+=t;
            }
            else if (p==5){
                if (s[l]%5==0) t++;
                now+=t;
            }
            else{
                now+=cnt[num[l]];
                cnt[num[l]]++;
            }
        }
        while (r>ask[i].r){
            if (p==2){
                if (s[r]%2==0) now-=(r-l+1),t--;
            }
            else if (p==5){
                if (s[r]%5==0) now-=(r-l+1),t--;
            }
            else{
                cnt[num[r+1]]--;
                now-=cnt[num[r+1]];
            }
            r--;
        }
        while (r<ask[i].r){
            r++;
            if (p==2){
                if (s[r]%2==0) now+=(r-l+1),t++;
            }
            else if (p==5){
                if (s[r]%5==0) now+=(r-l+1),t++;
            }
            else{
                now+=cnt[num[r+1]];
                cnt[num[r+1]]++;
            }
        }
        ans[ask[i].id]=now;
    }
    fo(i,1,m) printf("%d\n",ans[i]);
}

