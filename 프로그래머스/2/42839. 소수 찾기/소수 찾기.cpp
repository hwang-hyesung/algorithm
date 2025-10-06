#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>

using namespace std;

bool isprime(int n){
    if (n < 2) return false;
    for(int i=2;i<=sqrt(n);i++){
        if(n%i==0) return false;
    }
    return true;
}

int solution(string numbers) {
    int answer = 0;
    set<int> nums;
    
    sort(numbers.begin(), numbers.end());
    
    do {
        for (int i = 1; i <= numbers.size(); ++i)
        {
            string temp = numbers.substr(0, i);
            int num= stoi(temp);      
            if (isprime(num))
            {
                nums.insert(num);
            }
        }
    } while(next_permutation(numbers.begin(), numbers.end()));
    
    return nums.size();
}