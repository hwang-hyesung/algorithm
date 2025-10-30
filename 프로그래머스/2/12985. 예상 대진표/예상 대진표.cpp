#include <iostream>

using namespace std;

int solution(int n, int a, int b)
{
    int answer = 0;
    
    int s = a, e = b, cnt = 0;
    while(true){
        cnt++;
        
        s = (s+s%2)/2;
        e = (e+e%2)/2;
        
        if(s==e) break;
    }
    
    return cnt;
}