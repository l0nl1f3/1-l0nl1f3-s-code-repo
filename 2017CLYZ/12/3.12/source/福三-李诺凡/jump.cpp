#include<iostream>
#include<stdio.h>
using namespace std;
int t,i,x[1001],y[1001],head,tail,temp[1101][2201],answer[1101][2201]={},queue[4844401][2];
bool temp1=1,temp2=1;
const int step[8][2]={{1,2},{2,1},{1,-2},{2,-1},{-1,2},{-2,-1},{-2,1},{-1,-2}};
int abs (int x)
{
	return x>0?x:-x;
}
int main ()
{
	freopen("jump.in","r",stdin);
	freopen("jump.out","w",stdout);
	scanf("%d",&t);
	for (i=1;i<=t;i++)
	scanf("%d %d",&x[i],&y[i]);
	for (i=1;i<=t;i++)
	if (x[i]!=y[i])
	temp1=0;
	for (i=1;i<=t;i++)
	if (y[i]!=0)
	temp2=0;
	if (temp1)
	for (i=1;i<=t;i++)
	switch (abs(x[i]))
	{
		case 0:
			putchar('0');
			putchar('\n');
			break;
		case 1:case 3:
			putchar('0');
			putchar('\n');
			break;
		case 2:
			putchar('0');
			putchar('\n');
			break;
		default:
			printf("%d\n",(abs(x[i])-1)/3*2+2);
	}
	else
	if (temp2)
	for (i=1;i<=t;i++)
	switch (abs(x[i]))
	{
		case 0:
			putchar('0');
			putchar('\n');
			break;
		case 1:
			putchar('3');
			putchar('\n');
			break;
		default:
			printf("%d\n",(abs(x[i])-2)/4*2+abs(x[i])%2+2);
	}
	else
	{
		for (head=1,tail=1;head<=tail;head++)
		for (i=0;i<8;i++)
		if ((queue[head][0]+step[i][0]!=0||queue[head][1]+step[i][1]!=0)&&abs(queue[head][0]+step[i][0])<=1100&&abs(queue[head][1]+step[i][1])<=1100&&answer[queue[head][0]+step[i][0]][queue[head][1]+step[i][1]]==0)
		{
			answer[queue[head][0]+step[i][0]][queue[head][1]+step[i][1]]=answer[queue[head][0]][queue[head][1]]+1;
			tail++;
			queue[tail][0]=queue[head][0]+step[i][0];
			queue[tail][1]=queue[head][1]+step[i][1];
		}
		for (i=1;i<=t;i++)
		printf("%d\n",answer[x[i]][y[i]]);
	}
	return 0;
}
