#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> people, int limit) {
    int answer = 0;
    
    sort(people.begin(), people.end());
    int left = 0, right = people.size()-1;
    int boat = 0;
    
    while(left<=right){
        if(people[left]+people[right]<=limit) left += 1;
        right -= 1;
        boat++;
    }
    return boat;
}