#include <iostream> 
#include <fstream>
using namespace std;
template <class T> class Pair 
{
    public: 

        T x, y; 
        
        Pair() {}; 

        Pair(T x, T y) 
        {
            this->x = x; 
            this->y = y;
        }

        T getX() const { return this->x; }
        T getY() const { return this->y; }

        Pair<T>& operator= (const Pair<T>& pair) 
        {
            this->x = pair.getX(); 
            this->y = pair.getY(); 
            return *this; 
        }

        bool operator> (const Pair<T>& pair) 
        { 
            return this->x == pair.getX() ? this->y > pair.getY() : this->x > pair.getX(); 
        }

        std::ostream& getCoupleAsStream(std::ostream& out)
        {
            return out << "(" << this->x << ", " << this->y << ")"; 
        }

        template <class C>
        friend std::ostream& operator << (std::ostream& out, const Pair<C>& p); 


}; 

template <class T> std::ostream& operator << (std::ostream& out, const Pair<T>& p) 
{ 
    return out << "(" << p.x << " " << p.y << ")"; 
} 

template <class T> class MaxHeap 
{
    private: 

        int size, fill, hcalls; 
        T* array; 

        int _left(int index)
        {
            return index << 1; 
        }

        int _right(int index)
        {
            return index << 1 | 1; 
        }

        int _parent(int index)
        {
            return index >> 1; 
        }

        void _swapKey(int i, int j)
        {
            T tmp = array[i]; 
            array[i] = array[j]; 
            array[j]  = tmp; 
        }

        void _heapify(int index)
        {
            if (index >= size) return;
            hcalls ++; 

            int max = index; 
            int r = _right(index);
            int l = _left(index); 

            if (array[l] > array[max] && l < size) max = l; 
            if (array[r] > array[max] && r < size) max = r; 

            if (max != index) {
                _swapKey(max, index);
                _heapify(max);  
            }
        }

        void _buildHeap()
        {
            for (int i = (size - 1) / 2; i > 0; i--) 
                _heapify(i);   
        } 


    public: 

        MaxHeap(T* array, int len)
        {
            hcalls = 0; 
            size = len + 1; 
            this->array = new T[size]; 

            for (int i = 1; i < size; i++) {
                this->array[i] = array[i - 1];
            }
                 
            _buildHeap(); 
        }

        T extractMax() 
        {
                T max = array[1]; 
                array[1] = array[size - 1]; 
                size --; 
                if (size > 1) 
                    _heapify(1);
                return max;  
        }

        T* heapsort()
        {
            T *newArray = new T[size - 1]; 
            int tmpSize = size; 
            for (int i = size - 2; i >= 0; --i) 
                newArray[i] = extractMax();   
            return newArray;
        }

        int getHeapifyCalls()
        {
            return this->hcalls; 
        }

        ~MaxHeap() {
            delete array; 
        }

}; 

template <class T> 
void process(std::string type, Pair<T>* array, int len, std::fstream& in, std::fstream& out) 
{
    std::string xunf, yunf; 
    Pair<T>* sorted_array; 
    for (int i = 0; i < len; i++) {
        in >> xunf >> yunf;  
        
        if (type == "int" || type == "bool") {
            array[i].x = atoi(xunf.substr(1).c_str());
            array[i].y = atoi(yunf.substr(0, yunf.length() - 1).c_str());  
        }
        else if (type == "double") {
            array[i].x = atof(xunf.substr(1).c_str());
            array[i].y = atof(yunf.substr(0, yunf.length() - 1).c_str());  
        }
        else {
            array[i].x = xunf.substr(1)[0];
            array[i].y = yunf.substr(0, yunf.length() - 1)[0];  
        }    
    }

    MaxHeap<Pair<T>>* heap = new MaxHeap<Pair<T>>(array, len);
    sorted_array = heap->heapsort(); 

    out << heap->getHeapifyCalls() << " "; 

    for (int i = 0; i < len; ++i)
        out << sorted_array[i] << " ";  
    out << std::endl; 
}


int main()
{
    fstream input("input.txt", ios::in), output("output.txt", ios::out); 
    string type;
    int n_couples; 
    for(int i = 0; i<100; i++){

        input >> type >> n_couples; 
        if (type == "int" || type == "bool") {
            Pair<int>* array = new Pair<int>[n_couples]; 
            process(type, array, n_couples, input, output); 
        }
        if (type == "char") {
            Pair<char>* array = new Pair<char>[n_couples];
            process(type, array, n_couples, input, output); 
        }
        if (type == "double") {
            Pair<double>* array = new Pair<double>[n_couples];
            process(type, array, n_couples, input, output); 
        }        

    }
    return 0; 
}