#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <cmath>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<pair<int, int>> b;
    vector<int> boom;
    for (int i = 1; i <= n; i++)
    {
        int balloon;
        cin >> balloon;
        b.push_back({balloon, i});
    }
    int idx = 0;
    while (!b.empty())
    {
        int next = b[idx].first;

        boom.push_back(b[idx].second);
        b.erase(b.begin() + idx);

        if (b.empty())
            break;

        if (next > 0)
            idx = (idx + next - 1) % b.size();
        else
            idx = ((idx + next) % (int)b.size() + (int)b.size()) % (int)b.size();

    }

    for (int i : boom)
    {
        cout << i << " ";
    }
}
