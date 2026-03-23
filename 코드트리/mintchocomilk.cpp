#include <bits/stdc++.h>
using namespace std;

int N, T, dy[] = {-1, 1, 0, 0}, dx[] = {0, 0, -1, 1};
string types[55][55];
int power[55][55];
bool visited[55][55], spread[55][55];
map<string, int> tmap;

struct Node
{
    string t;
    int y, x, p;
    bool operator<(const Node &other) const
    {
        if (t.length() != other.t.length())
            return t.length() > other.t.length();
        if (p != other.p)
            return p < other.p;
        if (y != other.y)
            return y > other.y;
        if (x != other.x)
            return x > other.x;
        return false;
    }
};

Node findTeam(int r, int c)
{
    Node n;
    n.t = types[r][c];
    n.y = r;
    n.x = c;
    n.p = power[r][c];
    queue<pair<int, int>> q;
    vector<pair<int, int>> v;
    q.push({r, c});
    visited[r][c] = 1;
    power[r][c]--;
    int cnt = 1;
    while (!q.empty())
    {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for (int d = 0; d < 4; d++)
        {
            int ny = y + dy[d];
            int nx = x + dx[d];
            if (ny < 0 || ny >= N || nx < 0 || nx >= N || visited[ny][nx] != 0 || types[ny][nx] != n.t)
                continue;
            q.push({ny, nx});
            visited[ny][nx] = 1;

            if (power[ny][nx] > n.p)
            {
                n.y = ny;
                n.x = nx;
                n.p = power[ny][nx];
            }
            else if (power[ny][nx] == n.p)
            {
                if (ny < n.y)
                {
                    n.y = ny;
                    n.x = nx;
                    n.p = power[ny][nx];
                }
                else if (ny == n.y)
                {
                    if (nx < n.x)
                    {
                        n.y = ny;
                        n.x = nx;
                        n.p = power[ny][nx];
                    }
                }
            }

            power[ny][nx]--;
            cnt++;
        }
    }
    power[n.y][n.x] += cnt;
    n.p = power[n.y][n.x];
    return n;
}

vector<int> count()
{
    vector<int> res(7, 0);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            res[tmap[types[i][j]]] += power[i][j];

    return res;
}

int main()
{
    cin >> N >> T;
    for (int i = 0; i < N; i++)
    {
        string str;
        cin >> str;
        for (int j = 0; j < N; j++)
        {
            types[i][j] = str[j];
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> power[i][j];
        }
    }

    tmap["CMT"] = 0;
    tmap["CT"] = 1;
    tmap["MT"] = 2;
    tmap["CM"] = 3;
    tmap["M"] = 4;
    tmap["C"] = 5;
    tmap["T"] = 6;

    while (T--)
    {
        memset(visited, 0, sizeof(visited));
        memset(spread, 0, sizeof(spread));

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                power[i][j]++;

        priority_queue<Node> pq;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (visited[i][j] == 0)
                {
                    pq.push(findTeam(i, j));
                }
            }
        }

        while (!pq.empty())
        {
            string t = pq.top().t;
            int y = pq.top().y;
            int x = pq.top().x;
            int p = pq.top().p;
            pq.pop();

            if (spread[y][x] != 0)
                continue;
            int desire = p - 1;
            int d = p % 4;
            int sy = y, sx = x;
            power[y][x] = 1;
            if (desire == 0)
                break;
            while (true)
            {
                sy += dy[d];
                sx += dx[d];
                if (sy < 0 || sy >= N || sx < 0 || sx >= N)
                    break;
                if (types[sy][sx] == t)
                    continue;
                spread[sy][sx] = 1;
                if (desire > power[sy][sx])
                {
                    types[sy][sx] = t;
                    power[sy][sx]++;
                    desire -= power[sy][sx];
                }
                else if (desire <= power[sy][sx])
                {
                    set<char> s;
                    for (char c : t)
                    {
                        s.insert(c);
                    }
                    for (char c : types[sy][sx])
                    {
                        s.insert(c);
                    }
                    string nt = "";
                    for (char c : s)
                    {
                        nt += c;
                    }
                    types[sy][sx] = nt;
                    power[sy][sx] += desire;
                    desire = 0;
                }
                if (desire <= 0)
                    break;
            }
        }

        vector<int> ans = count();
        for (int a : ans)
        {
            cout << a << " ";
        }
        cout << "\n";
    }
    return 0;
}