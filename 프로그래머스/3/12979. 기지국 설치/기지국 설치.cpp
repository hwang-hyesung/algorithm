#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int solution(int n, vector<int> stations, int w)
{
    int answer = 0;
    
    int width = w * 2 + 1;
    int left = 1;

    for(int s : stations){
        int start = s - w;
        int end = s + w;

        if(left < start){
            answer += ((start - left) + width - 1) / width; 
        }

        left = end + 1; 
    }

    if(left <= n){
        answer += ((n - left + 1) + width - 1) / width;
    }

    return answer;
}