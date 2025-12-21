#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int n, arr[21][21];
int score[] = {0, 1, 10, 100, 1000};
int dy[] = {-1, 0, 0, 1}, dx[] = {0, -1, 1, 0};
bool like[401][401];

void find(int s)
{
    int mxcnt = -1, mxy = -1, mxx = -1;
    int emxcnt = -1;
    for (int y = 0; y < n; y++)
    {
        for (int x = 0; x < n; x++)
        {
            if (arr[y][x] != 0)
                continue;
            int cnt = 0, ecnt = 0;
            for (int d = 0; d < 4; d++)
            {
                int ny = y + dy[d], nx = x + dx[d];
                if (ny < 0 || ny >= n || nx < 0 || nx >= n)
                    continue;
                if (arr[ny][nx] == 0)
                    ecnt++;
                else if (like[s][arr[ny][nx]])
                    cnt++;
            }
            if (cnt > mxcnt)
            {
                mxcnt = cnt;
                emxcnt = ecnt;
                mxy = y;
                mxx = x;
            }
            else if (cnt == mxcnt && emxcnt < ecnt)
            {
                emxcnt = ecnt;
                mxy = y;
                mxx = x;
            }
        }
    }
    arr[mxy][mxx] = s;
}

int cal()
{
    int ans = 0;
    for (int y = 0; y < n; y++)
    {
        for (int x = 0; x < n; x++)
        {
            int s = arr[y][x], cnt = 0;
            for (int d = 0; d < 4; d++)
            {
                int ny = y + dy[d], nx = x + dx[d];
                if (ny < 0 || ny >= n || nx < 0 || nx >= n)
                    continue;
                if (like[s][arr[ny][nx]])
                    cnt++;
            }
            ans += score[cnt];
        }
    }
    return ans;
}
int main()
{
    memset(arr, 0, sizeof(arr));
    memset(like, false, sizeof(like));
    cin >> n;
    vector<int> prior;
    for (int i = 0; i < n * n; i++)
    {
        int n0, n1, n2, n3, n4;
        cin >> n0 >> n1 >> n2 >> n3 >> n4;
        prior.push_back(n0);
        like[n0][n1] = true;
        like[n0][n2] = true;
        like[n0][n3] = true;
        like[n0][n4] = true;
    }

    for (int stud : prior)
    {
        find(stud);
    }
    cout << cal();
    return 0;
}