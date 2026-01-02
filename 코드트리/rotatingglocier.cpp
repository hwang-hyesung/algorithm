#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int N, Q, M, arr[65][65];
bool visited[65][65];
int dy[] = {-1, 1, 0, 0}, dx[] = {0, 0, -1, 1};

pair<int, int> bfs(int y, int x)
{
    queue<pair<int, int>> q;
    q.push({y, x});
    visited[y][x] = true;
    int total = arr[y][x], cnt = 1;

    while (!q.empty())
    {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for (int d = 0; d < 4; d++)
        {
            int ny = y + dy[d], nx = x + dx[d];
            if (ny < 0 || ny >= M || nx < 0 || nx >= M || arr[ny][nx] < 1 || visited[ny][nx])
                continue;
            cnt++;
            total += arr[ny][nx];
            q.push({ny, nx});
            visited[ny][nx] = true;
        }
    }

    return {total, cnt};
}

void cal()
{
    memset(visited, false, sizeof(visited));
    int total = 0, bg = 0;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (arr[i][j] < 1 || visited[i][j])
                continue;
            pair<int, int> p = bfs(i, j);
            total += p.first;
            bg = max(bg, p.second);
        }
    }

    cout << total << "\n"
         << bg;
}

void turn(int lv)
{
    if (lv == 0)
        return;
    int w = pow(2, lv);
    int temp[65][65];
    for (int i = 0; i < M; i += w)
    {
        for (int j = 0; j < M; j += w)
        {
            for (int r = i; r < i + w / 2; r++)
                for (int c = j; c < j + w / 2; c++)
                    temp[r][c + w / 2] = arr[r][c];

            for (int r = i; r < i + w / 2; r++)
                for (int c = j + w / 2; c < j + w; c++)
                    temp[r + w / 2][c] = arr[r][c];

            for (int r = i + w / 2; r < i + w; r++)
                for (int c = j + w / 2; c < j + w; c++)
                    temp[r][c - w / 2] = arr[r][c];

            for (int r = i + w / 2; r < i + w; r++)
                for (int c = j; c < j + w / 2; c++)
                    temp[r - w / 2][c] = arr[r][c];
        }
    }

    for (int i = 0; i < M; i++)
        for (int j = 0; j < M; j++)
            arr[i][j] = temp[i][j];
}

void melt()
{
    vector<pair<int, int>> melting;
    for (int y = 0; y < M; y++)
    {
        for (int x = 0; x < M; x++)
        {
            if (arr[y][x] < 1)
                continue;
            int cnt = 0;
            for (int d = 0; d < 4; d++)
            {
                int ny = y + dy[d], nx = x + dx[d];
                if (ny < 0 || ny >= M || nx < 0 || nx >= M || arr[ny][nx] < 1)
                    continue;
                cnt++;
            }
            if (cnt < 3)
                melting.push_back({y, x});
        }
    }

    for (pair<int, int> m : melting)
    {
        arr[m.first][m.second]--;
    }
}

int main()
{
    cin >> N >> Q;
    M = pow(2, N);

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> arr[i][j];
        }
    }

    while (Q--)
    {
        int lv;
        cin >> lv;

        turn(lv);
        melt();
    }

    cal();
    return 0;
}