#include <iostream>
using namespace std;

int main()
{
    int arr[28];
    int num[30];
    
    for (int i = 0; i < 30; i++) {
        num[i] = i+1;
    }
    
    for (int i = 0; i < 28; i++) {
        cin >> arr[i];
    }
    
    for (int i = 0; i < 28; i++) {
        if (arr[i] < 31) {
            num[arr[i]-1] = 0;
        }
    }
    
    for (int i = 0; i < 30; i++) {
        if (num[i] != 0) {
            cout << num[i] << " ";
        }
    }

    return 0;
}