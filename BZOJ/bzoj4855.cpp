// by fateice!!!
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<algorithm>
#define time QAQ
using namespace std;
int n,m,t,L[200010],R[200010],w[200010],g[200010],f[200010],l[200010],r[200010],x[200010],y[200010],T[200010],time;
long long ans[200010],s[200010],p;
inline void dfs(int i)
{
	if(g[i] || !i)
	  return;
	dfs(L[i]);
	dfs(R[i]);
	w[++p]=i;
}
inline void down(int i)
{
	x[i]+=y[i];
	y[l[i]]+=y[i];
	y[r[i]]+=y[i];
	y[i]=0;
}
inline void rotate(int i)
{
	down(f[i]);
	down(i);
	if(i==l[f[i]])
	  {
	   l[f[i]]=r[i];
	   f[r[i]]=f[i];
	   r[i]=f[i];
	   f[i]=f[r[i]];
	   f[r[i]]=i;
	   if(r[i]==l[f[i]])
	     l[f[i]]=i;
	   if(r[i]==r[f[i]])
	     r[f[i]]=i;
      }
    else
	  {
	   r[f[i]]=l[i];
	   f[l[i]]=f[i];
	   l[i]=f[i];
	   f[i]=f[l[i]];
	   f[l[i]]=i;
	   if(l[i]==l[f[i]])
	     l[f[i]]=i;
	   if(l[i]==r[f[i]])
	     r[f[i]]=i;
      }
}
inline void splay(int i)
{
	while(l[f[i]]==i || r[f[i]]==i)
	  if(l[f[f[i]]]!=f[i] && r[f[f[i]]]!=f[i])
	    rotate(i);
	  else
	    if(l[f[i]]==i && l[f[f[i]]]==f[i] || r[f[i]]==i && r[f[f[i]]]==f[i])
	      {
	       rotate(f[i]);
	       rotate(i);
	      }
	    else
	      {
	       rotate(i);
	       rotate(i);
	      }
	down(i);
}
inline void access(int i)
{
	int j,k;
	splay(i);
	x[i]++;
	y[l[i]]++;
	for(j=i;l[j];j=l[j]);
	splay(j);
	k=f[j];
	if(!k)
	  return;
	if(L[k]+R[k]-j)
	  splay(L[k]+R[k]-j);
	splay(k);
	if(L[k]==j && x[j]>=x[R[k]] || R[k]==j && x[j]>=x[L[k]])
	  {
	   if(r[k])
	     {
	      p-=L[k]+R[k]-j;
	      r[k]=0;
	      T[k]=time;
	     }
	   if(L[k]==j && x[j]>x[R[k]] || R[k]==j && x[j]>x[L[k]])
	     {
	      p+=j;
	      r[k]=j;
	      if(T[k])
	        {
	         s[T[k]+1]-=j;
	         s[time+1]+=j;
	         T[k]=0;
	        }
	     }
      }
    access(k);
}
int main()
{
	int i;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	  {
	   scanf("%d%d",&L[i],&R[i]);
	   w[L[i]]=w[R[i]]=1;
	   f[L[i]]=f[R[i]]=i;
      }
    for(i=1;i<=n;i++)
      if(!w[i])
        break;
    t=i;
    scanf("%d",&m);
    for(i=1;i<=m;i++)
      {
       scanf("%d",&w[i]);
       g[w[i]]=1;
      }
    p=m;
    dfs(t);
    p=0;
    for(i=n;i>0;i--)
      {
       time=i;
       x[w[i]]=1;
       access(w[i]);
       ans[i]=p;
      }
    for(i=1;i<=n;i++)
      if(T[i])
        {
         s[1]+=L[i];
         s[T[i]+1]-=L[i];
        }
    for(i=1;i<=m+1;i++)
      {
       s[i]+=s[i-1];
       printf("%lld\n",ans[i]+s[i]);
      }
	return 0;
}

