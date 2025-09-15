#include <iostream>
#include <stack>
#include <vector>
using namespace std;
int main(){
    int n = 0;
    cin >> n;
    vector<int>arr(n);
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    vector<int>res(n);
    stack<int> st;
    for(int i = n - 1; i >= 0; i--){
        while(!st.empty() && arr[st.top()] <= arr[i]){
            st.pop();
        }
        if(st.empty()){
            res[i] = 0;
        }else{
            res[i] = st.top() + 1;
        }
        st.push(i);
    }
    for(int i = 0; i < n; i++){
        cout << res[i] << (i == n - 1 ? "" : " ");
    }
    return 0;
}