#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std; 

int resto(int R, vector<int> M, int N) 
{
    int RI = R + 1; 
    int *mins = new int[RI]; 
    int **S = new int*[RI];
    for(int i = 0; i<RI; i++)
        S[i] = new int[N];

    for (int i = 0; i < RI; i++) mins[i] = 10000; 

    for (int i = 0; i < RI; i++) {
        for (int j = 0; j < N; j++) {

            if (i == M[j]) S[i][j] = 1; 

            else if (i < M[j]) S[i][j] = 10000; 

            else if (i > M[j]) S[i][j] = mins[i - M[j]] + 1;
            
            mins[i] = S[i][j] < mins[i] ? S[i][j] : mins[i];  

        }
    }
    return mins[R]; 
}

int main()
{
    fstream input("input.txt", ios::in), output("output.txt", ios::out); 
    int R, N, coin;
    vector<int> coins;
    for(int i = 0; i<100; i++){
        coins.clear();
        input >> R >> N; 
        for(int j = 0; j<N; j++){
            input >> coin;
            coins.push_back(coin);
        }
        sort(coins.begin(), coins.end());
        output << resto(R, coins, N) << endl; 
    } 
}