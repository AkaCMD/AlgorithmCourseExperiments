#include <iostream>
#include <vector>

#ifndef _WEIGHTED_QUICK_UNION_H_
#define _WEIGHTED_QUICK_UNION_H_
class WeightedQuickUnion
{
    private:
        std::vector<int> id;
        std::vector<int> sz;
        int count;
        int n;

    public:
        WeightedQuickUnion(int N)
        {
            count = N;
            n = N;
            id = std::vector<int>(N);
            sz = std::vector<int>(N);
            int index = 0;
            for(int i=0; i<N; i++)
            {
                id[i] = index++;
                sz[i] = 1;
            } 
        }

        int GetCount()
        {
            return count;
        }

        bool Connected(int p, int q)
        {
            return Find(p) == Find(q);
        }

        int Find(int p)//find root
        {
            while(p != id[p]) p = id[p];
            return p;
        }

        void Union(int p, int q)
        {
            int i = Find(p);
            int j = Find(q);
            if(i == j) return;
            if(sz[i] < sz[j])   { id[i] = j; sz[j] += sz[i];}
            else                { id[j] = i; sz[i] += sz[j];}
            count--;
        }

        void Print()
        {
            for(int i=0; i<n; i++)
            {
                std::cout << id[i] << " ";
            }
        }

};
#endif