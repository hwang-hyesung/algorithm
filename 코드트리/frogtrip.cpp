#include <bits/stdc++.h>
using namespace std;

int Q, N;
int dy[] = {-1, 0, 1, 0}, dx[] = {0, -1, 0, 1};
int arr[55][55], dist[6][55][55];
bool isMove[55][55][55][55];

struct Node
{
    int cost, r, c, jump;
    bool operator<(const Node &other) const
    {
        return cost > other.cost;
    }
};

void buildMove()
{
    memset(isMove, 0, sizeof(isMove));

    for (int r = 1; r <= N; r++)
    {
        for (int c = 1; c <= N; c++)
        {
            if (arr[r][c] != '.')
                continue;

            for (int d = 0; d < 4; d++)
            {
                for (int len = 1; len <= 5; len++)
                {
                    int nr = r + dy[d] * len;
                    int nc = c + dx[d] * len;

                    if (nr < 1 || nr > N || nc < 1 || nc > N)
                        break;
                    if (arr[nr][nc] == '#')
                        break;
                    if (arr[nr][nc] == 'S')
                        continue;

                    isMove[r][c][nr][nc] = true;
                }
            }
        }
    }
}

int incCost(int from, int to)
{
    int sum = 0;
    for (int j = from + 1; j <= to; j++)
        sum += j * j;
    return sum;
}

int plan(int r1, int c1, int r2, int c2)
{
    const int INF = 1e9;
    for (int j = 1; j <= 5; j++)
        for (int r = 1; r <= N; r++)
            for (int c = 1; c <= N; c++)
                dist[j][r][c] = INF;

    priority_queue<Node> pq;
    dist[1][r1][c1] = 0;
    pq.push({0, r1, c1, 1});

    while (!pq.empty())
    {
        int cost = pq.top().cost;
        int r = pq.top().r;
        int c = pq.top().c;
        int jump = pq.top().jump;
        pq.pop();

        if (dist[jump][r][c] != cost)
            continue;

        for (int d = 0; d < 4; d++)
        {
            int nr = r + dy[d] * jump;
            int nc = c + dx[d] * jump;
            if (nr < 1 || nr > N || nc < 1 || nc > N)
                continue;
            if (!isMove[r][c][nr][nc])
                continue;

            int ncost = cost + 1;
            if (dist[jump][nr][nc] > ncost)
            {
                dist[jump][nr][nc] = ncost;
                pq.push({ncost, nr, nc, jump});
            }
        }

        for (int nj = jump + 1; nj <= 5; nj++)
        {
            int add = incCost(jump, nj);
            for (int d = 0; d < 4; d++)
            {
                int nr = r + dy[d] * nj;
                int nc = c + dx[d] * nj;
                if (nr < 1 || nr > N || nc < 1 || nc > N)
                    continue;
                if (!isMove[r][c][nr][nc])
                    continue;

                int ncost = cost + add + 1;
                if (dist[nj][nr][nc] > ncost)
                {
                    dist[nj][nr][nc] = ncost;
                    pq.push({ncost, nr, nc, nj});
                }
            }
        }

        for (int nj = 1; nj < jump; nj++)
        {
            for (int d = 0; d < 4; d++)
            {
                int nr = r + dy[d] * nj;
                int nc = c + dx[d] * nj;
                if (nr < 1 || nr > N || nc < 1 || nc > N)
                    continue;
                if (!isMove[r][c][nr][nc])
                    continue;

                int ncost = cost + 2;
                if (dist[nj][nr][nc] > ncost)
                {
                    dist[nj][nr][nc] = ncost;
                    pq.push({ncost, nr, nc, nj});
                }
            }
        }
    }

    int ans = INF;
    for (int j = 1; j <= 5; j++)
        ans = min(ans, dist[j][r2][c2]);
    return ans == INF ? -1 : ans;
}

int main()
{
    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        string str;
        cin >> str;
        for (int j = 1; j <= N; j++)
        {
            arr[i][j] = str[j - 1];
        }
    }

    buildMove();

    cin >> Q;
    for (int i = 0; i < Q; i++)
    {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        cout << plan(r1, c1, r2, c2) << "\n";
    }

    return 0;
}