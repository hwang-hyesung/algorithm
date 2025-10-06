#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> answers) {
    vector<int> answer;
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {2, 1, 2, 3, 2, 4, 2, 5};
    int arr3[] = {3, 3, 1, 1, 2, 2, 4, 4, 5, 5};
    int score1 = 0;
    int score2 = 0;
    int score3 = 0;
    
    for(int i = 0; i < answers.size();i++){
        if(arr1[i%5]==answers[i]){
            score1++;
        }
        if(arr2[i%8]==answers[i]){
            score2++;
        }
        if(arr3[i%10]==answers[i]){
            score3++;
        }
    }
    
    int max_score = max(score1, score2);
    max_score = max(max_score, score3);
    
    if(max_score==score1){
        answer.push_back(1);
    }
    
    if(max_score==score2){
        answer.push_back(2);
    }
    
    if(max_score==score3){
        answer.push_back(3);
    }
    
    
    return answer;
}