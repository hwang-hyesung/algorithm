#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

unordered_map<long long, long long> parent;

long long find(long long x) {
    if (parent.find(x) == parent.end()) return x;
    return parent[x] = find(parent[x]);
}

vector<long long> solution(long long k, vector<long long> room_number) {
    vector<long long> answer;
    for (auto rn : room_number) {
        long long empty_room = find(rn);
        answer.push_back(empty_room);
        parent[empty_room] = find(empty_room + 1);
    }
    return answer;
}
