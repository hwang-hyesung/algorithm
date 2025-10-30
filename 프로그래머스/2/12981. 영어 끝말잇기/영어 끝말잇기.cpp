#include <string>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

vector<int> solution(int n, vector<string> words) {
    vector<int> answer;
    answer.push_back(0);
    answer.push_back(0);
    int cnt = -1, len = -1;
    char start = '0';
    set<string> s;
    
    for(string word : words) {
        cnt++;
        s.insert(word);
        if(len == s.size() || (start != '0' && word[0] != start)) {
            cout << word << " ";
            answer[0] = (cnt)%n + 1;
            answer[1] = cnt/n + 1;
            return answer;
        }
        len = s.size();
        start = word[word.length()-1];
    }
    
    return answer;
}