// Johnson-TrottersAlg.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <boost/timer.hpp>

int main()
{
    boost::timer t;
    t.restart();

    const int N = 15;

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
    int n = 0;
    while (m != 1)
    {
        //for (int i = 1; i <= N; i++)
            //std::cout << cur[i] << " ";
        //std::cout << std::endl;
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
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
