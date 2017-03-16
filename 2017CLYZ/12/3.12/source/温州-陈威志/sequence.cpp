#include<cstdio>
using namespace std;


int main()
{
  scanf("%d%d",&n,&m),minb[0]=2000000001;
  for(i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]);
  for(i=1;i<=n;i++)
    {
	  minb[i]=min(minb[i-1],b[i]);
	  for(j=i-1;j>=0;j--)
	    {
		  
		}
	}
}
