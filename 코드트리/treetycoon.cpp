#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
int n, m, d, p, total, a[16][16];
int dy[] = {0, -1, -1, -1, 0, 1, 1, 1};
int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
vector<pair<int, int>> yyj;
int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> a[i][j];
        }
    }

    yyj.push_back(make_pair(n - 2, 0));
    yyj.push_back(make_pair(n - 2, 1));
    yyj.push_back(make_pair(n - 1, 0));
    yyj.push_back(make_pair(n - 1, 1));

    while (m--)
    {
        cin >> d >> p;
        d--;
        for (int i = 0; i < yyj.size(); i++)
        { // 영양제 이동
            yyj[i].first = (yyj[i].first + p * dy[d] + n) % n;
            yyj[i].second = (yyj[i].second + p * dx[d] + n) % n;
            a[yyj[i].first][yyj[i].second]++;
        }

        for (int i = 0; i < yyj.size(); i++)
        { // 영양제 대각선
            for (int j = 1; j < 8; j += 2)
            {
                int ny = yyj[i].first + dy[j];
                int nx = yyj[i].second + dx[j];
                if (ny < 0 || nx < 0 || ny >= n || nx >= n)
                    continue;
                if (a[ny][nx] >= 1)
                {
                    a[yyj[i].first][yyj[i].second]++;
                }
            }
        }

        vector<pair<int, int>> temp;
        for (int i = 0; i < n; i++)
        { // 영양제 갱신
            for (int j = 0; j < n; j++)
            {
                bool flag = true;
                for (int k = 0; k < yyj.size(); k++)
                {
                    if (yyj[k].first == i && yyj[k].second == j)
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag && a[i][j] >= 2)
                {
                    a[i][j] -= 2;
                    temp.push_back(make_pair(i, j));
                }
            }
        }
        yyj = temp;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            total += a[i][j];
        }
    }
    cout << total;
    return 0;
}
