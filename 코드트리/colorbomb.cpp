#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
#define EMPTY -5
#define STONE -1
#define BOMB 0

int N, M, arr[21][21], ans = 0;
int dy[] = {1, 0, 0, -1}, dx[] = {0, -1, 1, 0};
bool visited[21][21];

vector<int> bfs(int y, int x)
{
    int rcnt = 0, cnt = 0, marky = y, markx = x;
    queue<pair<int, int>> q;
    vector<pair<int, int>> redbomb;
    q.push({y, x});
    int val = arr[y][x];
    visited[y][x] = true;
    cnt++;

    while (!q.empty())
    {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for (int d = 0; d < 4; d++)
        {
            int ny = y + dy[d];
            int nx = x + dx[d];
            if (ny < 0 || ny >= N || nx < 0 || nx >= N || visited[ny][nx])
                continue;
            if (arr[ny][nx] == val)
            {
                q.push({ny, nx});
                visited[ny][nx] = true;
                cnt++;
                if (ny > marky || (ny == marky && nx < markx))
                {
                    marky = ny;
                    markx = nx;
                }
            }
            else if (arr[ny][nx] == BOMB)
            {

                q.push({ny, nx});
                visited[ny][nx] = true;
                redbomb.push_back({ny, nx});
                cnt++;
                rcnt++;
            }
        }
    }

    for (auto &p : redbomb)
        visited[p.first][p.second] = false;

    return {cnt, rcnt, marky, markx};
}

bool cmp(vector<int> a, vector<int> b)
{
    if (a.empty())
        return true;
    if (a[0] != b[0])
        return a[0] < b[0];
    if (a[1] != b[1])
        return a[1] > b[1];
    if (a[2] != b[2])
        return a[2] < b[2];
    return a[3] > b[3];
}

int boom()
{
    memset(visited, false, sizeof(visited));

    vector<int> mxbomb;
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            vector<int> cnt;
            if (arr[r][c] == STONE || arr[r][c] == EMPTY || arr[r][c] == BOMB || visited[r][c])
                continue;
            else
            {
                cnt = bfs(r, c);
                if (cnt[0] == 1)
                    continue;
                if (cmp(mxbomb, cnt))
                {
                    mxbomb = cnt;
                }
            }
        }
    }

    if (mxbomb.empty())
        return 0;

    memset(visited, false, sizeof(visited));
    queue<pair<int, int>> q;
    int y = mxbomb[2];
    int x = mxbomb[3];
    q.push({y, x});
    int val = arr[y][x];
    visited[y][x] = true;
    arr[y][x] = EMPTY;

    while (!q.empty())
    {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for (int d = 0; d < 4; d++)
        {
            int ny = y + dy[d];
            int nx = x + dx[d];
            if (ny < 0 || ny >= N || nx < 0 || nx >= N || visited[ny][nx])
                continue;
            if (arr[ny][nx] == val)
            {
                q.push({ny, nx});
                visited[ny][nx] = true;
                arr[ny][nx] = EMPTY;
            }
            else if (arr[ny][nx] == BOMB)
            {
                q.push({ny, nx});
                visited[ny][nx] = true;
                arr[ny][nx] = EMPTY;
            }
        }
    }

    return mxbomb[0];
}

void gravity()
{
    for (int col = 0; col < N; col++)
    {
        int write = N - 1;

        for (int row = N - 1; row >= 0; row--)
        {
            if (arr[row][col] == STONE)
            {
                write = row - 1;
            }
            else if (arr[row][col] != EMPTY)
            {
                if (row != write)
                {
                    arr[write][col] = arr[row][col];
                    arr[row][col] = EMPTY;
                }
                write--;
            }
        }
    }
}

void turn()
{
    int temp[21][21];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            temp[N - 1 - j][i] = arr[i][j];
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            arr[i][j] = temp[i][j];
        }
    }
}

int main()
{
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> arr[i][j];
        }
    }
    int i = 0;
    while (true)
    {
        int score = boom();
        if (score == 0)
            break;
        ans += score * score;
        gravity();
        turn();
        gravity();
    }
    cout << ans;
    return 0;
}