#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

struct Box
{
    int k, w, h, c, r;
};

int n, m;
vector<vector<int>> truck(50, vector<int>(50, 0));
vector<int> height(50, 0);
map<int, Box> box;

void placeBox(Box &b)
{
    int maxH = 0;
    for (int j = b.c; j < b.c + b.w; j++)
        maxH = max(maxH, height[j]);

    b.r = maxH;
    box[b.k] = b;
    for (int r = b.r; r < b.r + b.h; r++)
    {
        for (int c = b.c; c < b.c + b.w; c++)
        {
            truck[r][c] = b.k;
        }
    }

    for (int j = b.c; j < b.c + b.w; j++)
        height[j] = b.r + b.h;
}

bool canRemove(int bidx, bool side)
{
    Box &b = box[bidx];

    for (int r = b.r; r < b.r + b.h; r++)
    {
        if (side)
        {
            for (int c = b.c - 1; c >= 0; c--)
            {
                if (truck[r][c] != 0)
                    return false; // 옆에 장애물이 있음
            }
        }
        else
        {
            for (int c = b.c + b.w; c < n; c++)
            {
                if (truck[r][c] != 0)
                    return false;
            }
        }
    }

    return true;
}

int checkFall(Box &b)
{
    int cnt = n;
    for (int c = b.c; c < b.c + b.w; c++)
    {
        int r = b.r - 1;
        int fall = 0;
        while (r >= 0 && truck[r][c] == 0)
        {
            fall++;
            r--;
        }
        cnt = min(cnt, fall);
    }
    return cnt;
}

set<int> fall(Box &b, int dist)
{
    set<int> affected;

    if (dist == 0)
        return affected;

    for (int r = b.r; r < b.r + b.h; r++)
        for (int c = b.c; c < b.c + b.w; c++)
            truck[r][c] = 0;

    b.r -= dist;
    box[b.k] = b;

    for (int r = b.r; r < b.r + b.h; r++)
        for (int c = b.c; c < b.c + b.w; c++)
            truck[r][c] = b.k;

    int topRow = b.r + b.h + dist;
    if (topRow < n)
    {
        for (int c = b.c; c < b.c + b.w; c++)
        {
            if (truck[topRow][c] != 0)
                affected.insert(truck[topRow][c]);
        }
    }

    return affected;
}

void removeBox(bool side)
{
    int rbox = -1;
    set<int> next;

    for (int i = n - 1; i >= 0; i--)
    {
        int col = side ? 0 : n - 1;
        while (col >= 0 && col < n)
        {
            if (truck[i][col] != 0)
            {
                if (canRemove(truck[i][col], side) && (rbox == -1 || truck[i][col] < rbox))
                    rbox = truck[i][col];
                break;
            }
            col = side ? col + 1 : col - 1;
        }
    }

    if (rbox == -1)
        return;

    Box &b = box[rbox];

    for (int r = b.r; r < b.r + b.h; r++)
        for (int c = b.c; c < b.c + b.w; c++)
            truck[r][c] = 0;

    cout << rbox << "\n";

    for (int c = b.c; c < b.c + b.w; c++)
    {
        int aboveR = b.r + b.h;
        if (aboveR < n && truck[aboveR][c] != 0)
            next.insert(truck[aboveR][c]);
    }

    while (!next.empty())
    {
        int id = *next.begin();
        next.erase(next.begin());

        Box &nb = box[id];
        int cnt = checkFall(nb);
        set<int> newFallen = fall(nb, cnt);
        next.insert(newFallen.begin(), newFallen.end());
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        Box b;
        cin >> b.k >> b.h >> b.w >> b.c;
        b.c--;
        placeBox(b);
    }

    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //         cout << truck[i][j] << " ";
    //     cout << "\n";
    // }

    for (int i = 0; i < m; i++)
    {
        removeBox(i % 2 == 0);

        // for (int i = 0; i < n; i++)
        // {
        //     for (int j = 0; j < n; j++)
        //         cout << truck[i][j] << " ";
        //     cout << "\n";
        // }
    }
    return 0;
}
