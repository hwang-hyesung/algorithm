#include <string>
#include <vector>
#include <map>

using namespace std;

string solution(string letter) {
    map<string, char> morse = {
        {".-", 'a'}, {"-...", 'b'}, {"-.-.", 'c'}, {"-..", 'd'}, {".", 'e'},
        {"..-.", 'f'}, {"--.", 'g'}, {"....", 'h'}, {"..", 'i'}, {".---", 'j'},
        {"-.-", 'k'}, {".-..", 'l'}, {"--", 'm'}, {"-.", 'n'}, {"---", 'o'},
        {".--.", 'p'}, {"--.-", 'q'}, {".-.", 'r'}, {"...", 's'}, {"-", 't'},
        {"..-", 'u'}, {"...-", 'v'}, {".--", 'w'}, {"-..-", 'x'}, {"-.--", 'y'},
        {"--..", 'z'}
    };
    
    string answer = "", ch = "";
    vector<string> words;
    for(int i=0;i<letter.length();i++){
        if(letter[i]==' '){
            words.push_back(ch);
            ch = "";
        }else{
            ch+=letter[i];
        }
    }
    words.push_back(ch);
    
    for(string s : words){
        answer += morse[s];
    }
    return answer;
}