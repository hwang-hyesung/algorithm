#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer, days;
    for(int i=0;i<progresses.size();i++){
        int taketime = ((100-progresses[i])%speeds[i]==0)?
                       ((100-progresses[i])/speeds[i]):((100-progresses[i])/speeds[i]+1);
        days.push_back(taketime);
    }
    
    int release = days[0];
    int job = 1;
    for(int i=1;i<progresses.size();i++){
        if(release>=days[i]){
            job++;
        }else{
            answer.push_back(job);
            job=1;
            release = days[i];
        }
    }
    
    answer.push_back(job);
    return answer;
}