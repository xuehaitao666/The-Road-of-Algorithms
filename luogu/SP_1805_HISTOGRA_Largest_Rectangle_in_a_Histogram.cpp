#include <iostream>
#include <vector>
#include <stack>
using namespace std;

long long largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    if (n == 0) return 0;
    
    vector<int> left(n, -1);   
    vector<int> right(n, n);   
    stack<int> st;            
    
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && heights[st.top()] >= heights[i]) {
            st.pop();
        }
        if (!st.empty()) {
            left[i] = st.top();
        }
        st.push(i);
    }
    
    while (!st.empty()) {
        st.pop();
    }
    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && heights[st.top()] > heights[i]) {
            st.pop();
        }
        if (!st.empty()) {
            right[i] = st.top();
        }
        st.push(i);
    }
    
    long long max_area = 0;
    for (int i = 0; i < n; ++i) {
        long long area = (long long)heights[i] * (right[i] - left[i] - 1);
        if (area > max_area) {
            max_area = area;
        }
    }
    
    return max_area;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n && n != 0) {
        vector<int> heights(n);
        for (int i = 0; i < n; ++i) {
            cin >> heights[i];
        }
        cout << largestRectangleArea(heights) << '\n';
    }
    
    return 0;
}
