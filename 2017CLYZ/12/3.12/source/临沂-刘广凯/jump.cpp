#include <cstdio>
#include <queue>
#include <cassert>
#include <cstdlib>

const int dx[8] = { +1, +1, -1, -1, +2, +2, -2, -2 };
const int dy[8] = { +2, -2, +2, -2, +1, -1, +1, -1 };

const int U = 1000;

struct Point{
    int x, y;

    Point(int x = 0, int y = 0) : x(x), y(y) {}

    friend inline bool operator==(const Point &a, const Point &b){
        return a.x == b.x && a.y == b.y;
    }

    Point transform(int i){
        return Point(x + dx[i], y + dy[i]);
    }

    bool valid(){
        return -U <= x && x <= U && -U <= y && y <= U;
    }
};

template<typename T>
struct Array{
    T a[2 * U + 1][2 * U + 1];

    T& operator()(const Point &p){
        return a[p.x + U][p.y + U];
    }
};

Array<bool> vis;
Array<int> step;

int l, r;
Point Q[4 * (U + 1) * (U + 1)];

inline int BFS(const Point &T){
    if(vis(T)){
        return step(T);
    }

    while(l != r){
        if(Q[l] == T) return step(T);

        Point P = Q[l++];

        for(int i = 0; i < 8; i++){
            Point R = P.transform(i);
            if(R.valid() && !vis(R)){
                vis(R) = true, step(R) = step(P) + 1;
                Q[r++] = R;
            }
        }
    }

    return -1;
}

inline int solveEq(int x){
    x -= 4;
    return 4 + x / 3 * 2;
}

inline int solveZero(int x){
    x -= 2;
    int t = x / 4 + 1;
    return x % 2 ? 2 * t + 1 : 2 * t;
}

int main(){
    freopen("jump.in", "r", stdin), freopen("jump.out", "w", stdout);

    Point S(0, 0);
    l = 0, r = 0, Q[r++] = S, vis(S) = true, step(S) = 0;

    int t;
    scanf("%d", &t);
    while(t--){
        int x, y;
        scanf("%d%d", &x, &y);

        x = abs(x), y = abs(y);
 
        int ans = 0;

        if(-U <= x && x <= U && -U <= y && y <= U){
            ans = BFS(Point(x, y));
        } else if(x == y){
            ans = solveEq(x);
        } else if(x == 0 || y == 0){
            ans = solveZero(x + y);
        } else{
            // ans = BFS(Point(x, y));
        }

        printf("%d\n", ans);
    }
 
    fclose(stdin), fclose(stdout);
    return 0;
}

