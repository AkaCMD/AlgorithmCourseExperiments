#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

#ifndef _THREEWAY_QUICK_SORT_H_
#define _THREEWAY_QUICK_SORT_H_

class ThreeWayQuickSort
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
    static void sort(std::vector<int> &a, int lo, int hi)
    {
        if(hi <= lo)    return;
        int lt = lo, i = lo + 1, gt = hi;
        int flag = a[lo];
        while(i <= gt)
        {
            if     (less(a[i], flag))   exch(a, lt++, i++);
            else if(less(flag, a[i]))   exch(a, i, gt--);
            else                        i++;
        }
        sort(a, lo, lt - 1);
        sort(a, gt + 1, hi);
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