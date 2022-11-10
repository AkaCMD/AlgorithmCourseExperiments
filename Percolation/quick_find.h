#include <iostream>
#include <vector>

#ifndef _QUICK_FIND_H_
#define _QUICK_FIND_H_
class QuickFind
{   
    private:
        std::vector<int> id;
        int count;
        int n;

    public:
        QuickFind(int N)
        {
            count = N;
            n = N;
            id = std::vector<int>(N);
            int index = 0;
            for(int i=0; i<n; i++)
            {
                id[i] = index++;
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

        int Find(int p)
        {
            return id[p];
        }

        void Union(int p, int q)
        {
            int pID = Find(p);
            int qID = Find(q);
            if(pID == qID) return;
            for(int i=0; i<n; i++)
            {
                if(id[i] == pID) id[i] = qID;
            }
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