/*
*   max-z00
*
*   C++
*
*   Programming Assignment - Arrays, Find the most occurring number in the set.
*/
#include <iostream>

using namespace std;

int main()
{
    int numbers[10] = {4,5,9,12,9,22,45,7}; // we could also ask for a user input for the array using a simple for loop.
    int countNumber = 0, most = 0;
    int len = *(&numbers + 1) - numbers;
    cout << "original array is: ";
    for(auto counter : numbers)  // Have no idea what auto does ohh well found it on stack-overflow. just prints out the original array.
    {                            //-original output was: original array is: numbers[0], original array is: numbers[1], ect...
         cout << counter << " ";
    }

    //The next loop grabs the most repeated number in the array.
    for(int var_one = 0; var_one < len; var_one++)
    {
        int tempMost = numbers[var_one];
        int tempCount = 0;
        for (int var_two = 0; var_two < len; var_two++)
        {
            if (numbers[var_two] == tempMost) tempCount++;
            if (tempCount > countNumber)
            {
                most = tempMost;
                countNumber = tempCount;
            }
        }
    }
    cout << "\nThe most repeated number in this Array is: "<< most;



    return 0;
}
