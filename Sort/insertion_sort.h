#include <iostream>
#include <vector>

#ifndef _INSTERION_SORT_H_
#define _INSTERION_SORT_H_

class InsertionSort
{
private:
    static bool less(int v, int w)
    {
        return v < w;
    }
    static void exch(std::vector<int> &a, int i, int j)
    {
        int temp;
        temp = a[i];    a[i] = a[j];    a[j] = temp;
    }

public:
    static void sort(std::vector<int> &a)
    {// ascending order
        int N = a.size();
        for(int i = 1; i < N; i++)
        {
            for(int j = i; j > 0 && less(a[j], a[j-1]); j--)
            {
                exch(a, j, j-1);
            }
        }
    }
};

#endif