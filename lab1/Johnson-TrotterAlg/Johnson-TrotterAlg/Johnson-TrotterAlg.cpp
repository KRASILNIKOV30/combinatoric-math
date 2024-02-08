#include <iostream>
#include <vector>
#define BOOST_TIMER_ENABLE_DEPRECATED
#include <boost/timer.hpp>

constexpr bool IS_OUTPUT_ENABLED = true;

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
    boost::timer t;
    t.restart();

    const int N = 5;

    std::vector<int> cur;
    std::vector<int> rev;
    std::vector<int> dir;
    cur.resize(N + 2);
    rev.resize(N + 2);
    dir.resize(N + 2);
    for (int i = 1; i <= N; i++)
    {
        cur[i] = i;
        rev[i] = i;
        dir[i] = -1;
    }
    cur[0] = N + 1;
    cur[N + 1] = N + 1;
    dir[0] = 0;

    int m = 0;

    while (m != 1)
    {
        if (IS_OUTPUT_ENABLED)
        {
            for (int i = 1; i <= N; i++)
            {
                std::cout << cur[i] << " ";
            }
            std::cout << std::endl;
        }
            
        m = N;

        while ((cur[rev[m] + dir[m]] > m) && (m > 1))
        {
            dir[m] = -dir[m];
            m = m - 1;
        }
        std::swap(cur[rev[m]], cur[rev[m] + dir[m]]);
        std::swap(rev[cur[rev[m]]], rev[cur[rev[m] + dir[m]]]);
    }
    double duration = t.elapsed();

    std::cout << std::endl << duration << std::endl;
    TimeCount(duration);
}