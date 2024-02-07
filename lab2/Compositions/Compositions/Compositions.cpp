#include <iostream>
#include <vector>
#include <algorithm>

const int N = 10;
const int K = 3;

void WriteComposition(std::vector<int> separators)
{
    std::ranges::sort(separators);
    std::cout << separators[0] << " ";
    for (int i = 1; i < separators.size(); i++)
    {
        std::cout << separators[i] - separators[i - 1] - 1 << " ";
    }
    std::cout << N + K - 2 - separators[separators.size() - 1];
}

bool NextSeparators(std::vector<int>& v, const int n, const int k)
{
    if (v[0] == n - k + 1)
    {
        return false;
    }
    int i = k - 1;
    while (true)
    {
        int max = n - k + 1 + i;
        if (v[i] < max)
        {
            v[i]++;
            while (i < k - 1)
            {
                i++;
                v[i] = v[i - 1] + 1;
            }
            return true;
        }
        i--;
    }

}

int main()
{
    std::vector<int> separators(K - 1);
    for (int i = 0; i < K - 1; i++)
    {
        separators[i] = i;
    }

    do
    {
        WriteComposition(separators);
        std::cout << std::endl;
    } while (NextSeparators(separators, N + K - 2, K - 1));
}