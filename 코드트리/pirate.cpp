#include <bits/stdc++.h>
using namespace std;

struct Ship
{
    int id, p, r;
    int last;
};

unordered_map<int, Ship *> mp;
priority_queue<pair<int, int>> pq;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        int cmd;
        cin >> cmd;

        if (cmd == 100)
        {
            int N;
            cin >> N;
            while (N--)
            {
                Ship *s = new Ship();
                cin >> s->id >> s->p >> s->r;
                s->last = -100000;
                pq.push({s->p, -s->id});
                mp[s->id] = s;
            }
        }
        else if (cmd == 200)
        {
            Ship *s = new Ship();
            cin >> s->id >> s->p >> s->r;
            s->last = -100000;
            pq.push({s->p, -s->id});
            mp[s->id] = s;
        }
        else if (cmd == 300)
        {
            int id, pw;
            cin >> id >> pw;
            mp[id]->p = pw;
            pq.push({pw, -id});
        }
        else if (cmd == 400)
        {
            vector<pair<int, int>> ready;
            vector<int> used;
            long long damage = 0;

            while (!pq.empty() && used.size() < 5)
            {
                auto top = pq.top();
                pq.pop();
                int ship_id = -top.second;
                int power_in_pq = top.first;
                Ship *ship = mp[ship_id];

                if (power_in_pq != ship->p)
                    continue;

                if (t < ship->last + ship->r)
                {
                    ready.push_back(top);
                    continue;
                }

                damage += ship->p;
                ship->last = t;
                used.push_back(ship_id);
            }

            for (auto &p : ready)
                pq.push(p);
            for (int id : used)
                pq.push({mp[id]->p, -id});

            cout << damage << " " << used.size();
            for (int id : used)
                cout << " " << id;
            cout << "\n";
        }
    }

    return 0;
}
