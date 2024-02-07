#include <iostream>
#define BOOST_TIMER_ENABLE_DEPRECATED
#include <boost/timer.hpp>
#include <vector>

const int N = 3;
const int K = 2;

void NextCombination(std::vector<int>& v)
{
    int i = K - 1;
    while (true)
    {
        int max = N - K + 1 + i;
        if (v[i] < max)
        {
            v[i]++;
            while (i < K - 1)
            {
                i++;
                v[i] = v[i - 1] + 1;
            }
            return;
        }
        i--;
    }
}

int main()
{
    boost::timer t;
    t.restart();

    std::vector<int> v;
    v.resize(K);
    for (int i = 0; i < K; i++)
    {
        v[i] = i + 1;
    };

    while (true)
    {
        for (int i = 0; i < v.size(); i++)
        {
            std::cout << v[i] << " ";
        };
        std::cout << std::endl;
        if (v[0] == N - K + 1)
        {
            break;
        }
        NextCombination(v);
    };

    double duration = t.elapsed();
    std::cout << std::endl << duration << std::endl;



}

/*

Time Test
K = 5

N = 10: 0.005 s
N = 20: 0.271 s
N = 25: 0.913 s
N = 50: 36.4 s
N = 100: 21,5 min

*/