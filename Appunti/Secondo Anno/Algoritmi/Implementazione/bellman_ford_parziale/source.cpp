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
    Graph(int size)
    {
        this->size = size;
        nodes = new H[size];
        for(int i = 0; i<size; i++)
            nodes[i] = i;
        d = new int[size];
        edges_weight = new int*[size];
        for (int i = 0; i < size; i++)
        {
            edges_weight[i] = new int[size];
            for (int j = 0; j < size; j++)
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

    bool bellman_ford(H source, H destination, int K)
    {
        int src = findNode(source);
        int dest = findNode(destination);
        for (int i = 0; i < size; i++)
            d[i] = INF;
        d[src] = 0;
        for (int k = 0; k < K; k++)
        {
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    if (edges_weight[i][j] != INF)
                        relax(i, j);
                }
            }
        }
        return true;
    }

    int getShortPAth(H dest)
    {
        return d[findNode(dest)];
    }
};

template <class H>
void runtime(fstream& input, fstream& output, int N, int E, int K, H proto){
    Graph<H>* g = new Graph<H>(N);
    char c;
    H a, b;
    int w;
    for(int i = 0; i<E; i++){
        input >> c >> a >> b >> w >> c;
        g->addEdge(a,b,w);
    }
    H src, dest;
    input >> src >> dest;
    if(!g->bellman_ford(src, dest, K)){
        output << "undef.";
    }
    else{
        int path = g->getShortPAth(dest);
        if(path==INF){
            output << "inf.";
        }
        else
        {
            output << path;
        }
        
    }
}

int main(){
    fstream input("input.txt", ios::in), output("output.txt", ios::out);
    int N, E, K;
    for(int i = 0; i<100; i++){
        input >> N >> E >> K;
        runtime(input, output, N, E, K, double());
        output << endl;
    }
    return 0;
}