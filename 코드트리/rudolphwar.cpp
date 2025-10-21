#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>
using namespace std;

int n, m, p, c, d, ry, rx, arr[55][55];
vector<pair<pair<int, int>, pair<int, int>>> santa;
bool crash[35];
int kijul[35], isdead = 0;
int dy[] = {-1, 0, 1, 0}, dx[] = {0, 1, 0, -1};

void rcrash(int y, int x, int sdy, int sdx)
{
    int s_num = arr[y][x];
    int ny = y + c * sdy, nx = x + c * sdx;
    if (ny < 0 || ny >= n || nx < 0 || nx >= n)
    {
        arr[y][x] = 0;
        santa[s_num - 1].first.second += c;
        santa[s_num - 1].second.first = -1;
        isdead++;
        santa[s_num - 1].second.second = -1;
        return;
    }

    if (arr[ny][nx] == 0 || arr[ny][nx] == s_num)
    {
        arr[y][x] = 0;
        arr[ny][nx] = s_num;
        crash[s_num - 1] = true;
        kijul[s_num - 1] = kijul[s_num - 1] == 0 ? 1 : kijul[s_num - 1];
        santa[s_num - 1].first.second += c;
        santa[s_num - 1].second.first = ny;
        santa[s_num - 1].second.second = nx;
        return;
    }

    vector<pair<int, int>> chain;
    int sny = ny, snx = nx;
    while (true)
    {
        if (sny < 0 || sny >= n || snx < 0 || snx >= n || arr[sny][snx] == 0)
            break;
        chain.push_back({sny, snx});

        sny += sdy;
        snx += sdx;
    }

    for (int i = chain.size() - 1; i >= 0; --i)
    {
        int cy = chain[i].first, cx = chain[i].second;
        int next_num = arr[cy][cx];
        if (cy + sdy < 0 || cy + sdy >= n || cx + sdx < 0 || cx + sdx >= n)
        {
            isdead++;
            santa[next_num - 1].second.first = -1;
            santa[next_num - 1].second.second = -1;
            arr[cy][cx] = 0;
        }
        else
        {
            santa[next_num - 1].second.first = cy + sdy;
            santa[next_num - 1].second.second = cx + sdx;
            arr[cy][cx] = 0;
            arr[cy + sdy][cx + sdx] = next_num;
        }
    }

    crash[s_num - 1] = true;
    kijul[s_num - 1] = 1;
    santa[s_num - 1].first.second += c;
    santa[s_num - 1].second.first = ny;
    santa[s_num - 1].second.second = nx;
    arr[y][x] = 0;
    arr[ny][nx] = s_num;
}

void scrash(int y, int x, int sd, int s_num)
{
    int ny = y + d * dy[sd] - dy[sd], nx = x + d * dx[sd] - dx[sd];
    if (ny < 0 || ny >= n || nx < 0 || nx >= n)
    {
        isdead++;
        arr[y][x] = 0;
        santa[s_num - 1].first.second += d;
        santa[s_num - 1].second.first = -1;
        santa[s_num - 1].second.second = -1;
        return;
    }

    if (arr[ny][nx] == 0 || arr[ny][nx] == s_num)
    {
        crash[s_num - 1] = true;
        kijul[s_num - 1] = 1;
        santa[s_num - 1].first.second += d;
        santa[s_num - 1].second.first = ny;
        santa[s_num - 1].second.second = nx;
        arr[y][x] = 0;
        arr[ny][nx] = s_num;
        return;
    }

    vector<pair<int, int>> chain;
    int sny = ny, snx = nx;
    while (true)
    {
        if (sny < 0 || sny >= n || snx < 0 || snx >= n || arr[sny][snx] == 0)
            break;
        chain.push_back({sny, snx});

        sny += dy[sd];
        snx += dx[sd];
    }

    for (int i = chain.size() - 1; i >= 0; --i)
    {
        int cy = chain[i].first, cx = chain[i].second;
        int next_num = arr[cy][cx];
        if (cy + dy[sd] < 0 || cy + dy[sd] >= n || cx + dx[sd] < 0 || cx + dx[sd] >= n)
        {
            isdead++;
            santa[next_num - 1].second.first = -1;
            santa[next_num - 1].second.second = -1;
            arr[cy][cx] = 0;
        }
        else
        {
            santa[next_num - 1].second.first = cy + dy[sd];
            santa[next_num - 1].second.second = cx + dx[sd];
            arr[cy][cx] = 0;
            arr[cy + dy[sd]][cx + dx[sd]] = next_num;
        }
    }

    crash[s_num - 1] = true;
    kijul[s_num - 1] = 1;
    santa[s_num - 1].first.second += d;
    santa[s_num - 1].second.first = ny;
    santa[s_num - 1].second.second = nx;
    arr[y][x] = 0;
    arr[ny][nx] = s_num;
}

