#include <string>
#include <vector>

using namespace std;

string solution(string a, string b) {
    string answer = "";
    int olim = 0;
    int alen = a.length(), blen= b.length();
    int len = alen>blen?alen:blen;
    
    for(int i=1;i<=len;i++){
        int an=0, bn=0;
        if(blen-i>=0){
            bn = b[blen-i] - '0';
        }
        if(alen-i>=0){
            an = a[alen-i] - '0';
        }
        answer.insert(0, to_string((an+bn+olim)%10));
        olim = (an+bn+olim)/10;

    }
    if(olim!=0){
        answer.insert(0, to_string(olim));
    }
    return answer;
}