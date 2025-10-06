#include <string>
#include <vector>
#include <map>

using namespace std;

int solution(vector<vector<string>> clothes) {
    int answer = 1;
    map<string, int> closet;
    
    for (int i = 0; i < clothes.size(); i++) {
        closet[clothes[i][1]]++;
    }
    
    for (auto &c : closet) {
        answer *= (c.second + 1);
    }
    
    return answer - 1;
}
