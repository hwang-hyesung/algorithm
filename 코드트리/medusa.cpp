#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

int n, m, my, mx, py, px, road[51][51], a[51][51];
bool visited[51][51], seen[51][51];
int dis, stone, atk;
int dy[] = {-1, 1, 0, 0}, dx[] = {0, 0, -1, 1};
vector<pair<int, int>> knight;
stack<pair<int, int>> way;

void resetVision()
{
    memset(seen, false, sizeof(seen));
    memset(visited, false, sizeof(visited));
    visited[my][mx] = true;
}

void seeUp()
{
    resetVision();
    for (int i = 1; i < n; i++)
    {
        for (int j = -i; j <= i; j++)
        {
            int ny = my - i;
            int nx = mx + j;
            if (ny < 0 || nx < 0 || nx >= n)
                continue;
            if (!visited[ny][nx])
            {
                seen[ny][nx] = true;
                visited[ny][nx] = true;

                if (a[ny][nx] != 0)
                {
                    for (int k = 1; k <= ny; k++)
                    {
                        for (int l = 0; l <= k; l++)
                        {
                            if (j < 0 && nx - l >= 0)
                                visited[ny - k][nx - l] = true;
                            if (j == 0)
                                visited[ny - k][nx] = true;
                            if (j > 0 && nx + l < n)
                                visited[ny - k][nx + l] = true;
                        }
                    }
                }
            }
        }
    }
}

void seeDown()
{
    resetVision();
    for (int i = 1; i < n; i++)
    {
        for (int j = -i; j <= i; j++)
        {
            int ny = my + i;
            int nx = mx + j;
            if (ny >= n || nx < 0 || nx >= n)
                continue;
            if (!visited[ny][nx])
            {
                seen[ny][nx] = true;
                visited[ny][nx] = true;

                if (a[ny][nx] != 0)
                {
                    for (int k = 1; ny + k < n; k++)
                    {
                        for (int l = 0; l <= k; l++)
                        {
                            if (j < 0 && nx - l >= 0)
                                visited[ny + k][nx - l] = true;
                            if (j == 0)
                                visited[ny + k][nx] = true;
                            if (j > 0 && nx + l < n)
                                visited[ny + k][nx + l] = true;
                        }
                    }
                }
            }
        }
    }
}

void seeLeft()
{
    resetVision();
    for (int i = 1; i < n; i++)
    {
        for (int j = -i; j <= i; j++)
        {
            int ny = my + j;
            int nx = mx - i;
            if (nx < 0 || ny < 0 || ny >= n)
                continue;
            if (!visited[ny][nx])
            {
                seen[ny][nx] = true;
                visited[ny][nx] = true;

                if (a[ny][nx] != 0)
                {
                    for (int k = 1; nx - k >= 0; k++)
                    {
                        for (int l = 0; l <= k; l++)
                        {
                            if (j < 0 && ny - l >= 0)
                                visited[ny - l][nx - k] = true;
                            if (j == 0)
                                visited[ny][nx - k] = true;
                            if (j > 0 && ny + l < n)
                                visited[ny + l][nx - k] = true;
                        }
                    }
                }
            }
        }
    }
}

void seeRight()
{
    resetVision();
    for (int i = 1; i < n; i++)
    {
        for (int j = -i; j <= i; j++)
        {
            int ny = my + j;
            int nx = mx + i;
            if (nx >= n || ny < 0 || ny >= n)
                continue;
            if (!visited[ny][nx])
            {
                seen[ny][nx] = true;
                visited[ny][nx] = true;

                if (a[ny][nx] != 0)
                {
                    for (int k = 1; nx + k < n; k++)
                    {
                        for (int l = 0; l <= k; l++)
                        {
                            if (j < 0 && ny - l >= 0)
                                visited[ny - l][nx + k] = true;
                            if (j == 0)
                                visited[ny][nx + k] = true;
                            if (j > 0 && ny + l < n)
                                visited[ny + l][nx + k] = true;
                        }
                    }
                }
            }
        }
    }
}

int cntUp()
{
    int sum = 0;
    seeUp();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (seen[i][j])
                sum += a[i][j];
    return sum;
}
int cntDown()
{
    int sum = 0;
    seeDown();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (seen[i][j])
                sum += a[i][j];
    return sum;
}
int cntLeft()
{
    int sum = 0;
    seeLeft();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (seen[i][j])
                sum += a[i][j];
    return sum;
}
int cntRight()
{
    int sum = 0;
    seeRight();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (seen[i][j])
                sum += a[i][j];
    return sum;
}

