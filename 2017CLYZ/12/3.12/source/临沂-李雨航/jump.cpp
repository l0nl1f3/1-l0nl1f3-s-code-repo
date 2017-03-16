#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int main()
{
    freopen("jump.in", "r", stdin);
    freopen("jump.out", "w", stdout);
    
    int t;
    cin >> t;
    while (t--)
    {
        int x, y;
        scanf("%d%d", &x, &y);

        if (x == y)
        {
            if (x == 1 || x == -1)
            {
                cout << 2 << endl;
            }
            else if (x == 2 || x == -2)
            {
                cout << 4 << endl;
            }
            else if (x == 3 || x == -3)
            {
                cout << 2 << endl;
            }
            else
            {
                int pos = (x - 4) / 3 + 1;
                int ans = 2;

                for (int i = 1; i <= pos; i++)
                {
                    ans += 2;
                }
                cout << ans << endl;
            }
        }
        else if (x == 2 * y)
        {
            int ans = x / 2;
            cout << ans << endl;
        }
        else if (2 * x == y)
        {
            int ans = y / 2;
            cout << ans << endl;
        }

    }
    return 0;
}
