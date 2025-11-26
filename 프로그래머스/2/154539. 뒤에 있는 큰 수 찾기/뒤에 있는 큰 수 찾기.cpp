#include <string>
#include <vector>
#include <stack>

using namespace std;

vector<int> solution(vector<int> numbers) {
    int n = numbers.size();
    vector<int> answer(n);
    stack<int> st;

    for(int i = n - 1; i >= 0; i--) {
        while(!st.empty() && st.top() <= numbers[i])
            st.pop();

        answer[i] = st.empty() ? -1 : st.top();

        st.push(numbers[i]);
    }

    return answer;
}
