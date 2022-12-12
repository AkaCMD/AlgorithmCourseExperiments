#include <iostream>
#include <vector>

#ifndef _BU_MERGE_SORT_H_
#define _BU_MERGE_SORT_H_

class ButtomUpMergeSort
{
private:
    std::vector<int> aux;    // auxiliary array
    static bool less(int v, int w)
    {
        return v < w;
    }
    static int min(int v, int w)
    {
        if(v < w)   return v;
        else        return w;
    }
    void merge(std::vector<int> &a, int lo, int mid, int hi)
    {
        int i = lo, j = mid+1;
        for(int k = lo; k <= hi; k++)
            aux[k] = a[k];
        for(int k = lo; k <= hi; k++)
        {
            if     (i > mid)                a[k] = aux[j++];
            else if(j > hi)                 a[k] = aux[i++];
            else if(less(aux[j], aux[i]))   a[k] = aux[j++];
            else                            a[k] = aux[i++];
        }
        
    }
    void sort(std::vector<int> &a, int lo, int hi)
    {// sz: the size of sub-array
        int N = a.size();
        for(int sz = 1; sz < N; sz += sz)
            for(int lo = 0; lo < N - sz; lo += sz)
                merge(a, lo, lo+sz-1, min(lo+sz+sz-1, N-1));
    }
public:
    void sort(std::vector<int> &a)
    {
        aux = std::vector<int>(a.size());
        sort(a, 0, a.size()-1);
    }
};

#endif