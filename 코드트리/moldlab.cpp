#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstring>
using namespace std;

int n, m, k, arr[101][101], narr[101][101], sy = -1, ans = 0;
int dy[] = {-1, 1, 0, 0}, dx[] = {0, 0, 1, -1};
unordered_map<int, vector<int>> mold;

void move(int y, int x, int idx)
{
    vector<int> &cm = mold[idx];
    int s = cm[0];
    int d = cm[1];
    int size = cm[2];

    int ny = y;
    int nx = x;

    if (d == 0 || d == 1)
    {
        int dir = (d == 0 ? -1 : 1);
        int period = 2 * (n - 1);
        int pos = (y + dir * s) % period;
        if (pos < 0)
            pos += period;

        if (pos >= n)
        {
            ny = period - pos;
            cm[1] = (d == 0 ? 1 : 0);
        }
        else
        {
            ny = pos;
        }
    }
    else
    {
        int dir = (d == 2 ? 1 : -1);
        int period = 2 * (m - 1);
        int pos = (x + dir * s) % period;
        if (pos < 0)
            pos += period;

        if (pos >= m)
        {
            nx = period - pos;
            cm[1] = (d == 2 ? 3 : 2);
        }
        else
        {
            nx = pos;
        }
    }

    if (narr[ny][nx] != 0)
    {
        if (mold[narr[ny][nx]][2] > size)
        {
            mold[idx].clear();
            return;
        }
        else
        {
            mold[narr[ny][nx]].clear();
        }
    }

    narr[ny][nx] = idx;
}

int main()
{
    memset(arr, 0, sizeof(arr));
    memset(narr, 0, sizeof(narr));

    cin >> n >> m >> k;
    for (int i = 1; i <= k; i++)
    {
        int y, x, s, d, b;
        cin >> y >> x >> s >> d >> b;
        arr[y - 1][x - 1] = i;
        mold[i] = {s, d - 1, b};
    }

    while (++sy < m)
    {
        for (int i = 0; i < n; i++)
        {
            if (arr[i][sy] != 0)
            {
                ans += mold[arr[i][sy]][2];
                mold[arr[i][sy]].clear();
                arr[i][sy] = 0;
                break;
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (arr[i][j] != 0)
                {
                    move(i, j, arr[i][j]);
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                arr[i][j] = narr[i][j];
                narr[i][j] = 0;
            }
        }
    }

    cout << ans;
    return 0;
}