void msight(int y, int x)
{
    int cnt[4];
    cnt[0] = cntUp();
    cnt[1] = cntDown();
    cnt[2] = cntLeft();
    cnt[3] = cntRight();

    int maxdir = 0;
    for (int i = 1; i < 4; i++)
        if (cnt[i] > cnt[maxdir])
            maxdir = i;

    if (maxdir == 0)
        seeUp();
    else if (maxdir == 1)
        seeDown();
    else if (maxdir == 2)
        seeLeft();
    else
        seeRight();

    stone = cnt[maxdir];
}

bool findWay(int y, int x)
{
    memset(visited, 0, sizeof(visited));
    queue<pair<int, int>> q;
    pair<int, int> parent[51][51];
    q.push({y, x});
    visited[y][x] = true;
    bool found = false;

    while (!q.empty())
    {
        auto [cy, cx] = q.front();
        q.pop();
        if (cy == py && cx == px)
        {
            found = true;
            break;
        }

        for (int i = 0; i < 4; i++)
        {
            int ny = cy + dy[i], nx = cx + dx[i];
            if (ny < 0 || ny >= n || nx < 0 || nx >= n)
                continue;
            if (!visited[ny][nx] && road[ny][nx] == 0)
            {
                visited[ny][nx] = true;
                parent[ny][nx] = {cy, cx};
                q.push({ny, nx});
            }
        }
    }

    if (!found)
        return false;

    pair<int, int> cur = {py, px};
    while (cur != make_pair(y, x))
    {
        way.push(cur);
        cur = parent[cur.first][cur.second];
    }
    return true;
}

bool move1(int idx)
{
    int y = knight[idx].first;
    int x = knight[idx].second;

    if (y == -1)
        return false;
    int minDist = abs(y - my) + abs(x - mx);
    if (seen[y][x])
        return false;
    if (y == my && x == mx)
    {
        knight[idx] = {-1, -1};
        a[y][x]--;
        return false;
    }

    for (int i = 0; i < 4; i++)
    {
        int ny = y + dy[i];
        int nx = x + dx[i];
        if (ny < 0 || ny >= n || nx < 0 || nx >= n || seen[ny][nx])
            continue;
        int newDist = abs(ny - my) + abs(nx - mx);
        if (newDist < minDist)
        {
            if (ny == my && nx == mx)
            {
                knight[idx] = {-1, -1};
                a[y][x]--;
                atk++;
                dis++;
                return false;
            }

            knight[idx] = {ny, nx};
            a[y][x]--;
            a[ny][nx]++;
            dis++;
            return true;
        }
    }
    return false;
}

void move2(int idx)
{
    int y = knight[idx].first;
    int x = knight[idx].second;

    if (y == -1)
        return;
    int minDist = abs(y - my) + abs(x - mx);
    if (seen[y][x])
    {
        return;
    }
    if (y == my && x == mx)
    {
        knight[idx].first = -1;
        knight[idx].second = -1;
        a[y][x]--;
        return;
    }
    int d[] = {2, 3, 0, 1};
    for (int i = 0; i < 4; i++)
    {
        int ny = y + dy[d[i]];
        int nx = x + dx[d[i]];
        if (ny < 0 || ny >= n || nx < 0 || nx >= n || seen[ny][nx])
            continue;
        int newDist = abs(ny - my) + abs(nx - mx);
        if (newDist < minDist)
        {

            if (ny == my && nx == mx)
            {
                knight[idx] = make_pair(-1, -1);
                a[y][x]--;
                atk++;
                dis++;
                return;
            }

            knight[idx] = make_pair(ny, nx);
            a[y][x]--;
            a[ny][nx]++;
            dis++;
            return;
        }
    }
}

int main()
{
    cin >> n >> m;
    cin >> my >> mx >> py >> px;

    for (int i = 1; i <= m; i++)
    {
        int y, x;
        cin >> y >> x;
        a[y][x]++;
        knight.push_back(make_pair(y, x));
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> road[i][j];
        }
    }

    memset(visited, 0, sizeof(visited));
    visited[my][mx] = true;
    if (!findWay(my, mx))
        cout << -1;

    while (!way.empty())
    {
        my = way.top().first;
        mx = way.top().second;
        way.pop();
        if (my == py && mx == px)
        {
            cout << 0;
            break;
        }

        visited[my][mx] = true;
        msight(my, mx);

        dis = 0;
        atk = 0;
        for (int i = 0; i < knight.size(); i++)
        {
            if (knight[i].first == -1)
                continue;
            if (move1(i))
                move2(i);
        }
        cout << dis << " " << stone << " " << atk << "\n";
    }
    return 0;
}
