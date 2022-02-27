
#include <iostream>
#include <algorithm>
#include <vector>
#include <boost/timer.hpp>
#include "NarayanaAlg.h"


void TimeCount(double duration)
{
    long double d = duration;
    for (int i = 11; i <= 15; i++)
    {
        d *= i;
    }
    d /= 3600;
    std::cout << "N = 15: " << d << " hours" << std::endl;

    for (int i = 16; i <= 20; i++)
    {
        d *= i;
    }
    d /= 24;
    std::cout << "N = 20: " << d << " days" << std::endl;

    for (int i = 21; i <= 50; i++)
    {
        d *= i;
    }
    d /= 365;
    std::cout << "N = 50: " << d << " years" << std::endl;

    for (int i = 51; i <= 100; i++)
    {
        d *= i;
    }
    std::cout << "N = 100: " << d << " years" << std::endl;
}

int main()
{
    std::vector<size_t> v = { 1, 2 , 3, 4, 5, 6, 7, 8, 9, 10 };
    boost::timer t;
    t.restart();
    std::sort(v.begin(), v.end());
    do
    {
        //copy(v.begin(), v.end(), std::ostream_iterator<size_t>(std::cout, " "));
        //std::cout << std::endl;
    } while (std::next_permutation(v.begin(), v.end()));
    double duration = t.elapsed();

    std::cout << std::endl << duration << std::endl << std::endl;
    TimeCount(duration);
}
