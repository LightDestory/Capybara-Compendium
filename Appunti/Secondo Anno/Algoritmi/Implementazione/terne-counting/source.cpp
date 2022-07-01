#include <iostream>
#include <fstream>

using namespace std;

class NPair{
    private:
    int x,y,z;
    public:
    NPair(int x, int y, int z){
        this->x = x;
        this->y = y;
        this->z = z;
    }
    int getX(){ return x; }
    int getY(){ return y; }
    int getZ(){ return z; }
};
bool operator<(NPair& a, NPair& b){
    return a.getX()<b.getX();
}

void terne_counting_sort(fstream& input, fstream& output, int N){
    NPair** unsorted = new NPair*[N];
    NPair** sorted = new NPair*[N];
    char c;
    double x,y,z;
    for(int i = 0; i<N; i++){
        input >> c >> x >> y >> z >> c;
        unsorted[i] = new NPair(x*10, y*10, z*10);
    }
    NPair* max = unsorted[0];
    NPair* min = unsorted[0];
    for(int i = 1; i<N; i++){
        if(*max<*(unsorted[i])) max = unsorted[i];
        if(*(unsorted[i])<*min) min = unsorted[i];
    }
    int range = max->getX()-min->getX()+1;
    int* C = new int[range];
    for(int i = 0; i<range; i++) C[i] = 0;
    for(int i = 0; i<N; i++){
        C[unsorted[i]->getX()-min->getX()]++;
    }
    for(int i = 1; i<range; i++){
        C[i] = C[i] + C[i-1];
    }
    for(int i = N-1; i>=0; i--){
        int tmp_pos = unsorted[i]->getX()-min->getX();
        int out_pos = C[tmp_pos]-1;
        sorted[out_pos] = unsorted[i];
        C[tmp_pos]--;
    }
    for(int i = 0; i<range; i++){
        output << C[i] << " ";
    }
    for(int i = 0; i<N; i++){
        output << "(" << sorted[i]->getX()/10.0 << " " << sorted[i]->getY()/10.0 << " " << sorted[i]->getZ()/10.0 << ") ";
    }
}

int main(){
    fstream input("input.txt", ios::in), output("output.txt", ios::out);
    int N;
    for(int i = 0; i<100; i++){
        input >> N;
        terne_counting_sort(input, output, N);
        output << endl;
    }
}