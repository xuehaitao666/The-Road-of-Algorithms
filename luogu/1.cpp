#include <iostream>
#include <queue>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    queue<string> plane;
    
    while (n--) {
        int op;
        cin >> op;
        
        if (op == 1) {
            if (plane.size() == m) {
                printf("full\n");
            } else {
                string s;
                cin >> s;
                plane.push(s);
            }
        } else if (op == 2) {
            if (!plane.empty()) {
                string s = plane.front();
                plane.pop();
                printf("%s\n", s.c_str());  // Use c_str() for printf with %s
            } else {
                printf("empty\n");
            }
        } else if (op == 3) {
            int number = plane.size();
            printf("%d\n", number);  // Print the value, not the address
        }
    }
    
    return 0;
}