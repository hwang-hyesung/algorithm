#include <string>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

int solution(string word) {
    int answer = 0;
    map<char, int> m;
    m['A'] = 1;
    m['E'] = 2;
    m['I'] = 3;
    m['O'] = 4;
    m['U'] = 5;
    
    for (int i = 0; i < word.size(); i++) {
        int n = m[word[i]];
        for (int j = 1; j < n; j++) {
            for (int k = 0; k < 5 - i; k++) {
                answer += pow(5, k);
            }
        }
    }
    answer += word.size();
    
    return answer;
}