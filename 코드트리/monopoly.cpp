#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 20
#define MAX_M 400
#define DIR_NUM 4
#define EMPTY make_pair(401, 401)
#define EMPTY_NUM 401

using namespace std;

int N, M, K, turn = 0;
int dy[] = {-1, 1, 0, 0}, dx[] = {0, 0, -1, 1};
int given_map[MAX_N][MAX_N];
int nextdir[MAX_M + 1][DIR_NUM][DIR_NUM];
pair<int, int> player[MAX_N][MAX_N];
pair<int, int> next_player[MAX_N][MAX_N];
pair<int, int> contract[MAX_N][MAX_N];

void move(int y, int x)
{
    int num = player[y][x].first;
    int dir = player[y][x].second;
    for (int d = 0; d < 4; d++)
    {
        int ny = y + dy[nextdir[num][dir][d]];
        int nx = x + dx[nextdir[num][dir][d]];
        if (ny < 0 || ny >= N || nx < 0 || nx >= N)
            continue;
        if (contract[ny][nx].first == EMPTY_NUM)
        {
            if (next_player[ny][nx].first > num)
            {
                next_player[ny][nx] = {num, nextdir[num][dir][d]};
            }
            return;
        }
    }

    for (int d = 0; d < 4; d++)
    {
        int ny = y + dy[nextdir[num][dir][d]];
        int nx = x + dx[nextdir[num][dir][d]];
        if (ny < 0 || ny >= N || nx < 0 || nx >= N)
            continue;
        if (contract[ny][nx].first == num)
        {
            if (next_player[ny][nx].first > num)
            {
                next_player[ny][nx] = {num, nextdir[num][dir][d]};
            }
            return;
        }
    }
}

bool end()
{
    if (turn >= 1000)
        return true;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            if (player[i][j] == EMPTY)
                continue;

            int num = player[i][j].first;

            if (num != 1)
                return false;
        }

    return true;
}
int main()
{
    cin >> N >> M >> K;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            cin >> given_map[i][j];
            if (given_map[i][j] == 0)
            {
                player[i][j] = EMPTY;
                contract[i][j] = EMPTY;
            }
        }

    for (int num = 1; num <= M; num++)
    {
        int move_dir;
        cin >> move_dir;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (given_map[i][j] == num)
                {
                    player[i][j] = make_pair(num, move_dir - 1);
                    contract[i][j] = make_pair(num, K);
                }
    }

    for (int num = 1; num <= M; num++)
        for (int curr_dir = 0; curr_dir < 4; curr_dir++)
            for (int i = 0; i < 4; i++)
            {
                cin >> nextdir[num][curr_dir][i];
                nextdir[num][curr_dir][i]--;
            }

    while (!end())
    {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                next_player[i][j] = EMPTY;

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (player[i][j] != EMPTY)
                    move(i, j);

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                player[i][j] = next_player[i][j];

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (contract[i][j].first != EMPTY_NUM)
                {
                    if (contract[i][j].second == 1)
                        contract[i][j] = EMPTY;
                    else
                        contract[i][j].second--;
                }

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (player[i][j] != EMPTY)
                    contract[i][j] = {player[i][j].first, K};

        turn++;
    }

    if (turn >= 1000)
        turn = -1;

    cout << turn;
}
