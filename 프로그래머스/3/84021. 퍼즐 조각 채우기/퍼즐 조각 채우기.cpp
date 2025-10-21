#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int dy[] = {-1, 0, 1, 0}, dx[] = {0, -1, 0, 1};

vector<pair<int, int>> dfs(int y, int x, vector<vector<int>>& board,
                           vector<vector<bool>>& visited, int size, int oy, int ox, int target) {
    vector<pair<int, int>> v1, v2;
    v1.push_back({y - oy, x - ox});
    visited[y][x] = true;
    
    for (int i = 0; i < 4; i++) {
        int ny = y + dy[i], nx = x + dx[i];
        if (ny < 0 || ny >= size || nx < 0 || nx >= size) continue;
        if (visited[ny][nx] || board[ny][nx] != target) continue;
        v2 = dfs(ny, nx, board, visited, size, oy, ox, target);
        v1.insert(v1.end(), v2.begin(), v2.end());
    }
    return v1;
}

vector<pair<int, int>> normalize(vector<pair<int, int>> v) {
    int minY = 1e9, minX = 1e9;
    for (auto &p : v) {
        minY = min(minY, p.first);
        minX = min(minX, p.second);
    }
    for (auto &p : v) {
        p.first -= minY;
        p.second -= minX;
    }
    sort(v.begin(), v.end());
    return v;
}

vector<pair<int, int>> rotate(vector<pair<int, int>> &puzzle) {
    vector<pair<int, int>> rot;
    int maxY = 0;
    for (auto [y, x] : puzzle)
        maxY = max(maxY, y);
    for (auto [y, x] : puzzle)
        rot.push_back({x, maxY - y});
    return normalize(rot);
}

bool isfit(vector<pair<int, int>> a, vector<pair<int, int>> b) {
    a = normalize(a);
    b = normalize(b);
    return a == b;
}

int solution(vector<vector<int>> game_board, vector<vector<int>> table) {
    int answer = 0, size = table.size();

    vector<pair<int, vector<pair<int, int>>>> puzzle;
    vector<pair<int, vector<pair<int, int>>>> hole;
    vector<vector<bool>> tvisited(size, vector<bool>(size, false));
    vector<vector<bool>> gvisited(size, vector<bool>(size, false));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (table[i][j] == 1 && !tvisited[i][j]) {
                vector<pair<int, int>> p = dfs(i, j, table, tvisited, size, i, j, 1);
                puzzle.push_back({p.size(), p});
            }
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (game_board[i][j] == 0 && !gvisited[i][j]) {
                vector<pair<int, int>> p = dfs(i, j, game_board, gvisited, size, i, j, 0);
                hole.push_back({p.size(), p});
            }
        }
    }

    sort(puzzle.begin(), puzzle.end());
    sort(hole.begin(), hole.end());
    vector<bool> used(puzzle.size(), false);
    vector<bool> filled(hole.size(), false);

    for (int i = 0; i < hole.size(); i++) {
        int hs = hole[i].first;
        for (int j = 0; j < puzzle.size(); j++) {
            if (used[j] || filled[i]) continue;
            if (hs != puzzle[j].first) continue;

            vector<pair<int, int>> p = puzzle[j].second;
            for (int k = 0; k < 4; k++) {
                if (isfit(p, hole[i].second)) {
                    answer += hs;
                    used[j] = true;
                    filled[i] = true;
                    break;
                }
                p = rotate(p);
            }
        }
    }

    return answer;
}
