#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int n, m, h, k, rnd, ans = 0, finder = 0, dy[] = {0, 1, 0, -1}, dx[] = {1, 0, -1, 0};
vector<int> arr[100][100];
bool alive[10001];
pair<pair<int, int>, int> players[10001];
vector<pair<int, int>> route;
bool tree[100][100];

void init()
{
    route.clear();

    int y = n / 2;
    int x = n / 2;

    int dy[4] = {-1, 0, 1, 0};
    int dx[4] = {0, 1, 0, -1};

    route.push_back({y, x});

    int len = 1;
    int dir = 0;

    while (true)
    {
        for (int rep = 0; rep < 2; rep++)
        {
            for (int i = 0; i < len; i++)
            {
                y += dy[dir];
                x += dx[dir];

                if (y < 0 || y >= n || x < 0 || x >= n)
                    return;

                route.push_back({y, x});
            }
            dir = (dir + 1) % 4;
        }
        len++;
    }
}

bool inscope(pair<int, int> p)
{
    int disy = max((p.first - route[finder].first), (route[finder].first - p.first));
    int disx = max((p.second - route[finder].second), (route[finder].second - p.second));
    return disy + disx <= 3;
}

void movefinder()
{
    finder++;
    if (finder == route.size() - 1)
    {
        reverse(route.begin(), route.end());
        finder = 0;
    }
    int y = route[finder].first, x = route[finder].second;
    int ndy = route[finder + 1].first - y;
    int ndx = route[finder + 1].second - x;

    int cnt = 0;
    for (int i = 0; i < 3; i++)
    {
        if (y < 0 || y >= n || x < 0 || x >= n)
            break;
        if (!tree[y][x] && arr[y][x].size() > 0)
        {
            cnt += arr[y][x].size();
            for (int idx : arr[y][x])
            {
                alive[idx] = false;
            }
            arr[y][x].clear();
        }

        y += ndy;
        x += ndx;
    }
    ans += rnd * cnt;
}

void moveplayer(int idx)
{
    pair<pair<int, int>, int> &p = players[idx];
    int &y = p.first.first;
    int &x = p.first.second;
    int &d = p.second;

    int ny = y + dy[d], nx = x + dx[d];
    if (ny < 0 || ny >= n || nx < 0 || nx >= n)
    {
        d = (d + 2) % 4;
        ny = y + dy[d];
        nx = x + dx[d];
    }

    if (route[finder] != make_pair(ny, nx))
    {
        auto it = find(arr[y][x].begin(), arr[y][x].end(), idx);
        arr[y][x].erase(it);
        y = ny;
        x = nx;
        arr[y][x].push_back(idx);
    }
}

int main()
{
    memset(tree, false, sizeof(tree));
    memset(alive, true, sizeof(alive));
    cin >> n >> m >> h >> k;
    for (int i = 0; i < m; i++)
    {
        int y, x, d;
        cin >> y >> x >> d;
        players[i].first.first = y - 1;
        players[i].first.second = x - 1;
        players[i].second = d - 1;
        arr[y - 1][x - 1].push_back(i);
    }
    for (int i = 0; i < h; i++)
    {
        int y, x;
        cin >> y >> x;
        tree[y - 1][x - 1] = true;
    }

    init();

    for (rnd = 1; rnd <= k; rnd++)
    {
        for (int i = 0; i < m; i++)
        {
            if (alive[i] && inscope(players[i].first))
            {
                moveplayer(i);
            }
        }
        movefinder();
    }

    cout << ans;
    return 0;
}