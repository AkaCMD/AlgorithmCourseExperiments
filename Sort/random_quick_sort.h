#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

#ifndef _RANDOM_QUICK_SORT_H_
#define _RANDOM_QUICK_SORT_H_

class RandomQuickSort
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
    static int partition(std::vector<int> &a, int lo, int hi)
    {
        int flag = a[lo];
        int i = lo, j = hi + 1;
        while (true)
        {
            while(less(a[++i], flag))
            {
                if(i==hi)   break;
            }
            while(less(flag, a[--j]))
            {
                if(j==lo)   break;
            }
            if(i >= j)   break;
            exch(a, i, j);
        }
        exch(a, lo, j);
        return j;        
    }
    static void sort(std::vector<int> &a, int lo, int hi)
    {
        if(hi <= lo)    return; // recursion return
        int j = partition(a, lo, hi);
        sort(a, lo, j-1);
        sort(a, j+1, hi);
    }
    static void shuffle(std::vector<int> &a) // shuffle the array
    {
        auto rng = std::default_random_engine {};
        std::shuffle(std::begin(a), std::end(a), rng);
    }
public:
    static void sort(std::vector<int> &a)
    {
        shuffle(a);
        sort(a, 0, a.size()-1);
    }
};

#endif