#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(int distance, vector<int> rocks, int n) {
    rocks.push_back(distance);
    rocks.push_back(0);
    sort(rocks.begin(), rocks.end());
    
    int answer = 0;
    int left = 1;
    int right = distance;
    
    while(left<=right){
        int mid = (left + right) / 2;
        int prev = 0;
        int removed = 0;

        for (int i = 1; i < rocks.size(); i++) {
            if (rocks[i] - prev < mid) {
                removed++;
            } else {
                prev = rocks[i];
            }
        }
        
        if(removed > n){
            right = mid - 1;
        }else{
            answer = mid;
            left = mid + 1;   
        }
    }
    return answer;
}