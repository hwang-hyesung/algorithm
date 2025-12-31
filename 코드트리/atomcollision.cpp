#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

struct Atom
{
    int m, s, d;
};
int N, M, K;
vector<Atom> arr[51][51];
vector<Atom> narr[51][51];
int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1}, dx[] = {0, 1, 1, 1, 0, -1, -1, -1};

void move()
{
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            for (Atom a : arr[y][x])
            {
                int speed = a.s % N;
                int ny = (y + speed * dy[a.d] + N) % N;
                int nx = (x + speed * dx[a.d] + N) % N;

                narr[ny][nx].push_back(a);
            }
        }
    }
}

void fusenfiss()
{
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            if (narr[y][x].size() <= 1)
                continue;
            int s = 0, m = 0, d = narr[y][x][0].d % 2;
            bool flag = true;
            for (Atom a : narr[y][x])
            {
                s += a.s;
                m += a.m;
                if (flag && d != a.d % 2)
                    flag = false;
            }
            m /= 5;
            s /= narr[y][x].size();
            if (flag)
                d = 0;
            else
                d = 1;

            narr[y][x].clear();
            if (m == 0)
                continue;
            for (int i = d; i < 8; i += 2)
            {
                narr[y][x].push_back({m, s, i});
            }
        }
    }
}

int cal()
{
    int res = 0;
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            for (Atom a : arr[y][x])
            {
                res += a.m;
            }
        }
    }
    return res;
}

int main()
{
    cin >> N >> M >> K;
    for (int i = 0; i < M; i++)
    {
        int y, x, m, s, d;
        cin >> y >> x >> m >> s >> d;
        arr[y - 1][x - 1].push_back({m, s, d});
    }

    while (K--)
    {
        for (int y = 0; y < N; y++)
            for (int x = 0; x < N; x++)
                narr[y][x].clear();

        move();
        fusenfiss();

        for (int y = 0; y < N; y++)
        {
            for (int x = 0; x < N; x++)
            {
                arr[y][x] = narr[y][x];
            }
        }
    }

    cout << cal();

    return 0;
}