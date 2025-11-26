#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <sstream>

using namespace std;

int calFee(vector<int> fees, int time){
    int f = fees[1];
    if(time <= fees[0]) {
        return f;
    }
    int left = time - fees[0];
    f += ((left)/fees[2])*fees[3] + (left%fees[2]==0? 0 : fees[3]);
    return f;
}

int calTime(vector<string> time){
    string start = time[0];
    string end = time[1];
    
    int sh = stoi(start.substr(0,2));
    int sm = stoi(start.substr(3,2));
    int eh = stoi(end.substr(0,2));
    int em = stoi(end.substr(3,2));

    int m = em - sm;
    int h = eh - sh;
    if(m>60){
        h += m/60;
        m %= 60;
    }else if(m<0){
        h -= 1;
        m += 60;
    }

    return h*60 + m;
}

vector<int> solution(vector<int> fees, vector<string> records) {
    vector<int> answer;
    map<string, vector<string>> time;
    map<string, int> totaltime;
    
    for(string record : records){
        stringstream ss(record);
        string s;
        vector<string> rec;
        while(ss >> s){
            rec.push_back(s);
        }
        
        if(rec[2]=="IN"){
            time[rec[1]].clear();
            time[rec[1]].push_back(rec[0]);
        }else {
            
            time[rec[1]].push_back(rec[0]);
            totaltime[rec[1]] += calTime(time[rec[1]]);
        }
    }
    
    for(pair<string, vector<string>> t : time){
        if(t.second.size()%2!=0){
            t.second.push_back("23:59");
            totaltime[t.first] += calTime(t.second);
        }
    }
    
    for(pair<string, int> t : totaltime){
        answer.push_back(calFee(fees,t.second));
    }
    return answer;
}