#include<bits/stdc++.h>
#define N 401234
using namespace std;
int read(){
    int x=0,f=1;char ch;
    for(ch=getchar();!isdigit(ch);ch=getchar())
        if(ch=='-')f=-1;
    for(;isdigit(ch);x=x*10+ch-'0',ch=getchar());
    return x*f;
}
int n,cn,pn,lb,sgn[N];long long ans;
struct circle{int x,y,r;}c[N];
struct line{int i,x,sgn;}p[N];
double sqr(double x){return x*x;}
bool cmp(line a,line b){
    return a.x<b.x;
} 
struct height{
    int i,k;
    double h(){
        return c[i].y+k*sqrt(sqr(c[i].r)-sqr(lb-c[i].x));
    }
};
bool operator<(height a,height b){
    return a.h()!=b.h()?a.h()<b.h():a.k<b.k;
}
set<height>s;
int main(){
    int i,j,k;
    for(n=read();n--;){
        i=read();j=read();k=read();
        c[++cn]=(circle){i,j,k};
        p[++pn]=(line){cn,i-k,1};
        p[++pn]=(line){cn,i+k,-1};
    }
    sort(p+1,p+pn+1,cmp);
    for(i=1;lb=p[i].x,j=p[i].i,i<=pn;i++){
        if(~p[i].sgn){
            set<height>::iterator it=s.upper_bound((height){j,1});
            sgn[j]=(it==s.end()?1:(it->k==1?sgn[it->i]*-1:sgn[it->i]));
            s.insert((height){j,1});    
            s.insert((height){j,-1});
        }else{
            s.erase((height){j,1});
            s.erase((height){j,-1});
        }
    }
    for(i=1;i<=cn;i++)ans=ans+(long long)sgn[i]*c[i].r*c[i].r;
    printf("%lld",ans);
    return 0;
}
