#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    int answer = 0;
    
    if(n == 1)
        return 1;
    if(n == 2)
        return 2;
    
    int prev = 1;
    int temp = 2;
    
    for(int i = 3; i <= n; i++)
    {
        answer = (prev + temp) % 1000000007;
        prev = temp;
        temp = answer;
    }
    
    return answer;
}