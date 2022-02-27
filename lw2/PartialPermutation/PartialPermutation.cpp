#include <iostream>
#include <boost/timer.hpp>
#include <vector>
#include <algorithm>

const int N = 20;
const int K = 5;

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
        do
        {
            for (int i = 0; i < v.size(); i++)
            {
                std::cout << v[i] << " ";
            };
            std::cout << std::endl;
        } while (std::next_permutation(v.begin(), v.end()));
        if (v[0] == N - K + 1)
        {
            break;
        };
        NextCombination(v);
    };

    double duration = t.elapsed();
    std::cout << std::endl << duration << std::endl;
}

/*

Time Test
K = 5

N = 10: 0.147 s
N = 20: 9.197 s
N = 50: 21 min
N = 100: 12.4 h

*/