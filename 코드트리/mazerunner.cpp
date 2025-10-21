#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, k, ey, ex, dist = 0, a[11][11], dy[] = {-1, 1, 0, 0}, dx[] = {0, 0, -1, 1}, escape = 0;
vector<pair<int, int>> v;

void move(int idx)
{
    int y = v[idx].first;
    int x = v[idx].second;
    if (y == -1)
        return;
    int mindist = abs(ey - y) + abs(ex - x);
    for (int i = 0; i < 4; i++)
    {
        int ny = y + dy[i];
        int nx = x + dx[i];
        int newdist = abs(ey - ny) + abs(ex - nx);
        if (ny < 0 || nx < 0 || ny >= n || nx >= n || (a[ny][nx] > 0 && a[ny][nx] < 10) || newdist >= mindist)
            continue;
        if (ny == ey && nx == ex)
        {
            dist++;
            escape++;
            v[idx].first = -1;
            v[idx].second = -1;
            return;
        }
        else
        {
            dist++;
            v[idx].first = ny;
            v[idx].second = nx;
            return;
        }
    }
    return;
}
bool nemo(int r, int c, int w)
{
    if (r < 0 || c < 0 || r + w > n || c + w > n)
        return false;
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i].first == -1)
            continue;
        if (v[i].first >= r && v[i].first < r + w && v[i].second >= c && v[i].second < c + w)
            return true;
    }
    return false;
}

void rotate()
{
    // 작은 사각형 찾기
    int my, mx, width;
    bool flag = false;
    for (int w = 2; w <= n; w++)
    {
        for (int r = ey - w + 1; r <= ey; r++)
        {
            for (int c = ex - w + 1; c <= ex; c++)
            {
                flag = nemo(r, c, w);
                if (flag)
                {
                    my = r;
                    mx = c;
                    width = w;
                    break;
                }
            }
            if (flag)
                break;
        }
        if (flag)
            break;
    }

    // rotate
    int temp[11][11];
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[j][width - 1 - i] = a[my + i][mx + j];
        }
    }
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (temp[i][j] == -1)
            { // 출구갱신
                ey = my + i;
                ex = mx + j;
            }
            else if (temp[i][j] > 0 && temp[i][j] < 10)
            { // 벽 내구도 약화
                temp[i][j]--;
            }
            a[my + i][mx + j] = temp[i][j];
        }
    }

    // 기사 갱신
    for (int i = 0; i < v.size(); i++)
    {
        int y = v[i].first;
        int x = v[i].second;
        if (y == -1)
            continue;
        if (y >= my && y < my + width && x >= mx && x < mx + width)
        {
            v[i].first = my + x - mx;
            v[i].second = mx + (width - 1 - y + my);
        }
    }
}
int main()
{
    cin >> n >> m >> k;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> a[i][j];
        }
    }

    for (int i = 0; i < m; i++)
    {
        int r, c;
        cin >> r >> c;
        r--;
        c--;
        v.push_back(make_pair(r, c));
    }

    cin >> ey >> ex;
    ey--;
    ex--;
    a[ey][ex] = -1;
    while (k--)
    {
        for (int i = 0; i < v.size(); i++)
        {
            move(i);
        }
        if (escape == m)
            break;
        rotate();
    }
    cout << dist << "\n"
         << ey + 1 << " " << ex + 1;
    return 0;
}
