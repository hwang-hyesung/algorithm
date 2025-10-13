#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Work {
    int idx;
    int reqtime;
    int taketime;
};

bool cmp(const vector<int>& a, const vector<int>& b){
    if(a[0]==b[0]) {
        if(a[1]==b[1]) return a[2] < b[2];
        return a[1]<b[1];
    }
    return a[0]<b[0];
}

struct comp {
    bool operator()(const Work &a, const Work &b) const {
        if(a.taketime == b.taketime){
            if(a.reqtime == b.reqtime) return a.idx > b.idx; 
            return a.reqtime > b.reqtime;
        }
        return a.taketime > b.taketime;
    }
};


int solution(vector<vector<int>> jobs) {
    int answer = 0;
    int t = 0;
    int totaljobs = jobs.size();
    for(int i=0;i<jobs.size();i++){
        jobs[i].push_back(i);
    }
    
    sort(jobs.begin(), jobs.end(), cmp);
    
    priority_queue<Work, vector<Work>, comp> pq;
    Work w;
    w.idx = jobs[0][2];
    w.reqtime = jobs[0][0];
    w.taketime = jobs[0][1];
    pq.push(w);
    jobs.erase(jobs.begin());
    t = w.reqtime;
    
    while(true){
        
        while(jobs.size() > 0){
            if(jobs[0][0] <= t){
                Work ww;
                ww.idx = jobs[0][2];
                ww.reqtime = jobs[0][0];
                ww.taketime = jobs[0][1];
                pq.push(ww);
                jobs.erase(jobs.begin());
            } else {
                break;
            }
        }
        
        if(pq.empty()){
            if(jobs.empty()){
                break;
            }else {
                t = jobs[0][0];
                continue;
            }
        }
        
        Work work = pq.top();
        pq.pop();
        
        t += work.taketime;
        
        answer += ( t - work.reqtime);
        
        
    }
    answer /= totaljobs;
    
    return answer;
}