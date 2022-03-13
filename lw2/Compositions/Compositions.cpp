#include <iostream>
#include <vector>
#include <algorithm>

const int N = 3;
const int K = 4;

void WriteComposition(std::vector<int> separators)
{
    int sum = N;
    std::ranges::sort(separators, std::greater<int>());
    for (auto el : separators)
    {
        std::cout << sum - el << " ";
        sum = el;
    }
    std::cout << sum;
}

bool NextSeparators(std::vector<int> & separators)
{
    int i = K - 2;
    while (true)
    {
        if (separators[i] != N)
        {
            separators[i]++;
            i++;
            for (i; i <= K - 2; i++)
            {
                separators[i] = 0;
            }
            return true;
        }
        else if (i != 0)
        {
            i--;
        }
        else
        {
            return false;
        }
    };
}

int main()
{
    std::vector<int> separators(K-1);
    for (auto el : separators)
    {
        el = 0;
    }

    do
    {
        std::ranges::copy(separators, std::ostream_iterator<int>(std::cout, " "));
        std::cout << ": ";
        WriteComposition(separators);
        std::cout << std::endl;
    } while (NextSeparators(separators));
}
