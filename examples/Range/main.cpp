#include "../../Range/Range.hpp"
#include "../../IO/IO.hpp"
#include "../../Range/Enumerate.hpp"
#include "../../Range/In.hpp" //Deprecated
#include <iostream>
#include <array>
#include <iterator>
#include <functional>


int main()
{
    {
        /*use Range in range-based for loop*/
        for (auto i : Range(0, 10))
            print(i);

        /*use range to generate 1 random number*/
        Range r(-1, 100000);
        print("Random number in", r, "is", r.rand());

        /*use range to generate several random numbers*/
        auto [num1, num2, num3] = Range(1, 10).rand<3>();


        /*use range to fill a C style array*/
        double arr[10];
        Range(-500.0, 500.0).fillRand(arr);
        print(arr);

        /*use range to fill a STL container*/
        std::array<char, 20> arr2;
        Range('A', 'z').fillRand(arr2);
        print(arr2);

        /*Alternatively .randFast() provides a faster way for generating random number using rand() in C*/
        int arr3[10];
        Range(-200, 300).fillRandFast(arr3);
        print(arr3);
    }

    {
        std::array arr{ "cpp", "sugar", "sweet" };
        for (auto [index, string] : Enumerate(arr))
            print(index, '\t', string);
    }
    {
        print("1D range");
        for (auto i : Range(2.0, 10.0, 3))
            print(i);

        print("2D range");
        for (auto [i, j] : Range(-5, 1) | Range(0, 3))
            print(i, '\t', j);

        std::cin.get();
    }
    {
        std::vector<int> v(20);
        auto process = [](auto&& v) {print(v); };
        parallel(Range(0ull, v.size()), [&](auto range)
            {
                for (auto index : range)
                    process(index);
            }
        );
    }
    {
        /*in<Container> still works*/
        std::array arr{ 1,2,3,4, 5,6 };
        print(in{ arr } == 3);
    }
    {
        /*Range works for lvalue container */
        std::array arr{ 1,2,3,4, 5,6 };
        print(Range{ arr } == 3);
    }
    {
        /*Range works for lvalue container*/
        std::array arr{ 1,2,3,4, 5,6 };
        /*Lame*/
        Range{arr}.map([](auto &element) { return element * 3; });
        /*If macro can do this */
        Range{arr}.map([](auto &element) { => element * 3; });
        /*Epic*/
        Range{arr}.map(element * 3);

        print(3 == Range{arr});
    }
    {
        print(Range{ std::array{ 1,2,3,4, 5,6 } } == 3);
    }
    
}
