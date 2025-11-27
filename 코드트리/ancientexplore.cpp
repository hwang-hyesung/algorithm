#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>
using namespace std;

int k, m, a[6][6], visited[6][6];
int dy[] = {0, 1, 0, -1}, dx[] = {1, 0, -1, 0};
queue<int> piece;
void turn(int y, int x)
{
    int temp[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            temp[j][2 - i] = a[y + i][x + j];

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            a[y + i][x + j] = temp[i][j];
}

int dfs(int y, int x, int color)
{
    visited[y][x] = 1;
    int cnt = 1;
    for (int i = 0; i < 4; i++)
    {
        int ny = y + dy[i], nx = x + dx[i];
        if (ny < 0 || nx < 0 || ny >= 5 || nx >= 5)
            continue;
        if (!visited[ny][nx] && a[ny][nx] == color)
            cnt += dfs(ny, nx, color);
    }
    return cnt;
}

void mark(int y, int x, int color)
{
    visited[y][x] = 2;
    for (int i = 0; i < 4; i++)
    {
        int ny = y + dy[i], nx = x + dx[i];
        if (ny < 0 || nx < 0 || ny >= 5 || nx >= 5)
            continue;
        if (visited[ny][nx] != 2 && a[ny][nx] == color)
            mark(ny, nx, color);
    }
}

int find_and_mark()
{
    memset(visited, 0, sizeof(visited));
    int total = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (!visited[i][j])
            {
                int cnt = dfs(i, j, a[i][j]);
                if (cnt >= 3)
                {
                    total += cnt;
                    mark(i, j, a[i][j]);
                }
            }
        }
    }
    return total;
}

void fill()
{
    for (int col = 0; col < 5; col++)
    {
        for (int row = 4; row >= 0; row--)
        {
            if (visited[row][col] == 2)
            {
                a[row][col] = piece.front();
                piece.pop();
            }
        }
    }
    memset(visited, 0, sizeof(visited));
}

bool better(int removed, int y, int x, int t,
            int best_removed, int best_y, int best_x, int best_t)
{

    if (removed != best_removed)
        return removed > best_removed;

    if (t != best_t)
        return t < best_t;

    if (x != best_x)
        return x < best_x;

    return y < best_y;
}

int main()
{
    cin >> k >> m;

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            cin >> a[i][j];

    for (int i = 0; i < m; i++)
    {
        int p;
        cin >> p;
        piece.push(p);
    }

    while (k--)
    {
        int max_removed = 0, best_y = 0, best_x = 0, best_rot = 0;

        for (int i = 0; i <= 2; i++)
        {
            for (int j = 0; j <= 2; j++)
            {
                for (int t = 1; t <= 3; t++)
                {
                    turn(i, j);
                    int removed = find_and_mark();

                    if (better(removed, i, j, t, max_removed, best_y, best_x, best_rot))
                    {
                        max_removed = removed;
                        best_y = i;
                        best_x = j;
                        best_rot = t;
                    }
                }
                turn(i, j);
            }
        }

        if (max_removed == 0)
            break;

        for (int i = 0; i < best_rot; i++)
            turn(best_y, best_x);
        int round_score = 0;

        while (1)
        {
            int removed = find_and_mark();
            if (removed == 0)
                break;
            round_score += removed;
            fill();
        }

        cout << round_score << " ";
    }

    return 0;
}
