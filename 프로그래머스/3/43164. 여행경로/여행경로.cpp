#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

map<string, vector<pair<string, bool>>> m;
vector<string> answer;
int totalTickets;
bool finished = false;

void dfs(string city, vector<string>& path, int used) {
    if (finished) return;
    if (used == totalTickets) {
        answer = path;
        finished = true;
        return;
    }

    for (auto& [next, usedFlag] : m[city]) {
        if (!usedFlag) {
            usedFlag = true;
            path.push_back(next);
            dfs(next, path, used + 1);
            path.pop_back();
            usedFlag = false;
        }
    }
}

vector<string> solution(vector<vector<string>> tickets) {
    for (auto& t : tickets) {
        m[t[0]].push_back({t[1], false});
    }

    for (auto& [_, v] : m)
        sort(v.begin(), v.end());

    totalTickets = tickets.size();
    vector<string> path = {"ICN"};
    dfs("ICN", path, 0);
    return answer;
}