void rmove()
{
    int near_santa = 1, min_sy = 55, min_sx = 55, min_dis = 99999999;
    for (auto s : santa)
    {
        if (s.second.first == -1)
            continue;
        int dis = (s.second.first - ry) * (s.second.first - ry) + (s.second.second - rx) * (s.second.second - rx);

        if (min_dis < dis)
        {
            continue;
        }
        else if (min_dis == dis)
        {
            if (min_sy > s.second.first || (min_sy == s.second.first && min_sx > s.second.second))
            {
                continue;
            }
        }

        near_santa = s.first.first;
        min_sy = s.second.first;
        min_sx = s.second.second;
        min_dis = dis;
    }

    int rdy;
    if (ry > min_sy)
        rdy = -1;
    else if (ry < min_sy)
        rdy = 1;
    else
        rdy = 0;

    int rdx;
    if (rx > min_sx)
        rdx = -1;
    else if (rx < min_sx)
        rdx = 1;
    else
        rdx = 0;

    if (arr[ry + rdy][rx + rdx] != 0 && arr[ry + rdy][rx + rdx] != 50)
    {
        rcrash(ry + rdy, rx + rdx, rdy, rdx);
    }

    arr[ry][rx] = 0;
    arr[ry + rdy][rx + rdx] = 50;
    ry += rdy;
    rx += rdx;
}

void smove(pair<pair<int, int>, pair<int, int>> &s)
{
    int y = s.second.first;
    int x = s.second.second;

    long long disy = y - ry;
    long long disx = x - rx;
    long long min_dis = disy * disy + disx * disx;
    int min_i = 5;

    for (int i = 0; i < 4; i++)
    {
        int ny = y + dy[i];
        int nx = x + dx[i];

        if (ny < 0 || ny >= n || nx < 0 || nx >= n || (arr[ny][nx] != 0 && arr[ny][nx] != 50))
            continue;

        long long dis_ny = ny - ry;
        long long dis_nx = nx - rx;
        long long dis_n = dis_ny * dis_ny + dis_nx * dis_nx;

        if (min_dis > dis_n)
        {
            min_dis = dis_n;
            min_i = i;
        }
    }

    if (min_i >= 5)
    {
        return;
    }
    else if (arr[y + dy[min_i]][x + dx[min_i]] != 0 && arr[y + dy[min_i]][x + dx[min_i]] != 50)
    {
        return;
    }

    queue<pair<pair<int, int>, pair<int, int>>> q;
    if (arr[y + dy[min_i]][x + dx[min_i]] == 50)
    {
        q.push({{y, x}, {(min_i + 2) % 4, s.first.first}});
    }
    else
    {
        int s_num = arr[y][x];
        arr[y][x] = 0;
        arr[y + dy[min_i]][x + dx[min_i]] = s_num;
        s.second.first = y + dy[min_i];
        s.second.second = x + dx[min_i];
    }

    while (!q.empty())
    {
        int sy = q.front().first.first;
        int sx = q.front().first.second;
        int sd = q.front().second.first;
        int sn = q.front().second.second;
        q.pop();
        scrash(sy, sx, sd, sn);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(arr, 0, sizeof(arr));
    memset(kijul, 0, sizeof(kijul));
    memset(crash, false, sizeof(crash));

    cin >> n >> m >> p >> c >> d;
    cin >> ry >> rx;
    ry--;
    rx--;
    arr[ry][rx] = 50;

    for (int i = 0; i < p; i++)
    {
        int s_num, sy, sx;
        cin >> s_num >> sy >> sx;
        arr[sy - 1][sx - 1] = s_num;
        santa.push_back({{s_num, 0}, {sy - 1, sx - 1}});
    }

    sort(santa.begin(), santa.end());

    for (int i = 0; i < m; i++)
    {
        memset(crash, false, sizeof(crash));
        // rudolph move
        rmove();

        // cout << '\n';
        // for (int r = 0; r < n; r++)
        // {
        //     for (int c = 0; c < n; c++)
        //     {
        //         cout << arr[r][c] << " ";
        //     }
        //     cout << '\n';
        // }
        // cout << '\n';

        // santas move
        for (auto &s : santa)
        {
            if (s.second.first == -1 || crash[s.first.first - 1])
                continue;

            if (kijul[s.first.first - 1] == 0)
            {
                smove(s);
            }
            else
            {
                kijul[s.first.first - 1]--;
            }
        }

        // cout << '\n';
        // for (int r = 0; r < n; r++)
        // {
        //     for (int c = 0; c < n; c++)
        //     {
        //         cout << arr[r][c] << " ";
        //     }
        //     cout << '\n';
        // }
        // cout << '\n';

        bool alldead = true;
        for (auto &s : santa)
        {
            if (s.second.first != -1)
            {
                s.first.second++;
                alldead = false;
            }
        }

        if (alldead || isdead == p)
        {
            break;
        }

        // cout << i << '\n';
        // for (auto &s : santa)
        // {
        //     string dead = (s.second.first == -1) ? " " : "! ";
        //     cout << s.first.second << " ";
        // }
        // cout << '\n';
    }

    for (auto &s : santa)
    {
        cout << s.first.second << " ";
    }
}