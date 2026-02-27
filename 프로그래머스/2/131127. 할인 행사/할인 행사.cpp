#include <string>
#include <vector>
#include <map>

using namespace std;

int solution(vector<string> want, vector<int> number, vector<string> discount) {
    int answer = 0;
    map<string, int> m;
    
    for(int i=0;i<10;i++){
        m[discount[i]]++;
    }
    
    for(int i=0;i<=discount.size()-10;i++){
        
        bool flag = true;
        for(int j=0;j<want.size();j++){
            if(m[want[j]] != number[j]){
                flag = false;
                break;
            }
        }
        
        if(flag) answer++;
        
        if(i+10 < discount.size()){
            m[discount[i]]--;
            m[discount[i+10]]++;
        }
    }
    
    return answer;
}