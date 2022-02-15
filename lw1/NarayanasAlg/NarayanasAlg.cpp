// NarayanasAlg.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <boost/timer.hpp>


int main()
{
    std::vector<size_t> v = { 7, 1, 12, 5, 9, 20, 15, 4, 8, 6 };
    boost::timer t;
    t.restart();
    std::sort(v.begin(), v.end());
    do
    {
        //copy(v.begin(), v.end(), std::ostream_iterator<size_t>(std::cout, " "));
        std::cout << std::endl;
    } while (std::next_permutation(v.begin(), v.end()));
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
