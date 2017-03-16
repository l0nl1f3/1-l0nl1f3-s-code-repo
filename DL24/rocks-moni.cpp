#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <windows.h>
#include <conio.h>
#include <vector>
using namespace std;
int n,m,k,l;
char mp[555][555];
short src[550][50]={};
short map[550][50]={},map2[550][550]={},nxt[5][550][550];
int posx[550][550]={},posy[550][550]={};
HWND me;
LPPOINT xu=new POINT();
bool a=0;
#define pdq(x,y) if(map[x][y]==1) cout<<"●"; \
                 else if(map[x][y]==2) cout<<"○";\
                 else
template<class T>
void biaoge(int x,int y,T map)
{
    system("cls");
    cout<<"　";
    for (int i=1;i<=x;i++)
        cout<<char('a'+(i-1))<<" ";
    cout<<endl<<char('A'+(1-1));
    pdq(1,1) cout<<"　";
    for (int i=2;i<x; i++)
        pdq(1,i) cout<<"　";
    pdq(1,x) cout<<"　";
    cout<<endl;
    for (int i=2;i<y;i++)
    {
        cout<<char('A'+(i-1));
        pdq(i,1) cout<<"　";
        for (int j = 2; j < x; j ++)
            pdq(i,j) cout<<"　";
        pdq(i,x) cout<<"　";
        cout<<endl;
    }
    cout<<char('A'+(y-1));
    pdq(y,1) cout<<"　";
    for (int i=2;i<x;i++)
        pdq(y,i) cout<<"　";
    pdq(y,x) cout<<"　";
    cout<<endl;
}
#undef pdq 
#define pb push_back
#define fi first
#define se second
typedef pair<int,int> pii;
vector<pii> vs; int cnt=0;
#define pdq(x,y) if(x==vs[0].fi&&y==vs[0].se) cout<<"☆";else\
				 if(map[x][y]==2) cout<<"●"; \
                 else
template<class T>
void biaoge2(int x,int y,T map)
{
    system("cls");
    cout<<"　";
    for (int i=1;i<=x;i++)
        cout<<char('a'+(i-1))<<" ";
    cout<<endl<<char('A'+(1-1));
    pdq(1,1) cout<<"　";
    for (int i=2;i<x; i++)
        pdq(1,i) cout<<"　";
    pdq(1,x) cout<<"　";
    cout<<endl;
    for (int i=2;i<y;i++)
    {
        cout<<char('A'+(i-1));
        pdq(i,1) cout<<"　";
        for (int j = 2; j < x; j ++)
            pdq(i,j) cout<<"　";
        pdq(i,x) cout<<"　";
        cout<<endl;
    }
    cout<<char('A'+(y-1));
    pdq(y,1) cout<<"　";
    for (int i=2;i<x;i++)
        pdq(y,i) cout<<"　";
    pdq(y,x) cout<<"　";
    cout<<endl;
}
#undef pdq 
#define pdq(x,y) if(map[x][y]) cout<<"●"; \
                 else
