#include <iostream>
using namespace std;
struct student{
    long number;
    double score;
}Student;



int main(){
    int n,k;
    cin >> n >> k;
    student s[102];
    for(int i = 0; i < n; i++){
        cin >> s[i].number;
        cin >> s[i].score;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(s[j].score < s[j+1].score){
                long temp_n = s[j].number;
                double temp_s = s[j].score;
                s[j].number = s[j+1].number;
                s[j].score = s[j+1].score;
                s[j+1].number = temp_n;
                s[j+1].score = temp_s;
            }
        }
    }
    cout << s[k-1].number << " " << s[k-1].score << endl;
    return 0;
}