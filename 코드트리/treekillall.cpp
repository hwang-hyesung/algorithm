#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int n, m, k, c, arr[21][21], killed[21][21], ans = 0, rnd = 0;
int dy[] = {-1, 0, 1, 0}, dx[] = {0, -1, 0, 1};
int kdy[] = {-1, -1, 1, 1}, kdx[] = {-1, 1, -1, 1};
bool visited[21][21];

void grow()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int cnt = 0;
            if (arr[i][j] > 0)
            {
                for (int d = 0; d < 4; d++)
                {
                    int ny = i + dy[d], nx = j + dx[d];
                    if (ny < 0 || ny >= n || nx < 0 || nx >= n)
                        continue;
                    if (arr[ny][nx] > 0)
                        cnt++;
                }
                arr[i][j] += cnt;
            }
        }
    }
}

void defuse()
{
    int temp[21][21];
    memset(temp, 0, sizeof(temp));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (arr[i][j] > 0)
            {
                int cnt = 0;
                for (int d = 0; d < 4; d++)
                {
                    int ny = i + dy[d], nx = j + dx[d];
                    if (ny < 0 || ny >= n || nx < 0 || nx >= n)
                        continue;
                    if (arr[ny][nx] != 0)
                        continue;
                    if (killed[ny][nx] > 0 && rnd <= killed[ny][nx] + c)
                        continue;

                    cnt++;
                }

                for (int d = 0; d < 4; d++)
                {
                    int ny = i + dy[d], nx = j + dx[d];
                    if (ny < 0 || ny >= n || nx < 0 || nx >= n)
                        continue;
                    if (arr[ny][nx] != 0)
                        continue;
                    if (killed[ny][nx] > 0 && rnd <= killed[ny][nx] + c)
                        continue;
                    temp[ny][nx] += arr[i][j] / cnt;
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            arr[i][j] += temp[i][j];
        }
    }
}

int cal(int y, int x)
{
    if (arr[y][x] <= 0 || (killed[y][x] > 0 && rnd <= killed[y][x] + c))
        return 0;
    int res = arr[y][x];
    for (int d = 0; d < 4; d++)
    {
        for (int dis = 1; dis <= k; dis++)
        {
            int ny = y + kdy[d] * dis;
            int nx = x + kdx[d] * dis;
            if (ny < 0 || ny >= n || nx < 0 || nx >= n || arr[ny][nx] <= 0 || (killed[ny][nx] > 0 && rnd <= killed[ny][nx] + c))
                break;
            res += arr[ny][nx];
        }
    }
    return res;
}

pair<int, int> findplace()
{
    int value[21][21] = {0};
    int bestval = 0, besty = -1, bestx = -1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            value[i][j] = cal(i, j);
            int val = value[i][j];
            if (bestval < val)
            {
                bestval = val;
                besty = i;
                bestx = j;
            }
        }
    }

    return {besty, bestx};
}

void kill(pair<int, int> place)
{
    int y = place.first, x = place.second;
    if (arr[y][x] <= 0 || (killed[y][x] > 0 && rnd <= killed[y][x] + c))
        return;
    ans += arr[y][x];
    killed[y][x] = rnd;
    arr[y][x] = 0;
    for (int d = 0; d < 4; d++)
    {
        for (int dis = 1; dis <= k; dis++)
        {
            int ny = y + kdy[d] * dis;
            int nx = x + kdx[d] * dis;

            if (ny < 0 || ny >= n || nx < 0 || nx >= n || arr[ny][nx] < 0)
                break;
            if (arr[ny][nx] == 0 || (killed[ny][nx] > 0 && rnd <= killed[ny][nx] + c))
            {
                killed[ny][nx] = rnd;
                break;
            }
            ans += arr[ny][nx];
            killed[ny][nx] = rnd;
            arr[ny][nx] = 0;
        }
    }
}

int main()
{
    memset(killed, 0, sizeof(killed));

    cin >> n >> m >> k >> c;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> arr[i][j];
        }
    }

    for (rnd = 1; rnd <= m; rnd++)
    {
        memset(visited, false, sizeof(visited));
        grow();
        defuse();
        pair<int, int> place = findplace();
        if (place.first != -1)
            kill(place);
    }
    cout << ans;
    return 0;
}