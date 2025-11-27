#include <string>
#include <vector>

using namespace std;

int solution(vector<int> wallet, vector<int> bill) {
    int answer = 0;
    int w = bill[0], h = bill[1], ww=wallet[0], wh = wallet[1];
    
    while(true){
        if((ww>=w && wh>=h)||(ww>=h && wh>=w)) return answer;
        answer++;
        if(h>w) h/=2;
        else w/=2;
    }
    return answer;
}