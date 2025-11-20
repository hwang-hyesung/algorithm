#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

vector<int> solution(string s) {
    vector<vector<int>> arr;
    vector<int> answer;

    s = s.substr(1, s.size() - 2);

    vector<string> groups;
    string temp = "";
    for (char c : s) {
        if (c == '{') {
            temp.clear();
        } else if (c == '}') {
            groups.push_back(temp);
        } else {
            temp += c;
        }
    }

    for (string &g : groups) {
        vector<int> nums;
        stringstream ss(g);
        string x;
        while (getline(ss, x, ',')) {
            nums.push_back(stoi(x));
        }
        arr.push_back(nums);
    }

    sort(arr.begin(), arr.end(),
         [](auto &a, auto &b) { return a.size() < b.size(); });

    vector<bool> visited(100001, false);

    for (auto &v : arr) {
        for (int n : v) {
            if (!visited[n]) {
                visited[n] = true;
                answer.push_back(n);
            }
        }
    }

    return answer;
}
