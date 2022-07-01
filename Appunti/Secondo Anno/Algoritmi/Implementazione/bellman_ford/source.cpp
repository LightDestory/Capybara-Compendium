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

    bool bellman_ford(H source, H destination)
    {
        int src = findNode(source);
        int dest = findNode(destination);
        for (int i = 0; i < size; i++)
            d[i] = INF;
        d[src] = 0;
        for (int k = 0; k < size - 1; k++)
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

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (edges_weight[i][j] != INF)
                    relax(i, j);
            }
        }

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (edges_weight[i][j] != INF && d[j] > d[i] + edges_weight[i][j])
                    return false;
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
    if(!g->bellman_ford(src, dest)){
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
    int N, E;
    string type;
    for(int i = 0; i<100; i++){
        input >> N >> E >> type;
        runtime(input, output, N, E, double());
        output << endl;
    }
    return 0;
}