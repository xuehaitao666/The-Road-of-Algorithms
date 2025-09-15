#include <iostream>
#include <stack>
#include <vector>
using namespace std;
int main(){
    int T = 0;
    cin >> T;
    while(T--){
        int n = 0;
        cin >> n;
        vector<int> arr(n);
        for(int i = 0; i < n; i++){
            cin >> arr[i];
        }
        vector<int>res;
        stack<pair<int,int>>st;
        long long sum = 0;
        st.push({arr[0],1});
        sum += 1;
        for(int i = 1; i < n; i++){
            while(!st.empty() && st.top().first < arr[i]){
                sum += st.top().second;
                st.pop();
            }
            if(!st.empty() && st.top().first == arr[i]){
                int c = st.top().second;
                st.pop();
                sum += (c);
                st.push({arr[i],c+1});
            }else if(st.empty()){
                st.push({arr[i],1});
            }else{
                sum += 1;
                st.push({arr[i],1});
            }

        }
        cout << sum << "\n";
    }
    return 0;
}