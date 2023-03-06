#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int edit_distance(string s1, string s2, int s1_len, int s2_len){
    int **matrix = new int*[s1_len+1];
    for(int i = 0; i<=s1_len;i++){
        matrix[i] = new int[s2_len+1];
    }
    for(int i = 0; i<=s1_len; i++)
        matrix[i][0] = i;
    for(int j = 0; j<=s2_len; j++)
        matrix[0][j] = j;
    for(int i = 1; i<=s1_len; i++){
        for(int j = 1; j<=s2_len; j++){
            if(s1[i-1]==s2[j-1])
                matrix[i][j] = matrix[i-1][j-1];
            else{
                matrix[i][j] = min(min(matrix[i-1][j], matrix[i-1][j-1]), matrix[i][j-1])+1;
            }
        }
    }
    return matrix[s1_len][s2_len];
}

int main(){
    fstream input("input.txt", ios::in), output("output.txt", ios::out);
    int s1_len, s2_len;
    string s1, s2;
    for(int i = 0; i<100; i++){
        input >> s1_len >> s2_len >> s1 >> s2;
        output << edit_distance(s1, s2, s1_len, s2_len) << endl;
    }
    return 0;
}