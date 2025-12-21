#include <bits/stdc++.h>
using namespace std;
#define N 4
#define DIR 8
#define PDIR 4

int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1}, dx[] = {0, -1, -1, -1, 0, 1, 1, 1};
int pdy[] = {-1, 0, 1, 0}, pdx[] = {0, -1, 0, 1};
int mons[26][N][N][8];
int dead[N][N][3];
int m, t, py, px, turn = 1;

bool canMove(int y, int x)
{
    if (y < 0 || y >= N || x < 0 || x >= N)
        return false;
    if (dead[y][x][0] || dead[y][x][1] || dead[y][x][2])
        return false;
    if (y == py && x == px)
        return false;
    return true;
}

void move_mons()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int d = 0; d < DIR; d++)
            {
                if (mons[turn - 1][i][j][d] > 0)
                {
                    bool moved = false;
                    for (int dd = 0; dd < DIR; dd++)
                    {
                        int dir = (d + dd) % DIR;
                        int ny = i + dy[dir];
                        int nx = j + dx[dir];

                        if (canMove(ny, nx))
                        {
                            mons[turn][ny][nx][dir] += mons[turn - 1][i][j][d];
                            moved = true;
                            break;
                        }
                    }

                    if (!moved)
                        mons[turn][i][j][d] += mons[turn - 1][i][j][d];
                }
            }
        }
    }
}

void move_pacman()
{
    int best_cnt = -1;
    vector<int> best_path;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                int y = py, x = px;
                int cnt = 0;
                bool visited[4][4] = {};

                int dir[3] = {i, j, k};
                bool valid = true;

                for (int step = 0; step < 3; step++)
                {
                    y += pdy[dir[step]];
                    x += pdx[dir[step]];

                    if (y < 0 || y >= 4 || x < 0 || x >= 4)
                    {
                        valid = false;
                        break;
                    }

                    if (!visited[y][x])
                    {
                        visited[y][x] = true;
                        for (int d = 0; d < 8; d++)
                            cnt += mons[turn][y][x][d];
                    }
                }

                if (!valid)
                    continue;

                if (cnt > best_cnt)
                {
                    best_cnt = cnt;
                    best_path = {i, j, k};
                }
            }
        }
    }

    for (int d : best_path)
    {
        py += pdy[d];
        px += pdx[d];

        for (int i = 0; i < 8; i++)
        {
            if (mons[turn][py][px][i] > 0)
            {
                dead[py][px][2] = mons[turn][py][px][i];
                mons[turn][py][px][i] = 0;
            }
        }
    }
}

int countMons()
{
    int cnt = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int d = 0; d < DIR; d++)
            {
                cnt += mons[t][i][j][d];
            }
        }
    }
    return cnt;
}

int main()
{
    memset(mons, 0, sizeof(mons));
    cin >> m >> t >> py >> px;
    py--;
    px--;
    for (int i = 1; i <= m; i++)
    {
        int mr, mc, md;
        cin >> mr >> mc >> md;
        mons[0][mr - 1][mc - 1][md - 1]++;
    }

    for (turn = 1; turn <= t; turn++)
    {
        // move
        move_mons();

        // pacman move
        move_pacman();

        // body
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                for (int k = 0; k < 2; k++)
                {
                    dead[i][j][k] = dead[i][j][k + 1];
                }
                dead[i][j][2] = 0;
            }
        }

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                for (int d = 0; d < DIR; d++)
                {
                    mons[turn][i][j][d] += mons[turn - 1][i][j][d];
                }
            }
        }
    }

    cout << countMons();
    return 0;
}