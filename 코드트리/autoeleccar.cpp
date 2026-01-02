#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int N, M, C, arr[25][25];
int dy[] = {-1, 0, 0, 1}, dx[] = {0, -1, 1, 0};
pair<int, int> car;
vector<pair<int, int>> dst;

vector<int> findNextPassenger(pair<int, int> c)
{
    if (arr[c.first][c.second] > 0)
        return {c.first, c.second, 0};
    int visited[25][25];
    memset(visited, -1, sizeof(visited));
    vector<int> res = {N, N, 999};
    queue<pair<int, int>> q;
    q.push(c);
    visited[c.first][c.second] = 0;

    while (!q.empty())
    {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for (int d = 0; d < 4; d++)
        {
            int ny = y + dy[d];
            int nx = x + dx[d];
            if (ny < 0 || ny >= N || nx < 0 || nx >= N || arr[ny][nx] == -1 || visited[ny][nx] > -1)
                continue;

            q.push({ny, nx});
            visited[ny][nx] = visited[y][x] + 1;
            if (arr[ny][nx] > 0)
            {
                if (res[2] > visited[ny][nx])
                {
                    res = {ny, nx, visited[ny][nx]};
                }
                else if (res[2] == visited[ny][nx])
                {
                    if (res[0] > ny)
                        res = {ny, nx, visited[ny][nx]};
                    else if (res[0] == ny && res[1] > nx)
                        res = {ny, nx, visited[ny][nx]};
                }
            }
        }
    }

    if (res[0] != N)
        return res;
    return {-1, -1, -1};
}

int go(pair<int, int> c, pair<int, int> d)
{
    int visited[25][25];
    memset(visited, -1, sizeof(visited));
    queue<pair<int, int>> q;
    q.push(c);
    visited[c.first][c.second] = 0;

    while (!q.empty())
    {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (ny < 0 || ny >= N || nx < 0 || nx >= N || arr[ny][nx] == -1 || visited[ny][nx] > -1)
                continue;

            q.push({ny, nx});
            visited[ny][nx] = visited[y][x] + 1;
            if (make_pair(ny, nx) == d)
            {
                return visited[ny][nx];
            }
        }
    }
    return -1;
}

int main()
{
    cin >> N >> M >> C;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            cin >> arr[i][j];
            if (arr[i][j] == 1)
            {
                arr[i][j] = -1;
            }
        }

    cin >> car.first >> car.second;
    car.first--;
    car.second--;

    for (int i = 1; i <= M; i++)
    {
        int py, px, desty, destx;
        cin >> py >> px >> desty >> destx;
        arr[py - 1][px - 1] = i;
        dst.push_back({desty - 1, destx - 1});
    }

    int turn = 0;
    bool flag = true;
    while (turn < M)
    {
        turn++;
        vector<int> np = findNextPassenger(car);
        if (np[0] == -1)
        {
            flag = false;
            break;
        }
        int passengerId = arr[np[0]][np[1]];
        arr[np[0]][np[1]] = 0;
        car = {np[0], np[1]};
        C -= np[2];
        if (C <= 0)
        {
            flag = false;
            break;
        }

        int nd = go(car, dst[passengerId - 1]);
        if (nd == -1)
        {
            flag = false;
            break;
        }
        car = dst[passengerId - 1];
        C -= nd;

        if (C < 0)
        {
            flag = false;
            break;
        }
        C += (nd * 2);
    }
    if (!flag)
        cout << -1;
    else
        cout << C;

    return 0;
}