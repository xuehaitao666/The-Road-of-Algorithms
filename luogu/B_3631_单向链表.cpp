#include <iostream>
#include <unordered_map>
using namespace std;
int main(){
    unordered_map <int,int> next;
    next[1] = 0;
    int q;
    cin >> q;
    while(q--){
        int op,x,y;
        cin >> op;
        if(op == 1){
            cin >> x >> y;
            int temp = next[x];
            next[x] = y;
            next[y] = temp;
        }else if(op == 2){
            cin >> x;
            cout << next[x] << endl;
        }else if(op == 3){
            cin >> x;
            int del = next[x];
            next[x] = next[del];
            next.erase(del);
        }
    }
    return 0;
    
}