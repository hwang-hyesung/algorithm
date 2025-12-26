#include <iostream>
#include <vector>
using namespace std;

int n, k, cnt = 0, step = 0;
vector<pair<int, bool>> u;
vector<pair<int, bool>> d;

int main()
{
    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        int s;
        cin >> s;
        u.push_back({s, true});
    }
    for (int i = 0; i < n; i++)
    {
        int s;
        cin >> s;
        d.push_back({s, true});
    }

    while (cnt < k)
    {
        step++;

        if (!u.back().second)
            u.back().second = true;
        u.insert(u.begin(), d.back());
        d.insert(d.begin(), u.back());
        u.pop_back();
        d.pop_back();

        if (!u.back().second)
            u.back().second = true;

        for (int i = n - 2; i >= 0; i--)
        {
            if (u[i].second || !u[i + 1].second || u[i + 1].first <= 0)
                continue;
            u[i].second = true;
            u[i + 1].second = false;
            u[i + 1].first--;
            if (u[i + 1].first <= 0)
                cnt++;
        }

        if (u.front().first > 0 && u.front().second)
        {
            u.front().second = false;
            u.front().first--;
            if (u.front().first <= 0)
                cnt++;
        }

        cout << cnt << "\n";
        for (pair<int, int> p : u)
        {
            cout << "(" << p.first << "," << p.second << ")";
        }
        cout << "\n";
    }

    cout << step;
    return 0;
}