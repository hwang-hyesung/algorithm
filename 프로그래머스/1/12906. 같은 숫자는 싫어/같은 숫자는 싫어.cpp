#include <vector>
#include <iostream>

using namespace std;

vector<int> solution(vector<int> arr) 
{
    vector<int> answer;

    for(int a : arr){
        if(answer.empty()) answer.push_back(a);
        else{
            if(a==answer.back()) continue;
            else answer.push_back(a);
        }
    }

    return answer;
}