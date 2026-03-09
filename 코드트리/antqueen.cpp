#include <bits/stdc++.h>
using namespace std;

set<long long> houses;
map<int, long long> id_to_pos;
int next_id = 1;

bool check(vector<long long> &v, int r, long long mid)
{
    int m = v.size();
    int ants = 0;
    int i = 0;

    while (i < m)
    {
        ants++;
        if (ants > r)
            return false;
        long long reach = v[i] + mid;

        while (i < m && v[i] <= reach)
            i++;
    }
    return true;
}

long long patrol(int r)
{
    vector<long long> v(houses.begin(), houses.end());
    int m = v.size();

    if (m == 0)
        return 0;

    long long lo = 0, hi = v.back() - v.front();

    while (lo < hi)
    {
        long long mid = (lo + hi) / 2;
        if (check(v, r, mid))
            hi = mid;
        else
            lo = mid + 1;
    }

    return lo;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int Q;
    cin >> Q;

    while (Q--)
    {
        int cmd;
        cin >> cmd;

        if (cmd == 100)
        {
            int N;
            cin >> N;

            houses.clear();
            id_to_pos.clear();
            next_id = 1;

            for (int i = 0; i < N; i++)
            {
                long long x;
                cin >> x;
                id_to_pos[next_id++] = x;
                houses.insert(x);
            }
        }
        else if (cmd == 200)
        {
            long long p;
            cin >> p;
            id_to_pos[next_id++] = p;
            houses.insert(p);
        }
        else if (cmd == 300)
        {
            int q;
            cin >> q;
            long long pos = id_to_pos[q];
            id_to_pos.erase(q);
            houses.erase(houses.find(pos));
        }
        else if (cmd == 400)
        {
            int r;
            cin >> r;
            cout << patrol(r) << "\n";
        }
    }
}