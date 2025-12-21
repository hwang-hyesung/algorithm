#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, m;
vector<list<pair<ll, ll>>> belt;
vector<int> alive;
vector<int> nextBelt;

unordered_map<ll, pair<int, list<pair<ll, ll>>::iterator>> mp;

int findNext(int x)
{
    if (nextBelt[x] == x)
        return x;
    return nextBelt[x] = findNext(nextBelt[x]);
}

void init()
{
    cin >> n >> m;

    belt.assign(m + 1, list<pair<ll, ll>>());
    alive.assign(m + 1, 1);
    nextBelt.resize(m + 2);

    for (int i = 1; i <= m; i++)
        nextBelt[i] = i;
    nextBelt[m + 1] = m + 1;

    mp.clear();

    vector<ll> id(n), w(n);
    for (int i = 0; i < n; i++)
        cin >> id[i];
    for (int i = 0; i < n; i++)
        cin >> w[i];

    int num = n / m;
    for (int i = 0; i < n; i++)
    {
        int bnum = i / num + 1;
        belt[bnum].push_back({id[i], w[i]});
        auto it = prev(belt[bnum].end());
        mp[id[i]] = {bnum, it};
    }
}

ll takeoffBox(ll wmax)
{
    ll total = 0;

    for (int i = 1; i <= m; i++)
    {
        if (!alive[i] || belt[i].empty())
            continue;

        auto it = belt[i].begin();
        ll id = it->first;
        ll weight = it->second;

        belt[i].erase(it);

        if (weight <= wmax)
        {
            total += weight;
            mp.erase(id);
        }
        else
        {
            belt[i].push_back({id, weight});
            auto nit = prev(belt[i].end());
            mp[id] = {i, nit};
        }
    }
    return total;
}

ll deleteBox(ll rid)
{
    if (mp.find(rid) == mp.end())
        return -1;

    auto [bnum, it] = mp[rid];
    belt[bnum].erase(it);
    mp.erase(rid);
    return rid;
}

ll checkBox(ll fid)
{
    if (mp.find(fid) == mp.end())
        return -1;

    auto [bnum, it] = mp[fid];

    belt[bnum].splice(
        belt[bnum].end(),
        belt[bnum],
        belt[bnum].begin(),
        it);

    return bnum;
}

ll brokeBelt(ll bnum)
{
    if (!alive[bnum])
        return -1;

    alive[bnum] = 0;

    int nxt = bnum % m + 1;
    nextBelt[bnum] = nxt;

    int nb = findNext(bnum);

    if (!alive[nb])
        return bnum;

    for (auto &p : belt[bnum])
    {
        belt[nb].push_back(p);
        auto it = prev(belt[nb].end());
        mp[p.first] = {nb, it};
    }

    belt[bnum].clear();
    return bnum;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    while (q--)
    {
        ll code;
        cin >> code;

        if (code == 100)
        {
            init();
        }
        else if (code == 200)
        {
            ll wmax;
            cin >> wmax;
            cout << takeoffBox(wmax) << "\n";
        }
        else if (code == 300)
        {
            ll rid;
            cin >> rid;
            cout << deleteBox(rid) << "\n";
        }
        else if (code == 400)
        {
            ll fid;
            cin >> fid;
            cout << checkBox(fid) << "\n";
        }
        else if (code == 500)
        {
            ll bnum;
            cin >> bnum;
            cout << brokeBelt(bnum) << "\n";
        }
    }
    return 0;
}
