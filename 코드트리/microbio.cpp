#include <bits/stdc++.h>
using namespace std;

int N, Q;
int dy[] = {-1, 0, 1, 0}, dx[] = {0, -1, 0, 1};
vector<vector<int>> board, nextBoard;
map<int, int> width;
struct Node
{
    int idx, y, x, w;
    vector<pair<int, int>> cells;
};

struct Cmp
{
    bool operator()(const Node &a, const Node &b) const
    {
        if (a.w != b.w)
            return a.w < b.w;
        return a.idx > b.idx;
    }
};

Node bfsComponent(int sy, int sx, vector<vector<int>> &visited)
{
    queue<pair<int, int>> q;
    q.push({sy, sx});
    visited[sy][sx] = 1;

    int val = board[sy][sx];
    vector<pair<int, int>> cells;
    cells.push_back({sy, sx});

    int minY = sy, minX = sx;

    while (!q.empty())
    {
        auto [y, x] = q.front();
        q.pop();

        if (y < minY || (y == minY && x < minX))
        {
            minY = y;
            minX = x;
        }

        for (int d = 0; d < 4; d++)
        {
            int ny = y + dy[d];
            int nx = x + dx[d];

            if (ny < 0 || ny >= N || nx < 0 || nx >= N)
                continue;
            if (visited[ny][nx])
                continue;
            if (board[ny][nx] != val)
                continue;

            visited[ny][nx] = 1;
            q.push({ny, nx});
            cells.push_back({ny, nx});
        }
    }

    Node res;
    res.idx = val;
    res.y = minY;
    res.x = minX;
    res.w = (int)cells.size();
    res.cells = cells;
    return res;
}

priority_queue<Node, vector<Node>, Cmp> findSeparated()
{
    vector<vector<int>> visited(N, vector<int>(N, 0));
    map<int, Node> remain;
    set<int> removed;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (visited[i][j])
                continue;
            if (board[i][j] == 0)
                continue;

            Node comp = bfsComponent(i, j, visited);
            int val = comp.idx;

            if (removed.count(val))
                continue;

            if (remain.count(val))
            {
                remain.erase(val);
                removed.insert(val);
            }
            else
            {
                remain[val] = comp;
            }
        }
    }

    priority_queue<Node, vector<Node>, Cmp> pq;
    for (auto &p : remain)
        pq.push(p.second);

    return pq;
}

bool check(int y, int x, const Node &n)
{
    for (auto &cell : n.cells)
    {
        int oy = cell.first - n.y;
        int ox = cell.second - n.x;

        int ny = y + oy;
        int nx = x + ox;

        if (ny < 0 || ny >= N || nx < 0 || nx >= N)
            return false;
        if (nextBoard[ny][nx] != 0)
            return false;
    }
    return true;
}

int moveMicrobe(int y, int x, const Node &n)
{
    int score = 0;
    set<int> adj;
    for (auto &cell : n.cells)
    {
        int oy = cell.first - n.y;
        int ox = cell.second - n.x;

        int ny = y + oy;
        int nx = x + ox;

        nextBoard[ny][nx] = n.idx;

        for (int i = 0; i < 4; i++)
        {
            int ay = ny + dy[i];
            int ax = nx + dx[i];
            if (ay < 0 || ay >= N || ax < 0 || ax >= N || nextBoard[ay][ax] == 0 || nextBoard[ay][ax] == n.idx)
                continue;
            adj.insert(nextBoard[ay][ax]);
        }
    }
    for (int aidx : adj)
    {
        score += n.w * width[aidx];
    }
    width[n.idx] = n.w;
    return score;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> Q;
    board.assign(N, vector<int>(N, 0));
    nextBoard.assign(N, vector<int>(N, 0));

    for (int q = 1; q <= Q; q++)
    {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        for (int i = r1; i < r2; i++)
            for (int j = c1; j < c2; j++)
                board[i][j] = q;

        nextBoard.assign(N, vector<int>(N, 0));
        width.clear();

        auto pq = findSeparated();
        int score = 0;

        while (!pq.empty())
        {
            Node n = pq.top();
            pq.pop();

            bool placed = false;

            for (int y = 0; y < N && !placed; y++)
            {
                for (int x = 0; x < N; x++)
                {
                    if (!check(y, x, n))
                        continue;

                    score += moveMicrobe(y, x, n);
                    placed = true;
                    break;
                }
            }
        }

        board = nextBoard;

        cout << score << '\n';
    }

    return 0;
}