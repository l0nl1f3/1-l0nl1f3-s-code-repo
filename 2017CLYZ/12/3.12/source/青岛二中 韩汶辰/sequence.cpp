#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=100100;
const ll inf=(ll)1000000007*(ll)1000000007;
ll b[N],a[N],mxl[22][N],mxr[22][N],mnf[N],f[N],sum[N],m,mb[N],ma[N];
int to[N],n,tp,yes[N],can[N];
void cdq(int l,int r,int dep,int flag)
{
    if(l==r)return;
	int mid=(l+r)>>1,i,j,k,fl;
	ll res=inf;
	cdq(l,mid,dep+1,flag);
	if(!flag)
	{
	    mxr[dep][mid]=0;
	    for(i=mid+1;i<=r;i++)mxr[dep][i]=max(mxr[dep][i-1],a[i]);
	    mxl[dep][mid+1]=mxl[dep][mid]=0;
	    for(i=mid-1;i>=l;i--)mxl[dep][i]=max(mxl[dep][i+1],a[i+1]);
	}
	j=r;k=l-1;fl=0;
	for(i=r;i>mid;i--)//a[lef]>=b[righ]
	{
		if(!fl)j=to[i];
		else
		{
		    for(j--;((j>=to[i])&&(j>=l));j--)
			   if(res>f[j]+mxl[dep][j])res=f[j]+mxl[dep][j];
		    j++;
		}
		while((k<mid)&&(mxl[dep][k+1]>=mxr[dep][i]))
		{
			k++;
			//if(j<=k)fl=1;
			if((fl)&&(res>f[k]+mxl[dep][k]))res=f[k]+mxl[dep][k];
		}
		if((!fl)&&(j<=k))
		{
			fl=1;
			for(int p=max(j,l);p<=k;p++)
			   if(res>f[p]+mxl[dep][p])res=f[p]+mxl[dep][p];
		}
		if(f[i]>res)f[i]=res;
	}
	
	mnf[mid+1]=inf;
	for(i=mid;i>=l;i--)mnf[i]=min(mnf[i+1],f[i]);
	k=mid+1;
	for(i=mid+1;i<=r;i++)
	{
		if(to[i]>mid)break;
		while((k>l)&&(mxl[dep][k-1]<mxr[dep][i]))k--;
		f[i]=min(f[i],mnf[max(to[i],k)]+mxr[dep][i]);
	}
	cdq(mid+1,r,dep+1,flag);
}
bool che(ll res,bool flag)//<=res是否合法 
{
	int i,j;
	for(i=1,j=1;i<=tp;i++)
	{
		while((j<=i)&&(sum[i]-sum[j-1]>res))j++;
		to[i]=j-1;
	}
	f[0]=0;
    for(i=1;((i<=tp)&&(sum[i]<=res));i++)f[i]=max(f[i-1],a[i]);
	for(;i<=tp;i++)f[i]=inf;
	cdq(1,tp,1,flag);
	if(f[tp]<=m)return 1;
	return 0;
}
int main()
{
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	int i,j,k;bool fl=0;
	ll l,r,mid;
	cin>>n>>m;
	for(i=1;i<=n;i++)scanf("%I64d%I64d",&a[i],&b[i]);
	//找分界点
	mb[0]=inf;
	for(i=1;i<=n;i++)mb[i]=min(mb[i-1],b[i]);
	ma[n+1]=0;
	for(i=n;i;i--)ma[i]=max(ma[i+1],a[i]);
	for(i=1;i<n;i++)
	   if(mb[i]>ma[i+1])yes[i]=1;
	for(i=1;i<=n;i=j+1)
	{
		j=i;
		while((j<n)&&(!yes[j]))
		{
			j++;
			b[i]+=b[j];a[i]=max(a[i],a[j]);
		}
		can[i]=1;
	}
	tp=0;
	for(i=1;i<=n;i++)
	   if(can[i])a[++tp]=a[i],b[tp]=b[i];
	for(i=1;i<=tp;i++)sum[i]=sum[i-1]+b[i];
	l=1;r=sum[tp];
	//r=25;//debug
	ll ans=r;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(che(mid,fl))ans=mid,r=mid-1;
		else l=mid+1;
		fl=1;
	}
	cout<<ans<<endl;
	return 0;
}
