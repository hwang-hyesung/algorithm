#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <queue>
using namespace std;

int n, arr[30][30], groups[30][30], ans = 0, dy[] = {-1, 0, 1, 0}, dx[] = {0, -1, 0, 1};
bool visited[30][30];
int w[1000], value[1000];

void turn()
{
    int temp[30][30];
    memset(temp, 0, sizeof(temp));

    int mid = n / 2;

    for (int i = 0; i < n; i++)
    {
        temp[n - 1 - i][mid] = arr[mid][i];
        temp[mid][i] = arr[i][mid];
    }

    for (int i = 0; i < mid; i++)
        for (int j = 0; j < mid; j++)
            temp[j][mid - 1 - i] = arr[i][j];

    for (int i = 0; i < mid; i++)
        for (int j = mid + 1; j < n; j++)
            temp[j - n / 2 - 1][n - 1 - i] = arr[i][j];

    for (int i = mid + 1; i < n; i++)
        for (int j = 0; j < mid; j++)
            temp[j + mid + 1][mid - 1 - (i - (mid + 1))] = arr[i][j];

    for (int i = mid + 1; i < n; i++)
        for (int j = mid + 1; j < n; j++)
            temp[j][n + n / 2 - i] = arr[i][j];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            arr[i][j] = temp[i][j];
}

void bfs(int idx, int y, int x)
{
    int val = arr[y][x], cnt = 0;
    queue<pair<int, int>> q;

    visited[y][x] = true;
    groups[y][x] = idx;
    q.push({y, x});

    while (!q.empty())
    {
        int cy = q.front().first;
        int cx = q.front().second;
        q.pop();
        cnt++;

        for (int d = 0; d < 4; d++)
        {
            int ny = cy + dy[d];
            int nx = cx + dx[d];

            if (ny < 0 || ny >= n || nx < 0 || nx >= n || visited[ny][nx] || arr[ny][nx] != val)
                continue;

            visited[ny][nx] = true;
            groups[ny][nx] = idx;
            q.push({ny, nx});
        }
    }

    w[idx] = cnt;
    value[idx] = val;
}

void make_groups()
{
    memset(visited, false, sizeof(visited));
    memset(groups, 0, sizeof(groups));
    memset(w, 0, sizeof(w));
    memset(value, 0, sizeof(value));

    int idx = 1;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (!visited[i][j])
                bfs(idx++, i, j);
}

int cal()
{
    map<pair<int, int>, int> edgeCnt;

    for (int y = 0; y < n; y++)
    {
        for (int x = 0; x < n; x++)
        {
            for (int d = 0; d < 4; d++)
            {
                int ny = y + dy[d];
                int nx = x + dx[d];
                if (ny < 0 || nx < 0 || ny >= n || nx >= n)
                    continue;

                int a = groups[y][x];
                int b = groups[ny][nx];

                if (a >= b)
                    continue;
                edgeCnt[{a, b}]++;
            }
        }
    }

    int score = 0;
    for (auto &e : edgeCnt)
    {
        int a = e.first.first;
        int b = e.first.second;
        int edges = e.second;
        score += (w[a] + w[b]) * value[a] * value[b] * edges;
    }

    return score;
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

    for (int i = 0; i < 4; i++)
    {
        make_groups();
        ans += cal();
        turn();
    }
    cout << ans;
    return 0;
}