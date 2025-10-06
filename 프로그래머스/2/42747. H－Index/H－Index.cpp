#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(const int& a, const int& b){
    return a>=b;
}

int solution(vector<int> citations) {
    int answer = 0;
    sort(citations.begin(), citations.end(), cmp);
    int h = citations.size();
    while(true){
        if(citations[h-1]>=h) return h;
        else h--;
        
    }
    return answer;
}