template<class T>
void biaoge3(int x,int y,T map)
{
    cout<<"　";
    for (int i=1;i<=x;i++)
        cout<<char('a'+(i-1))<<" ";
    cout<<endl<<char('A'+(1-1));
    pdq(1,1) cout<<"　";
    for (int i=2;i<x; i++)
        pdq(1,i) cout<<"　";
    pdq(1,x) cout<<"　";
    cout<<endl;
    for (int i=2;i<y;i++)
    {
        cout<<char('A'+(i-1));
        pdq(i,1) cout<<"　";
        for (int j = 2; j < x; j ++)
            pdq(i,j) cout<<"　";
        pdq(i,x) cout<<"　";
        cout<<endl;
    }
    cout<<char('A'+(y-1));
    pdq(y,1) cout<<"　";
    for (int i=2;i<x;i++)
        pdq(y,i) cout<<"　";
    pdq(y,x) cout<<"　";
    cout<<endl;
}
bool xia1(int x,int y)
{
    cout<<"请选择要连成一坨的。选完请按Esc\n";
    int mx,my;
    while(1)
    {
        while(!(GetAsyncKeyState(VK_LBUTTON)&0x8000f)&&!(GetAsyncKeyState(VK_ESCAPE)&0x8000f));
        if(GetAsyncKeyState(VK_ESCAPE)&0x8000f) return true;
        GetCursorPos(xu);
        ScreenToClient(me,xu);
        if(xu->x<posx[1][1]-8||xu->y<posy[1][1]-8||xu->x>posx[y][x]+15||xu->y>posy[y][x]+15) continue;
        long mindis=1000000;
        for(int i=1;i<=y;i++)
        {
            for(int j=1;j<=x;j++)
            {
                long dis=(xu->x-posx[i][j])*(xu->x-posx[i][j])
                        +(xu->y-posy[i][j])*(xu->y-posy[i][j]);
                if(dis<mindis)
                {
                    mx=i; my=j; mindis=dis;
                }
            }
        }
        if(map[mx][my]==1) {map[mx][my]=2; break;} else continue;
    }
    return false;
}
pii xia2(int x,int y)
{
    cout<<"请选择一个清真的地方。\n";
    int mx,my;
    while(1)
    {
        while(!(GetAsyncKeyState(VK_LBUTTON)&0x8000f));
        GetCursorPos(xu);
        ScreenToClient(me,xu);
        if(xu->x<posx[1][1]-8||xu->y<posy[1][1]-8||xu->x>posx[y][x]+15||xu->y>posy[y][x]+15) continue;
		long mindis=1000000;
        for(int i=1;i<=y;i++)
        {
            for(int j=1;j<=x;j++)
            {
                long dis=(xu->x-posx[i][j])*(xu->x-posx[i][j])
                        +(xu->y-posy[i][j])*(xu->y-posy[i][j]);
                if(dis<mindis)
                {
                    mx=i; my=j; mindis=dis;
                }
            }
        }
        if(map2[mx][my]==0) return pii(mx,my); else continue;
    }
}
template<class T>
bool gnxt(T nx,pii np)
{
	memcpy(nx,map2,sizeof(map2));
	for(int i=0;i<vs.size();i++)
	{
		pii nn=make_pair(vs[i].fi-vs[0].fi+np.fi,vs[i].se-vs[0].se+np.se);
		if(nn.fi<1||nn.fi>m||nn.se<1||nn.se>n||nx[nn.fi][nn.se]) return 0;
		nx[nn.fi][nn.se]=cnt;
	}
	return 1;
}
bool chk()
{
    for(int i=1;i<=l;i++)
     	for(int j=1;j<=k;j++)
       		if(map[i][j]==1) return 1;
    return 0;
}
#define SZ 666666
vector<pii> rs[SZ]; int px[SZ],py[SZ],pz[SZ];
int main()
{
    me=FindWindow("ConsoleWindowClass",NULL);
    scanf("%d%d%d%d",&n,&m,&k,&l);
    for(int i=1;i<=l;i++) scanf("%s",mp[i]+1);
    for(int i=1;i<=l;i++)
    {
    	for(int j=1;j<=k;j++) map[i][j]=(mp[i][j]=='X');
	}
	posx[0][1]=16;posy[0][1]=6;
    for(int i=1; i<=500; i++)
    {
        posx[i][1]=posx[i-1][1];
        posy[i][1]=posy[i-1][1]+16;
        for(int j=2; j<=500; j++)
        {
            posx[i][j]=posx[i][j-1]+16;
            posy[i][j]=posy[i][j-1];
        }
    }
    do
    {
    	++cnt;
    	do{biaoge(k,l,map);}while(!xia1(k,l));
        vs.clear();
        for(int i=1;i<=l;i++)
        	for(int j=1;j<=k;j++)
        		if(map[i][j]==2) vs.pb(pii(i,j));
        biaoge2(k,l,map);
        system("pause&cls");
        biaoge3(n,m,map2);
        pii pos=xia2(n,m);
        system("cls");
        for(int i=0;i<=3;i++)
        {
        	bool ok=gnxt(nxt[i],pos);
        	if(ok)
        	{
        		cout<<"Case "<<i<<":\n";
        		biaoge3(n,m,nxt[i]);
			}
			int wx=vs[0].fi,wy=vs[0].se;
			for(int j=0;j<vs.size();j++)
				vs[j]=make_pair(vs[j].se-wy+wx,wx-vs[j].fi+wy);
		}
		cout<<"Select or -1: ";
		int p; cin>>p;
		if(p==-1)
		{
			--cnt;
        	for(int i=1;i<=l;i++)
        		for(int j=1;j<=k;j++)
 		       		if(map[i][j]==2) map[i][j]=1;
			continue;
		}
        for(int i=0;i<vs.size();i++)
        	src[vs[i].fi][vs[i].se]=cnt;
		rs[cnt]=vs;
        for(int i=1;i<=l;i++)
        	for(int j=1;j<=k;j++)
        		if(map[i][j]==2) map[i][j]=0;
        memcpy(map2,nxt[p],sizeof(map2));
        px[cnt]=pos.fi; py[cnt]=pos.se; pz[cnt]=p;
    }while(chk());
    system("cls");
    int dx[]={1,0},dy[]={0,1},ans=0;
    for(int i=1;i<=l;i++)
    {
    	for(int j=1;j<=k;j++)
    	{
    		for(int g=0;g<2;g++)
    		if(src[i][j]&&src[i+dx[g]][j+dy[g]]&&src[i][j]!=src[i+dx[g]][j+dy[g]])
    			++ans;
		}
	}
	freopen("rocks-rec.txt","w",stdout); 
	printf("%d %d\n",cnt,ans);
	for(int i=1;i<=cnt;i++) printf("%d ",rs[i].size());puts("");
	for(int i=1;i<=cnt;i++)
	{
		for(int j=0;j<rs[i].size();j++)
			printf("%d %d ",rs[i][j].se,rs[i][j].fi);
		puts("");
	}
	for(int i=1;i<=cnt;i++)
		printf("%d %d %d\n",py[i],px[i],pz[i]);
    return 0;
}
