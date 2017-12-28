#include <iostream>
#define MAX(a,b) (((a)>(b))?(a):(b))
using namespace std;

int main()
{
    int number;
    cin >> number;
    int* ary = new int[number];
    for (int i = number - 1; i >= 0; --i)
    {
        int temp;
        cin >> temp;
        ary[i] = temp;
    }

    int* count = new int[number];
    for (int i = 0 ; i < number; ++i)
    {
        count[i] = 1;
    }
    for (int i = 0; i < number; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (ary[j] < ary[i])
            {
                count[i] = MAX(count[i], count[j] + 1);
            }
        }
    }
    int result = count[0];
    for (int i = 1; i < number; ++i)
    {
        if (result <= count[i])
            result = count[i];
    }
    delete[] ary;
    delete[] count;
    cout << result;
    return 0;
}

