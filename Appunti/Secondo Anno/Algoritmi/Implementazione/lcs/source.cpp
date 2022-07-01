#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

int lcs(string s1, string s2){
    int **matrix = new int*[s1.length()+1];
    for(int i = 0; i<=s1.length(); i++)
        matrix[i] = new int[s2.length()+1]  {0};
    for(int i = 1; i<=s1.length(); i++){
        for(int j = 1; j<=s2.length(); j++){
            if(s1[i-1] == s2[j-1]){
                matrix[i][j] = matrix[i-1][j-1]+1;
            }
            else{
                matrix[i][j] = max(matrix[i-1][j], matrix[i][j-1]);
            }
        }
    }
    return matrix[s1.length()][s2.length()];
}

int main(){
    fstream input("input.txt", ios::in), output("output.txt", ios::out);
    int  N;
    string s1, s2;
    for(int i = 0; i<100; i++){
        input >> N >> N >>s1 >> s2;
        output << lcs(s1, s2) << endl;
    }
}