#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int main()
{
    int x;
    cin >> x;

    queue<pair<int, int>> q;
    q.push({x, 0});

    while (!q.empty())
    {
        int n = q.front().first;
        int idx = q.front().second;
        q.pop();

        if (n == 1)
        {
            cout << idx << "\n";
            return 0;
        }

        if (n % 3 == 0 && n / 3 > 0)
        {
            q.push({n / 3, idx + 1});
        }
        if (n % 2 == 0 && n / 2 > 0)
        {
            q.push({n / 2, idx + 1});
        }
        q.push({n - 1, idx + 1});
    }

    return 0;
}
