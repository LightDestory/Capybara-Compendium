#include <iostream>
#include <fstream>
using namespace std;

class Activity
{

public:
    int s, e;

    Activity(int s, int e)
    {
        this->s = s;
        this->e = e;
    }

    friend bool operator<(const Activity &a, const Activity &b);
    friend ostream &operator<<(ostream &os, const Activity &a);
};

bool operator<(const Activity &a, const Activity &b)
{
    return a.e < b.e;
}

ostream &operator<<(ostream &os, const Activity &a)
{
    os << "[" << a.s << ", " << a.e << "]";
    return os;
}

Activity *parse(string str)
{
    str = str.substr(1, str.length() - 2);
    int comma = str.find(' ');

    int s = atoi((str.substr(0, comma)).c_str());
    int e = atoi((str.substr(comma + 1)).c_str());

    return new Activity(s, e);
}

void sort(Activity **a, int len)
{
    for (int i = 0; i < len; i++)
    {
        for (int j = i; j < len; j++)
        {
            if (*a[j] < *a[i])
            {

                Activity *tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }
}

int activities(Activity **S, int n)
{
    int c = 1;
    int e = (S[0])->e;

    for (int i = 1; i < n; i++)
    {
        if ((S[i])->s >= e)
        {
            e = (S[i])->e;
            c++;
        }
    }

    return c;
}

int main()
{
    fstream input("input.txt", ios::in), output("output.txt", ios::out);
    int N;
    for (int i = 0; i < 100; i++)
    {
        int N;
        input >> N;
        Activity **S = new Activity *[N];
        for (int j = 0; j < N; j++)
        {
            string str_1, str_2;
            input >> str_1 >> str_2;
            str_1 += " " + str_2;
            S[j] = parse(str_1);
        }
        sort(S, N);
        output << activities(S, N) << endl;
    }
}