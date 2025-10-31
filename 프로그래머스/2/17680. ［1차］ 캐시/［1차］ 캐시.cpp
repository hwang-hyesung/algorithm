#include <string>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

int solution(int cacheSize, vector<string> cities) {
    if (cacheSize == 0) return cities.size() * 5;
    int answer = 0;
    list<string> cache;
    
    for(string c : cities){
        transform(c.begin(), c.end(), c.begin(), ::tolower);
        
        auto it = find(cache.begin(), cache.end(), c);
        if (it == cache.end()) { 
            answer += 5;
            if (!cache.empty() && cache.size() >= cacheSize)
                cache.pop_back(); 
        } else { 
            answer += 1;
            cache.erase(it); 
        }
        cache.push_front(c);
    }
    
    return answer;
}