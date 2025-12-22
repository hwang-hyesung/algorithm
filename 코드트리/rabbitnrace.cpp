#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cmath>
#include <algorithm>
using namespace std;

struct Rabbit
{
    int id, i, cnt = 0, y = 0, x = 0;
    long long score = 0, dist;
    bool isrunned = false;

    Rabbit(int i, int id, long long dist)
    {
        this->i = i;
        this->id = id;
        this->dist = dist;
    }
};

struct cmp
{
    bool operator()(Rabbit a, Rabbit b)
    {
        return make_tuple(a.cnt, a.y + a.x, a.y, a.x, a.id) > make_tuple(b.cnt, b.y + b.x, b.y, b.x, b.id);
    }
};

int Q, N, M, P;
long long zero = 0;
int dy[] = {1, 0, 0, -1}, dx[] = {0, 1, -1, 0};
vector<Rabbit> players;
map<int, int> idx;

pair<int, int> move(int y, int x, long long d)
{
    int ny, nx, by = -1, bx = -1, bs = -2;
    int periodY = 2 * (N - 1);
    int periodX = 2 * (M - 1);

    for (int i = 0; i < 4; i++)
    {
        ny = (y + dy[i] * d) % periodY;
        if (ny < 0)
            ny += periodY;
        if (ny >= N)
            ny = periodY - ny;

        nx = (x + dx[i] * d) % periodX;
        if (nx < 0)
            nx += periodX;
        if (nx >= M)
            nx = periodX - nx;

        if (make_tuple(ny + nx, ny, nx) > make_tuple(bs, by, bx))
        {
            bs = ny + nx;
            by = ny;
            bx = nx;
        }
    }
    return {by, bx};
}

void race(int k, int s)
{
    priority_queue<Rabbit, vector<Rabbit>, cmp> q;
    for (Rabbit &r : players)
    {
        q.push(r);
    }
    for (int i = 0; i < k; i++)
    {
        Rabbit &r = players[q.top().i];
        q.pop();
        pair<int, int> loc = move(r.y, r.x, r.dist);

        int ny = loc.first;
        int nx = loc.second;
        r.y = ny;
        r.x = nx;
        r.score -= (ny + nx + 2);
        r.cnt++;
        r.isrunned = true;
        zero += (ny + nx + 2);
        q.push(r);
    }
    Rabbit best = Rabbit(-1, -1, -1);
    for (Rabbit &r : players)
    {
        if (!r.isrunned)
            continue;
        if (make_tuple(r.y + r.x, r.y, r.x, r.id) > make_tuple(best.y + best.x, best.y, best.x, best.id))
        {
            best = r;
        }
        r.isrunned = false;
    }
    players[best.i].score += s;
}

int main()
{
    cin >> Q;

    int cmd;
    cin >> cmd >> N >> M >> P;
    for (int i = 0; i < P; i++)
    {
        int pid, d;
        cin >> pid >> d;
        players.push_back(Rabbit(i, pid, d));
        idx[pid] = i;
    }

    for (int q = 1; q < Q - 1; q++)
    {
        cin >> cmd;
        if (cmd == 200)
        {
            int k, s;
            cin >> k >> s;
            race(k, s);
        }
        else if (cmd == 300)
        {
            int pid;
            long long l;
            cin >> pid >> l;
            players[idx[pid]].dist *= l;
        }
    }

    cin >> cmd;
    long long mxs = -999999999;
    for (Rabbit r : players)
    {
        if (mxs < (long long)r.score + zero)
            mxs = (long long)r.score + zero;
    }
    cout << mxs;
    return 0;
}