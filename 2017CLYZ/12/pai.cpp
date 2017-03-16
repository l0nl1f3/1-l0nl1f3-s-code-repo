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
int n,lim,a[M],b[M],p[M],q[M]; //p[i]��ʾ��b�����С�����������±꣬
//q[i]��ʾb�еĵ�i��Ԫ����a�е�q[i]��Ԫ�ؿ����г�ͻ
int dp[M]; //dp[i]��ʾ�����i������ʱ��a���ܴﵽ����Сֵ

bool cmp(int i,int j)
{
   return b[i]<b[j];  //��b�������򣬽��±��Ӧ����
}

multiset<int>sbt; //���ؼ�������������Ĵ洢�ṹ��ƽ�������
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
         return false; //˵���е�����ֵ������m
      while(le<=r&&a[i]>=a[q[r]]) //ȥ�������С��
      {		 
         if(le<r)
            sbt.erase(dp[q[r-1]]+a[q[r]]);  //ע��ʹ��A�����ֵ����Сʱ��
                                          //����������a[i]Ϊ�ֽ��
         r--;
      }
      q[++r]=i;
      if(le<r) //�����������������Ԫ��
         sbt.insert(dp[q[r-1]]+a[q[r]]);
      while(le<=r&&q[le]<p)
      {
         if(le<r)
            sbt.erase(dp[q[le]]+a[q[le+1]]);
         le++;
      }
      dp[i]=a[q[le]]+dp[p-1];
      ll tmp=*sbt.begin();
      if(le<r&&tmp<dp[i]) //����������������Ԫ��
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
         while(j<=n&&b[p[j]]<=a[i]) //��b����a��ͻ�ı��
               q[p[j++]]=i;         //��bȫ�����꣬����ȥ�����±�ֵ��ģ�
                                    //С�Ĳ��ù���,�ҵ�����ͻ����

      int le,ri,j=1;
      for(int i=1;i<=n;i=le,j++)  //�г�ͻһ��Ҫ����һ��
      {
         a[j]=a[i],b[j]=b[i];
         for(le=i+1,ri=max(q[i],i);le<=ri;le++)
         {
            a[j]=max(a[j],a[le]);
            b[j]+=b[le];
            ri=max(ri,q[le]); //�ֲ������µĳ�ͻ
         }
      }
      
      n=j-1;//����һ��ֻ��j-1����
	for(int i=1;i<=n;i++)cout<<a[i]<<","<<b[i]<<endl;
      le=1,ri=((1<<31)-1);
      //printf("%d\n",ri);
      int m,ans;

      while(le<=ri)
      {
         m=(le+ri)>>1;
         if(iscan(m))
            ans=m,ri=m-1; //�ܷ��С
         else
            le=m+1;//���еĻ�������
      }
      printf("%d\n",ans);
   }
   return 0;
}




