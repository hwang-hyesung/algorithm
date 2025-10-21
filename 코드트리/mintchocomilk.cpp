#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, t, power[51][51], dy[] = {-1, 1, 0, 0}, dx[] = {0, 0, -1, 1};
string a[51][51], kind[] = {"T", "C", "M", "CM", "TM", "TC", "TCM"}; // 0 1 2 3 4 5 6
int heart[7], junpa[51][51], visited[51][51];
vector<pair<int, pair<int, int>>> king[3];

auto comp = [](const auto &a, const auto &b)
{
    if (a.first != b.first)
        return a.first > b.first; // power 내림차순
    if (a.second.second != b.second.second)
        return a.second.second < b.second.second; // y 오름차순
    return a.second.first < b.second.first;       // x 오름차순
};

void findKing(int y, int x)
{
    if (visited[y][x] != 0)
        return;
    int mp = power[y][x], my = y, mx = x, count = 0;
    string type = a[y][x];
    queue<pair<int, int>> q;
    q.push({y, x});
    visited[y][x] = 1;
    while (!q.empty())
    {
        y = q.front().first;
        x = q.front().second;
        q.pop();
        count++;
        for (int i = 0; i < 4; i++)
        {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (ny < 0 || nx < 0 || ny >= n || nx >= n || visited[ny][nx] != 0 || a[y][x] != a[ny][nx])
                continue;
            q.push({ny, nx});
            visited[ny][nx] = 1;
            if (mp < power[ny][nx])
            {
                mp = power[ny][nx];
                my = ny;
                mx = nx;
            }
            else if (mp == power[ny][nx])
            {
                if (ny < my)
                {
                    my = ny;
                    mx = nx;
                }
                else if (ny == my)
                {
                    if (nx < mx)
                    {
                        my = ny;
                        mx = nx;
                    }
                }
            }
        }
    }
    power[my][mx] += count;
    king[type.length() - 1].push_back({power[my][mx], {mx, my}});
}

// 같은 음식끼리 그룹 지어서 대표자(파워크고 가장 좌상단)에게 1씩 줌
void lunch()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            findKing(i, j);
        }
    }
}

// 대표자가 본인 파워%4 방향으로 본인 파워 -1 만큼 전파를 시도함
//  전파가 더 세면 같아지고 전파자는 상대 신앙심+1만큼 깎임
//  전차가 더 약하면 섞이고 전파자는 0 상대는 전파만큼 증가
//  전파 된 상대는 당일에 전파는 못함 계속 당할순 있음
void dinner()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < king[i].size(); j++)
        {
            int p = king[i][j].first - 1;
            int y = king[i][j].second.second;
            int x = king[i][j].second.first;
            string type = a[y][x];
            if (junpa[y][x] != 0)
                continue;
            // cout << type << " " << p << " " << y << " " << x <<"\n";
            int ny = y, nx = x;
            int d = (p + 1) % 4;
            power[y][x] = 1;
            while (true)
            {
                ny += dy[d];
                nx += dx[d];
                if (ny < 0 || nx < 0 || ny >= n || nx >= n || p <= 0)
                    break;
                if (a[ny][nx] == type)
                    continue;
                if (p > power[ny][nx])
                {
                    a[ny][nx] = type;
                    power[ny][nx]++;
                    junpa[ny][nx] = 1;
                    p -= power[ny][nx];
                    if (p <= 0)
                        break;
                }
                else
                {
                    string ntype = type + a[ny][nx];
                    string rtype = "";
                    if (ntype.find("T") != string::npos)
                        rtype += "T";
                    if (ntype.find("C") != string::npos)
                        rtype += "C";
                    if (ntype.find("M") != string::npos)
                        rtype += "M";
                    a[ny][nx] = rtype;
                    power[ny][nx] += p;
                    junpa[ny][nx] = 1;
                    break;
                }
            }
            // for(int i=0;i<n;i++){
            //     for(int j=0;j<n;j++){
            //         cout << a[i][j] << " ";
            //     }
            //     cout << "\n";
            // }
            // for(int i=0;i<n;i++){
            //     for(int j=0;j<n;j++){
            //         cout << power[i][j]<< " ";
            //     }
            //     cout << "\n";
            // }
        }
    }
}

void countHeart()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < 7; k++)
            {
                if (kind[k] == a[i][j])
                    heart[k] += power[i][j];
            }
        }
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> t;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            char aa;
            cin >> aa;
            a[i][j] = aa;
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> power[i][j];
        }
    }

    memset(heart, 0, sizeof(heart));
    while (t--)
    {
        memset(junpa, 0, sizeof(junpa));
        memset(visited, 0, sizeof(visited));
        memset(heart, 0, sizeof(heart));
        king[0].clear();
        king[1].clear();
        king[2].clear();

        lunch();

        sort(king[0].begin(), king[0].end(), comp);
        sort(king[1].begin(), king[1].end(), comp);
        sort(king[2].begin(), king[2].end(), comp);

        dinner();

        // for(int i=0;i<n;i++){
        //     for(int j=0;j<n;j++){
        //         cout << a[i][j] << " ";
        //     }
        //     cout << "\n";
        // }
        // for(int i=0;i<n;i++){
        //     for(int j=0;j<n;j++){
        //         cout << power[i][j] << " ";
        //     }
        //     cout << "\n";
        // }
        countHeart();
        for (int i = 6; i >= 0; i--)
        {
            cout << heart[i] << " ";
        }
        cout << "\n";
    }
}
