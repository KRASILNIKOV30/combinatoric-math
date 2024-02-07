#include <iostream>
#include <vector>
#include <ctime>

int main()
{
    const int N = 10;
    srand(time(0));
    std::vector<int> v;
    v.resize(N);
    for (int i = 0; i < N; i++)
    {
        v[i] = i + 1;
    };
    int r = 0;
    for (int i = 0; i < N; i++)
    {
        r = rand() % N;
        std::swap(v[i], v[r]);
    }
    for (int i = 0; i < N; i++)
    {
        std::cout << v[i] << " ";
    };
    std::cout << std::endl;
}