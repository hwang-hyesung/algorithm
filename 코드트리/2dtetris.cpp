#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define ROW 6
#define COL 4

int K, score = 0;
int ty[] = {1, 1, 2}, tx[] = {1, 2, 1};
vector<vector<bool>> yboard(6, vector<bool>(4, true)), rboard(6, vector<bool>(4, true));

int findRplace(int t, int y, int x)
{
    int row;
    for (row = ROW - tx[t]; row >= 0; row--)
    {
        for (int r = row; r < row + tx[t]; r++)
        {
            for (int c = y; c < y + ty[t]; c++)
            {
                if (!rboard[r][c])
                    return row + 1;
            }
        }
    }
    return row + 1;
}

int findYplace(int t, int y, int x)
{
    int row;
    for (row = 0; row + ty[t] <= ROW; row++)
    {
        for (int r = row; r < row + ty[t]; r++)
        {
            for (int c = x; c < x + tx[t]; c++)
            {
                if (!yboard[r][c])
                    return row - 1;
            }
        }
    }
    return row - 1;
}

void put(int t, int y, int x)
{
    int rr = findRplace(t, y, x);
    int yr = findYplace(t, y, x);

    for (int r = rr; r < rr + tx[t]; r++)
    {
        for (int c = y; c < y + ty[t]; c++)
        {
            rboard[r][c] = false;
        }
    }

    for (int r = yr; r < yr + ty[t]; r++)
    {
        for (int c = x; c < x + tx[t]; c++)
        {
            yboard[r][c] = false;
        }
    }
}

void full()
{
    vector<bool> temp(4, true);
    int row = ROW - 1;
    while (row >= 0)
    {
        int cnt = 0;
        for (int c = 0; c < COL; c++)
        {
            if (!yboard[row][c])
                cnt++;
        }
        if (cnt == 0)
            break;
        if (cnt == COL)
        {
            score++;
            yboard.erase(yboard.begin() + row);
            yboard.insert(yboard.begin(), temp);
        }
        else
        {
            row--;
        }
    }

    row = 0;
    while (row < ROW)
    {
        int cnt = 0;
        for (int c = 0; c < COL; c++)
        {
            if (!rboard[row][c])
            {
                cnt++;
            }
        }
        if (cnt == 0)
            break;
        if (cnt == COL)
        {
            score++;
            rboard.erase(rboard.begin() + row);
            rboard.push_back(temp);
        }
        else
        {
            row++;
        }
    }
}

void overflow()
{
    vector<bool> temp(4, true);

    int cnt = 0;
    for (int r = ROW - 1; r > ROW - 3; r--)
    {
        for (int c = 0; c < COL; c++)
        {
            if (!rboard[r][c])
            {
                cnt++;
                break;
            }
        }
    }

    for (int i = 0; i < cnt; i++)
    {
        rboard.erase(rboard.begin());
        rboard.push_back(temp);
    }

    cnt = 0;
    for (int r = 0; r < 2; r++)
    {
        for (int c = 0; c < COL; c++)
        {
            if (!yboard[r][c])
            {
                cnt++;
                break;
            }
        }
    }

    for (int i = 0; i < cnt; i++)
    {
        yboard.pop_back();
        yboard.insert(yboard.begin(), temp);
    }
}

int count()
{
    int res = 0;
    for (int r = 0; r < ROW; r++)
    {
        for (int c = 0; c < COL; c++)
        {
            if (!yboard[r][c])
                res++;
            if (!rboard[r][c])
                res++;
        }
    }
    return res;
}

int main()
{
    cin >> K;
    while (K-- > 0)
    {
        int t, y, x;
        cin >> t >> y >> x;
        put(t - 1, y, x);
        full();
        overflow();
    }

    cout << score << "\n"
         << count();
    return 0;
}