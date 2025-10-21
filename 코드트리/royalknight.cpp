#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

int l, n, q, damage[34], board[41][41], kb[41][41], knight[34][5], dy[] = {-1, 0, 1, 0}, dx[] = {0, 1, 0, -1};

bool ispossible(int idx, int dir)
{
    int r = knight[idx][0];
    int c = knight[idx][1];
    int h = knight[idx][2];
    int w = knight[idx][3];
    int k = knight[idx][4];
    if (k <= 0)
        return true;
    for (int y = r; y < r + h; y++)
    {
        for (int x = c; x < c + w; x++)
        {
            int ny = y + dy[dir];
            int nx = x + dx[dir];
            if (ny < 0 || nx < 0 || ny >= l || nx >= l || board[ny][nx] == 2)
                return false;
            if (kb[ny][nx] != 0 && kb[ny][nx] != idx)
            {
                if (!ispossible(kb[ny][nx], dir))
                    return false;
            }
            else
                continue;
        }
    }
    return true;
}
void move(int idx, int dir, bool ispush)
{
    int r = knight[idx][0];
    int c = knight[idx][1];
    int h = knight[idx][2];
    int w = knight[idx][3];
    int k = knight[idx][4];
    if (k <= 0)
        return;
    for (int y = r; y < r + h; y++)
    {
        for (int x = c; x < c + w; x++)
        {
            kb[y][x] = 0;
        }
    }
    r = r + dy[dir];
    c = c + dx[dir];
    for (int y = r; y < r + h; y++)
    {
        for (int x = c; x < c + w; x++)
        {
            if (kb[y][x] != 0 && kb[y][x] != idx)
            {
                move(kb[y][x], dir, true);
            }
            kb[y][x] = idx;
            if (board[y][x] == 1 && ispush && k > 0)
            {
                k--;
                damage[idx]++;
            }
        }
    }
    if (k == 0)
    {
        for (int y = r; y < r + h; y++)
        {
            for (int x = c; x < c + w; x++)
            {
                kb[y][x] = 0;
            }
        }
    }
    knight[idx][0] = r;
    knight[idx][1] = c;
    knight[idx][4] = k;
}

int sumd()
{
    int res = 0;
    for (int j = 1; j <= n; j++)
    {
        if (knight[j][4] > 0)
        {
            res += damage[j];
        }
    }
    return res;
}
int main()
{

    cin >> l >> n >> q;

    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < l; j++)
        {
            cin >> board[i][j];
        }
    }

    for (int i = 1; i <= n; i++)
    {
        cin >> knight[i][0] >> knight[i][1] >> knight[i][2] >> knight[i][3] >> knight[i][4];
        knight[i][0]--;
        knight[i][1]--;
        for (int y = knight[i][0]; y < knight[i][0] + knight[i][2]; y++)
        {
            for (int x = knight[i][1]; x < knight[i][1] + knight[i][3]; x++)
            {
                kb[y][x] = i;
            }
        }
    }

    for (int i = 0; i < q; i++)
    {
        int idx, dir;
        cin >> idx >> dir;
        if (ispossible(idx, dir))
        {
            move(idx, dir, false);
        }
    }

    cout << sumd();
    return 0;
}
