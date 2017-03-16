#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, l, r;
ll fz, fm, ny, ans;
void exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return ;
    }
    else
    {
        exgcd(b, a % b, y, x);
        y -= x * (a / b);
    }
}

ll work(ll a, ll b)
{
    ll x, y;
    exgcd(a, b, x, y);
    return (x + b) % b;
}

int main()
{
    freopen("abs.in", "r", stdin);
    freopen("abs.out", "w", stdout);
    cin >> n >> l >> r;
    fz = (r + 1) * r / 2;
    if (l < 0) fz += (l - 1) * l / 2;
    else fz -= (l - 1) * (l - 2) / 2;
    fm = r - l + 1;
    ny = work(fm, mod);
    ans = (fz * ny) % mod;
    if (ans < 0) ans += mod;
    cout << ans ;
    return 0;
}
