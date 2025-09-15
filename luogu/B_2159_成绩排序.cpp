#include <iostream>
using namespace std;
struct student{
    string name;
    int number;
} Student;
int main(){
    int n;
    cin >> n;
    student s[30];
    for(int i = 0; i < n; i++){
        cin >> s[i].name;
        cin >> s[i].number;
    }
    for(int i = 0; i < n ; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(s[j].number < s[j+1].number){
                string temp_s = s[j].name;
                int temp_n = s[j].number;
                s[j].number = s[j+1].number;
                s[j].name = s[j+1].name;
                s[j+1].number = temp_n;
                s[j+1].name = temp_s;
            }else if(s[j].number == s[j+1].number){
                if(s[j].name > s[j+1].name){
                string temp_s = s[j].name;
                int temp_n = s[j].number;
                s[j].number = s[j+1].number;
                s[j].name = s[j+1].name;
                s[j+1].number = temp_n;
                s[j+1].name = temp_s;
                }
            }
        }
    }
    for(int i = 0; i < n; i++){
        cout << s[i].name << " "<< s[i].number << endl;
    }
    return 0;

}
