#include <iostream>
#include <vector>

#ifndef _TD_MERGE_SORT_H_
#define _TD_MERGE_SORT_H_

class TopDownMergeSort
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
        if(hi <= lo)    return;     // recursion return
        int mid = lo + (hi-lo)/2;
        sort(a, lo, mid);       // sort the left part
        sort(a, mid+1, hi);     // sort the right part
        merge(a, lo, mid, hi);  // merge
    }
public:
    void sort(std::vector<int> &a)
    {
        aux = std::vector<int>(a.size());
        sort(a, 0, a.size()-1);
    }
};

#endif