#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <algorithm>
using namespace std;

int N, M, arr[26][26], ans = 0;
int dy[] = {0, 1, 0, -1}, dx[] = {1, 0, -1, 0};
bool visited[26][26];
vector<pair<int, int>> route;

void init()
{
    memset(visited, false, sizeof(visited));
    int y = 0, x = 0, d = 0;
    route.push_back({y, x});
    visited[y][x] = true;
    while (true)
    {
        int ny = y + dy[d];
        int nx = x + dx[d];
        if (ny < 0 || ny >= N || nx < 0 || nx >= N || visited[ny][nx])
        {
            d = (d + 1) % 4;
            continue;
        }
        route.insert(route.begin(), {ny, nx});
        visited[ny][nx] = true;
        y = ny;
        x = nx;
        if (y == N / 2 && x == N / 2)
            break;
    }
}

void fillBlank()
{
    vector<int> temp;
    for (int i = 1; i < route.size(); i++)
    {
        int y = route[i].first;
        int x = route[i].second;
        if (arr[y][x] != 0)
            temp.push_back(arr[y][x]);
    }

    memset(arr, 0, sizeof(arr));
    for (int i = 0; i < temp.size() && i + 1 < route.size(); i++)
    {
        int y = route[i + 1].first;
        int x = route[i + 1].second;
        arr[y][x] = temp[i];
    }
}

int popGroup()
{
    int cn = -1, cc = -1, si = -1, res = 0;
    for (int i = 1; i < route.size(); i++)
    {
        int y = route[i].first;
        int x = route[i].second;
        if (arr[y][x] == 0)
            break;

        if (arr[y][x] != cn)
        {
            if (cc > 3)
            {
                for (int j = si; j < si + cc; j++)
                {
                    int py = route[j].first;
                    int px = route[j].second;
                    arr[py][px] = 0;
                }
                res += cn * cc;
            }
            si = i;
            cc = 0;
            cn = arr[y][x];
        }
        cc++;
    }
    if (cc > 3)
    {
        for (int j = si; j < si + cc; j++)
        {
            int py = route[j].first;
            int px = route[j].second;
            arr[py][px] = 0;
        }
        res += cn * cc;
    }
    return res;
}

void makeNewMons()
{
    vector<int> temp;
    int cn = -1, cc = 0;

    for (int i = 1; i < route.size(); i++)
    {
        int y = route[i].first;
        int x = route[i].second;
        if (arr[y][x] == 0)
            break;

        if (arr[y][x] != cn)
        {
            if (cn != -1)
            {
                temp.push_back(cc);
                temp.push_back(cn);
            }
            cn = arr[y][x];
            cc = 0;
        }
        cc++;
    }

    if (cn != -1)
    {
        temp.push_back(cc);
        temp.push_back(cn);
    }

    memset(arr, 0, sizeof(arr));
    for (int i = 1; i < route.size() && i - 1 < temp.size(); i++)
    {
        int y = route[i].first;
        int x = route[i].second;
        arr[y][x] = temp[i - 1];
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

    init();

    for (int i = 0; i < M; i++)
    {
        int d, p;
        cin >> d >> p;
        map<int, int> cnt;
        for (int j = 1; j <= p; j++)
        {
            int ny = N / 2 + dy[d] * j;
            int nx = N / 2 + dx[d] * j;
            if (ny < 0 || ny >= N || nx < 0 || nx >= N)
                break;
            cnt[arr[ny][nx]]++;
            arr[ny][nx] = 0;
        }

        for (pair<int, int> c : cnt)
        {
            ans += c.first * c.second;
        }
        while (true)
        {
            fillBlank();
            int score = popGroup();
            if (score == 0)
                break;
            ans += score;
        }
        makeNewMons();
    }
    cout << ans;
    return 0;
}