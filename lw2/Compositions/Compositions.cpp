#include <iostream>
#include <vector>

const int N;
const int K;

void WriteComposition(std::vector<int> separators)
{
    int sum = N;
    for (auto& el : separators)
    {

    }
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
    }
}

int main()
{
    std::vector<int> separators(K-1);
    for (auto& el : separators)
    {
        el = 0;
    }

    do
    {

    }
}
