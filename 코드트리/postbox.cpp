#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Box
{
    int id, r, c, h, w;
};

int N, M;
int arr[55][55];
map<int, Box> bmap;

int moveDown(int id)
{
    Box &b = bmap[id];
    int dist = 0;

    while (true)
    {
        int nr = b.r - 1;
        if (nr < 0)
            break;

        bool canGo = true;
        for (int x = b.c; x < b.c + b.w; x++)
        {
            if (arr[nr][x] != 0)
            {
                canGo = false;
                break;
            }
        }
        if (!canGo)
            break;

        for (int x = b.c; x < b.c + b.w; x++)
        {
            arr[b.r + b.h - 1][x] = 0;
            arr[nr][x] = id;
        }
        b.r--;
        dist++;
    }
    return dist;
}

void applyGravity()
{
    while (true)
    {
        bool changed = false;
        vector<Box> sorted;
        for (auto const &[id, b] : bmap)
            sorted.push_back(b);

        sort(sorted.begin(), sorted.end(), [](const Box &a, const Box &b)
             { return a.r < b.r; });

        for (auto &sb : sorted)
        {
            if (moveDown(sb.id) > 0)
                changed = true;
        }
        if (!changed)
            break;
    }
}

bool canUnload(int id, int side)
{
    Box &b = bmap[id];
    for (int y = b.r; y < b.r + b.h; y++)
    {
        if (side == 0)
        {
            for (int x = 0; x < b.c; x++)
                if (arr[y][x] != 0)
                    return false;
        }
        else
        {
            for (int x = b.c + b.w; x < N; x++)
                if (arr[y][x] != 0)
                    return false;
        }
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;

    for (int i = 0; i < M; i++)
    {
        int k, h, w, c;
        cin >> k >> h >> w >> c;
        c--;

        int startR = N - h;
        bmap[k] = {k, startR, c, h, w};
        for (int y = startR; y < startR + h; y++)
        {
            for (int x = c; x < c + w; x++)
                arr[y][x] = k;
        }

        applyGravity();
    }

    for (int i = 0; i < M; i++)
    {
        int side = i % 2;
        int targetId = -1;

        for (auto const &[id, b] : bmap)
        {
            if (canUnload(id, side))
            {
                if (targetId == -1 || id < targetId)
                    targetId = id;
            }
        }

        if (targetId != -1)
        {
            cout << targetId << "\n";

            Box &b = bmap[targetId];
            for (int y = b.r; y < b.r + b.h; y++)
            {
                for (int x = b.c; x < b.c + b.w; x++)
                    arr[y][x] = 0;
            }
            bmap.erase(targetId);

            applyGravity();
        }
    }

    return 0;
}