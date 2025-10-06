#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;
    for(vector<int> c : commands){
        int from = c[0];
        int to = c[1];
        int th = c[2];
        if(from==to) {
            answer.push_back(array[from-1]);
            continue;
        }
        vector<int> nv(array.begin()+from-1, array.begin()+to);
        sort(nv.begin(), nv.end());
        answer.push_back(nv[th-1]);
    }
    return answer;
}