#include <iostream>
#include <fstream>
#define INF 100000
using namespace std;

template <class H>
class Graph
{
private:
    H *nodes;
    int **edges_weight;
    int *d;
    int size;
    int findNode(H a)
    {
        for (int i = 0; i < size; i++)
        {
            if (nodes[i] == a)
                return i;
        }
        return -1;
    }
    void relax(int i, int j)
    {
        if (d[j] > d[i] + edges_weight[i][j])
        {
            d[j] = d[i] + edges_weight[i][j];
        }
    }

public:
    Graph(int arraySize)
    {
        this->size = 0;
        nodes = new H[arraySize];
        d = new int[arraySize];
        edges_weight = new int*[arraySize];
        for (int i = 0; i < arraySize; i++)
        {
            edges_weight[i] = new int[arraySize];
            for (int j = 0; j < arraySize; j++)
            {
                edges_weight[i][j] = INF;
            }
        }
    }

    void addNode(H item)
    {
        nodes[size++] = item;
    }

    void addEdge(H a, H b, int w)
    {
        int i = findNode(a);
        int j = findNode(b);
        edges_weight[i][j] = w;
    }
    int dijkstra(H source, H destination)
        {
            int src = findNode(source);
            int dest = findNode(destination);

            if (src == -1 || dest == -1)
                return -1; 

            bool locks[size]; 
            int  extracted;    

            for (int i = 0; i < size; i++) {
                locks[i] = false; 
                d[i] = INF; 
            }

            extracted = src; 
            d[extracted] = 0; 
            for (int i = 0; i < size; ++i) {
                locks[extracted] = true; 
                for (int j = 0; j < size; ++j) {
                    int weight = d[extracted] + edges_weight[extracted][j]; 
                    if (d[j] > weight && !locks[j]) {
                        d[j] = weight; 
                    }
                }
                int min = INF; 
                for (int j = 0; j < size; ++j) {
                    if (d[j] < min && !locks[j]) {
                        extracted = j; 
                        min = d[j]; 
                    }
                }
            }

            return d[dest]; 
        }
};

template <class H>
void runtime(fstream& input, fstream& output, int N, int E, H proto){
    Graph<H>* g = new Graph<H>(N);
    for(int i = 0; i<N; i++){
        input >> proto;
        g->addNode(proto);
    }
    char c;
    H a, b;
    int w;
    for(int i = 0; i<E; i++){
        input >> c >> a >> b >> w >> c;
        g->addEdge(a,b,w);
    }
    H src, dest;
    input >> src >> dest;
    int pathw = g->dijkstra(src, dest); 
    if (pathw < INF)
        output << pathw;
    else 
        output << "inf.";
}

int main(){
    fstream input("input.txt", ios::in), output("output.txt", ios::out);
    int N, E;
    string type;
    for(int i = 0; i<100; i++){
        input >> N >> E >> type;
        runtime(input, output, N, E, double());
        output << endl;
    }
    return 0;
}