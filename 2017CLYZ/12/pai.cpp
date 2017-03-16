#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<stack>
#include<list>
#include<queue>
#define eps 1e-6
#define INF 0x1f1f1f1f
#define PI acos(-1.0)
#define ll __int64
#define lson l,m,(rt<<1)
#define rson m+1,r,(rt<<1)|1
using namespace std;

/*
freopen("data.in","r",stdin);
freopen("data.out","w",stdout);
*/
#define M 55000
int n,lim,a[M],b[M],p[M],q[M]; //p[i]表示将b数组从小到大排序后的下标，
//q[i]表示b中的第i号元素与a中的q[i]号元素可能有冲突
int dp[M]; //dp[i]表示到达第i个数对时，a中能达到的最小值

bool cmp(int i,int j)
{
   return b[i]<b[j];  //按b数组排序，将下标对应交换
}

multiset<int>sbt; //多重集合容器，里面的存储结构是平衡二叉树
bool iscan(int m)
{
   int p=1,r=-1,le=0;
   ll sum=0;
   sbt.clear();

   for(int i=1;i<=n;i++)
   {
      sum+=b[i];
      while(sum>m)
         sum-=b[p++];
      if(p>i)
         return false; //说明有单个的值超过了m
      while(le<=r&&a[i]>=a[q[r]]) //去掉后面的小的
      {		 
         if(le<r)
            sbt.erase(dp[q[r-1]]+a[q[r]]);  //注意使得A的最大值和最小时，
                                          //可以以最大的a[i]为分界点
         r--;
      }
      q[++r]=i;
      if(le<r) //如果队列至少有两个元素
         sbt.insert(dp[q[r-1]]+a[q[r]]);
      while(le<=r&&q[le]<p)
      {
         if(le<r)
            sbt.erase(dp[q[le]]+a[q[le+1]]);
         le++;
      }
      dp[i]=a[q[le]]+dp[p-1];
      ll tmp=*sbt.begin();
      if(le<r&&tmp<dp[i]) //队列中至少有两个元素
         dp[i]=tmp;
   }
   return dp[n]<=lim;
}

int main()
{
   while(scanf("%d%d",&n,&lim)!=EOF)
   {
      for(int i=1;i<=n;i++)
      {
         scanf("%d%d",&a[i],&b[i]);
         q[i]=p[i]=i;
      }
      sort(p+1,p+n+1,cmp);
      for(int i=n,j=1;i>=1;i--)
         while(j<=n&&b[p[j]]<=a[i]) //将b中与a冲突的标记
               q[p[j++]]=i;         //将b全部用完，尽量去消耗下标值大的，
                                    //小的不用管了,找到最大冲突区间

      int le,ri,j=1;
      for(int i=1;i<=n;i=le,j++)  //有冲突一定要放在一起
      {
         a[j]=a[i],b[j]=b[i];
         for(le=i+1,ri=max(q[i],i);le<=ri;le++)
         {
            a[j]=max(a[j],a[le]);
            b[j]+=b[le];
            ri=max(ri,q[le]); //又产生了新的冲突
         }
      }
      
      n=j-1;//现在一共只有j-1组了
	for(int i=1;i<=n;i++)cout<<a[i]<<","<<b[i]<<endl;
      le=1,ri=((1<<31)-1);
      //printf("%d\n",ri);
      int m,ans;

      while(le<=ri)
      {
         m=(le+ri)>>1;
         if(iscan(m))
            ans=m,ri=m-1; //能否更小
         else
            le=m+1;//不行的话，增大
      }
      printf("%d\n",ans);
   }
   return 0;
}




