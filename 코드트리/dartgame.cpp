#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int N, M, Q;
int dy[] = {-1, 0, 1, 0}, dx[] = {0, -1, 0, 1};
vector<vector<int>> disc;
bool visited[51][51];

int bfs(int y, int x)
{
    queue<pair<int, int>> q;
    q.push({y, x});
    visited[y][x] = true;
    int val = disc[y][x];
    int cnt = 0;

    while (!q.empty())
    {
        int cy = q.front().first;
        int cx = q.front().second;
        q.pop();

        for (int d = 0; d < 4; d++)
        {
            int ny = cy + dy[d];
            int nx = (cx + dx[d] + M) % M;
            if (ny < 0 || ny >= N)
                continue;
            if (visited[ny][nx] || disc[ny][nx] != val)
                continue;
            visited[ny][nx] = true;
            q.push({ny, nx});
            cnt++;
            disc[ny][nx] = -1;
        }
    }
    if (cnt > 0)
    {
        disc[y][x] = -1;
        return true;
    }
    return false;
}

pair<int, int> cal()
{
    int res = 0, cnt = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (disc[i][j] > 0)
            {
                cnt++;
                res += disc[i][j];
            }
        }
    }
    return {res, cnt};
}

bool clear()
{
    bool flag = false;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (!visited[i][j] && disc[i][j] > 0)
                if (bfs(i, j))
                    flag = true;
        }
    }
    return flag;
}

void nomalize()
{
    pair<int, int> info = cal();
    if (info.second == 0)
        return;
    int avg = info.first / info.second;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (disc[i][j] <= 0)
                continue;
            if (avg > disc[i][j])
            {
                disc[i][j]++;
            }
            else if (avg < disc[i][j])
            {
                disc[i][j]--;
            }
        }
    }
}

void turn(int x, int d, int k)
{
    for (int i = 0; i < N; i++)
    {
        if ((i + 1) % x != 0)
            continue;
        int rot = k % M;
        vector<int> &plate = disc[i];

        if (d == 0)
        {
            while (rot--)
            {
                plate.insert(plate.begin(), plate.back());
                plate.pop_back();
            }
        }
        else
        {
            while (rot--)
            {
                plate.push_back(plate.front());
                plate.erase(plate.begin());
            }
        }
    }
}

int main()
{
    cin >> N >> M >> Q;
    for (int i = 0; i < N; i++)
    {
        disc.push_back({});
        for (int j = 0; j < M; j++)
        {
            int num;
            cin >> num;
            disc.back().push_back(num);
        }
    }

    while (Q-- > 0)
    {
        memset(visited, false, sizeof(visited));
        int x, d, k;
        cin >> x >> d >> k;

        turn(x, d, k);

        if (!clear())
            nomalize();
    }

    cout << cal().first;
    return 0;
}