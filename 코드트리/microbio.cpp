#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

int n, q, arr[20][20], visited[20][20], temp[20][20], width[55][4];
int dy[] = {-1, 1, 0, 0}, dx[] = {0, 0, -1, 1};
set<int> adj;
vector<pair<int, int>> w;

bool cmp(const pair<int, int> &a, const pair<int, int> &b)
{
    if (a.second != b.second)
        return a.second > b.second;
    else
        return a.first < b.first;
}

bool div_check(int i)
{
    memset(visited, 0, sizeof(visited));
    int cnt = 0;
    int min_r = n, min_c = n, max_r = -1, max_c = -1;
    for (int r = width[i][0]; r < width[i][2]; r++)
    {
        for (int c = width[i][1]; c < width[i][3]; c++)
        {
            if (arr[r][c] == i)
            {
                min_r = min(min_r, r);
                min_c = min(min_c, c);
                max_r = max(max_r, r);
                max_c = max(max_c, c);
                if (visited[r][c] != 0)
                    continue;
                cnt++;
                visited[r][c] = 1;
                queue<pair<int, int>> q;
                int y = r;
                int x = c;
                q.push({y, x});
                while (!q.empty())
                {
                    y = q.front().first;
                    x = q.front().second;
                    q.pop();

                    for (int d = 0; d < 4; d++)
                    {
                        int ny = y + dy[d];
                        int nx = x + dx[d];
                        if (ny < 0 || ny >= n || nx < 0 || nx >= n || visited[ny][nx] != 0 || arr[ny][nx] != i)
                            continue;
                        else
                        {
                            visited[ny][nx] = 1;
                            q.push({ny, nx});
                        }
                    }
                }
            }
        }
    }
    width[i][0] = min_r;
    width[i][1] = min_c;
    width[i][2] = max_r + 1;
    width[i][3] = max_c + 1;
    return cnt == 1;
}

void discard()
{
    for (int i : adj)
    {
        if (!div_check(i))
        {
            for (int r = width[i][0]; r < width[i][2]; r++)
            {
                for (int c = width[i][1]; c < width[i][3]; c++)
                {
                    if (arr[r][c] == i)
                    {
                        arr[r][c] = 0;
                    }
                }
            }
            width[i][0] = -1;
            width[i][1] = -1;
            width[i][2] = -1;
            width[i][3] = -1;
            w[i - 1].second = -1;
        }
    }
}

bool loc_check(int y, int x, int i)
{
    int r1 = width[i][0];
    int c1 = width[i][1];
    int r2 = width[i][2];
    int c2 = width[i][3];

    for (int r = r1; r < r2; r++)
    {
        for (int c = c1; c < c2; c++)
        {
            if (arr[r][c] == i)
            {
                int ny = y + r - r1;
                int nx = x + c - c1;

                if (ny < 0 || ny >= n || nx < 0 || nx >= n)
                    return false;
                if (temp[ny][nx] != 0)
                    return false;
            }
        }
    }
    return true;
}

void move(int y, int x, int i)
{
    int r1 = width[i][0];
    int c1 = width[i][1];
    int r2 = width[i][2];
    int c2 = width[i][3];

    for (int r = r1; r < r2; r++)
    {
        for (int c = c1; c < c2; c++)
        {
            if (arr[r][c] == i && temp[y + r - r1][x + c - c1] == 0)
            {
                temp[y + r - r1][x + c - c1] = i;
            }
        }
    }

    width[i][0] = y;
    width[i][1] = x;
    width[i][2] = y + r2 - r1;
    width[i][3] = x + c2 - c1;
}

void relocate()
{
    vector<pair<int, int>> sw = w;
    sort(sw.begin(), sw.end(), cmp);
    memset(temp, 0, sizeof(temp));

    for (pair<int, int> &i : sw)
    {
        if (i.second == -1)
            continue;
        bool moved = false;
        for (int r = 0; r < n; r++)
        {
            for (int c = 0; c < n; c++)
            {
                if (moved)
                    break;
                if (loc_check(r, c, i.first))
                {
                    move(r, c, i.first);
                    moved = true;
                }
            }
            if (moved)
                break;
        }
        if (!moved)
        {
            i.second = -1;
            width[i.first][0] = -1;
            width[i.first][1] = -1;
            width[i.first][2] = -1;
            width[i.first][3] = -1;
        }
    }

    for (int y = 0; y < n; y++)
    {
        for (int x = 0; x < n; x++)
        {
            arr[y][x] = temp[y][x];
        }
    }
}
int cal()
{
    int cnt = 0;
    int aadj[55][55] = {0};

    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            int a = arr[r][c];
            if (a == 0 || w[a - 1].second == -1)
                continue;

            for (int d = 0; d < 4; d++)
            {
                int ny = r + dy[d];
                int nx = c + dx[d];
                if (ny < 0 || ny >= n || nx < 0 || nx >= n)
                    continue;

                int b = arr[ny][nx];
                if (b == 0 || a == b || w[b - 1].second == -1)
                    continue;

                if (aadj[a][b] == 0 && aadj[b][a] == 0)
                {
                    cnt += w[a - 1].second * w[b - 1].second;
                    aadj[a][b] = aadj[b][a] = 1;
                }
            }
        }
    }

    return cnt;
}

int main()
{
    cin >> n >> q;
    memset(arr, 0, sizeof(arr));
    for (int i = 1; i <= q; i++)
    {
        adj.clear();
        w.push_back({i, 0});

        cin >> width[i][0] >> width[i][1] >> width[i][2] >> width[i][3];
        for (int r = width[i][0]; r < width[i][2]; r++)
        {
            for (int c = width[i][1]; c < width[i][3]; c++)
            {
                if (arr[r][c] != 0)
                {
                    adj.insert(arr[r][c]);
                    w[arr[r][c] - 1].second--;
                }
                arr[r][c] = i;
                w[i - 1].second++;
            }
        }

        // 나눠지면 버리기
        discard();

        // 재배치
        relocate();

        // cout << "\n"
        //      << i << ": \n";
        // for (int r = 0; r < n; r++)
        // {
        //     for (int c = 0; c < n; c++)
        //     {
        //         cout << arr[r][c] << " ";
        //     }
        //     cout << "\n";
        // }
        // cout << "\n";

        // 결과 기록
        cout << cal() << "\n";
    }
}
