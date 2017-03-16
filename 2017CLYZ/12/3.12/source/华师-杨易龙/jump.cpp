#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
int t, x, y, pre1, pre2, pre3;
int b[40][40], dep;
int tx[8]= {1,1,2,2,-1,-1,-2,-2};
int ty[8]= {-2,2,-1,1,2,-2,1,-1};
void bfs()
{
    while(true)
    {
        ++dep;
        if(b[20+x][20+y]!=0)
        {
            printf("%d\n", pre1 + pre2 + pre3 + b[20 + x][20 + y] - 1);
            break;
        }
        for(int i=0; i<40; ++i)
            for(int j=0; j<40; ++j)
                if(b[i][j]==dep)
                    for(int k=0; k<8; ++k)
                        if(i+tx[k]>=0&&i+tx[k]<40&&j+ty[k]>=0&&j+ty[k]<40&&!b[i+tx[k]][j+ty[k]])
                            b[i+tx[k]][j+ty[k]]=dep+1;
    }
}

void work1()
{
    int alpha = x / 3;
    x %= 3;
    y = x;
    alpha *= 2;
    if (x == 0)
    {
        printf("%d\n", alpha);
        return ;
    }
    else if (x == 1)
    {
        alpha += 2;
        printf("%d\n", alpha);
        return ;
    }
    else if (x == 2)
    {
        if (alpha)
        {
            alpha -= 2;
            alpha += 4;
            printf("%d\n", alpha);
        }
        else
        {
            alpha = 4;
            printf("%d\n", alpha);
        }
        return ;
    }
}

void work2()
{
    int alpha = x / 4;
    alpha <<= 1;
    x %= 4;
    if (x == 0)
    {
        printf("%d\n", alpha);
        return ;
    }
    if (x == 2)
    {
        printf("%d\n", alpha + 2);
        return ;
    }
    if (x == 3)
    {
        printf("%d\n", alpha + 3);
        return ;
    }
    if (x == 1)
    {
        if (alpha == 0)
        {
            alpha = 3;
            printf("%d\n", alpha);
        }
        else
        {
            alpha -= 2;
            alpha += 3;
            printf("%d\n", alpha);
        }
        return ;
    }
}

int main()
{
    freopen("jump.in", "r", stdin);
    freopen("jump.out", "w", stdout);
    scanf("%d", &t);
    while (t--)
    {
        pre1 = pre2 = pre3 = dep = 0;
        scanf("%d%d", &x, &y);
        if (x < 0) x = -x;
        if (y < 0) y = -y;
        if (x < y) swap(x, y);
        if (x == y)
        {
            work1();
            continue;
        }
        if (y == 0)
        {
            work2();
            continue;
        }
        /*if (x > 2000)
        {
            if (x < y * 2)
            {
                int delta = x - y;
                pre1 = (y - delta) / 3;
                x -= pre1 * 3;
                y -= pre1 * 3;
                pre1 <<= 1;
                //cout<<x <<" "<<y<<endl;
            }
            pre3 = (x - 2000) >> 1;
            x -= (pre3 << 1);
            if (y - pre3 > 1000) y -= pre3;
            else if (y + pre3 < 1000) y += pre3;
            else
            {
                if (y > 1000)
                {
                    if ((pre3 & 1) == ((y - 1000) & 1)) y = 1000;
                    else y = 1001;
                }
                else
                {
                    if ((pre3 & 1) == ((1000 - y) & 1)) y = 1000;
                    else y = 1001;
                }
            }
        }
        if (y > 2000)
        {
            swap(x, y);
            pre2 = (x - 2000) >> 1;
            x -= (pre2 << 1);
            if (y - pre2 > 1000) y -= pre2;
            else if (y + pre2 < 1000) y += pre2;
            else
            {
                if (y > 1000)
                {
                    if ((pre2 & 1) == ((y - 1000) & 1)) y = 1000;
                    else y = 1001;
                }
                else
                {
                    if ((pre2 & 1) == ((1000 - y) & 1)) y = 1000;
                    else y = 1001;
                }
            }
        }*/
        if (x <= 1000)
        {
            while(x + y > 18)
            {
                pre2 += 2;
                if(x < y) swap(x, y);
                if(x - 4 >= 2 * y) x -= 4;
                else
                {
                    x -= 4;
                    y -= 2;
                }
            }
            memset(b, 0, sizeof(b));
            b[20][20]=1;
            dep = 0;
            bfs();
            continue;
        }
        if (x == y * 2)
        {
            printf("%d\n", y);
            continue;
        }
        else if (x < y * 2)
        {
            int delta = x - y;
            delta = y - delta;
            y -= delta;
            int alpha = delta / 3;
            delta %= 3;
            alpha *= 2;
            if (delta == 0)
            {
                printf("%d\n", y + alpha);
                continue;
            }
            if (delta == 1)
            {
                alpha += 2;
                printf("%d\n", y + alpha);
                continue;
            }
            else if (delta == 2)
            {
                if (alpha)
                {
                    alpha -= 2;
                    alpha += 4;
                    printf("%d\n", y + alpha);
                }
                else
                {
                    alpha = 4;
                    printf("%d\n", y + alpha);
                }
                continue;
            }
        }
        else if (x > y * 2)
        {
            int delta = x - 2 * y;
            int alpha = delta / 4;
            alpha <<= 1;
            delta %= 4;
            if (delta == 0)
            {
                printf("%d\n", alpha + y);
                continue;
            }
            if (delta == 2)
            {
                printf("%d\n", alpha + 2 + y);
                continue;
            }
            if (delta == 3)
            {
                printf("%d\n", alpha + 3 + y);
                continue;
            }
            if (delta == 1)
            {
                if (alpha == 0)
                {
                    alpha = 3;
                    printf("%d\n", alpha + y);
                }
                else
                {
                    alpha -= 2;
                    alpha += 3;
                    printf("%d\n", alpha + y);
                }
                continue;
            }
        }
    }
    return 0;
}
