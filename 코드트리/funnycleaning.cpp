#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int n, ans = 0, arr[500][500];
double blow[5][5] = {
    {0, 0, 2, 0, 0},
    {0, 10, 7, 1, 0},
    {5, 0, 0, 0, 0},
    {0, 10, 7, 1, 0},
    {0, 0, 2, 0, 0}};
vector<pair<int, int>> route;

void init()
{
    route.clear();

    int y = n / 2;
    int x = n / 2;
    int dy[] = {0, 1, 0, -1}, dx[] = {-1, 0, 1, 0};

    int len = 1;
    int dir = 0;

    while (true)
    {
        for (int rep = 0; rep < 2; rep++)
        {
            for (int i = 0; i < len; i++)
            {
                y += dy[dir];
                x += dx[dir];

                if (y < 0 || y >= n || x < 0 || x >= n)
                    return;

                route.push_back({y, x});
            }
            dir = (dir + 1) % 4;
        }
        len++;
    }
}

void defuse(int y, int x, int ny, int nx)
{
    int dust = arr[ny][nx];
    arr[ny][nx] = 0;
    int dy = ny - y, dx = nx - x;
    int total = 0;

    for (int i = -2; i <= 2; i++)
    {
        for (int j = -2; j <= 2; j++)
        {
            int rate = blow[i + 2][j + 2];
            if (rate == 0)
                continue;

            int cy, cx;
            if (dy == 0 && dx == -1)
            {
                cy = ny + i;
                cx = nx + j;
            }
            else if (dy == 1 && dx == 0)
            {
                cy = ny - j;
                cx = nx + i;
            }
            else if (dy == 0 && dx == 1)
            {
                cy = ny - i;
                cx = nx - j;
            }
            else
            {
                cy = ny + j;
                cx = nx - i;
            }

            int val = dust * rate / 100;
            total += val;
            if (cy < 0 || cy >= n || cx < 0 || cx >= n)
                ans += val;
            else
                arr[cy][cx] += val;
        }
    }

    int ay = ny + dy;
    int ax = nx + dx;
    if (ay < 0 || ay >= n || ax < 0 || ax >= n)
        ans += dust - total;
    else
        arr[ay][ax] += dust - total;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> arr[i][j];
        }
    }

    init();
    int y = n / 2, x = n / 2;
    for (pair<int, int> p : route)
    {
        defuse(y, x, p.first, p.second);
        y = p.first;
        x = p.second;
    }
    cout << ans;

    return 0;
}