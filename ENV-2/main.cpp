#include <iostream>
#include <vector>
#include "Complex.h"
#include "Sort.h"

int main() 
{
    vector<Complex> complexNumbers = 
    {
        Complex(3, 5),
        Complex(-2, 1),
        Complex(4, -3),
        Complex(0, 2),
        Complex(-1, -4)

    };
    for (auto& num : complexNumbers) 
    {
	    std::cout << num << endl;
    }

    bubbleSort(complexNumbers);
    for (auto& num : complexNumbers) 
    {
	    std::cout << num << endl;
    }

    return 0;
}
