#include <iostream>
/// @brief IndexMinPQ
class IndexPQ
{
private:
    int *pq;
    int *qp;//pq[qp[i]] = qp[pq[i]]
    int *key;//actual value
    int sz;
    int capacity;//the size of indexPQ
    
public:
    IndexPQ(int n)
    {
        pq = new int[n+1];//pq[0] is unused
        qp = new int[n+1];
        for(int i=1; i <= n; i++)   qp[i] = -1;//-1 means empty
        key = new int[n+1];
        sz = 0;
        capacity = n;
    }
    ~IndexPQ()
    {
        delete []pq;
        delete []qp;
        delete []key;
    }
    int operator[](int n)
    {
        return key[n];
    }
    bool insert(int k, int val)//insert a value as k, O(lgn)
    {
        if(k > capacity)    return false;
        sz++;
        pq[sz] = k;
        qp[k] = sz;
        key[k] = val;
        swim(sz);//correct the new elem's pos in pq
        return true;
    }
    int pop()//return the index on the top; pop the top;
    {
        int v = topIndex();
        if(sz > 0)
        {
            exch(1, sz--);
            sink(1);
            key[pq[sz+1]]=NULL;
            qp[pq[sz+1]]=-1;
        }
        return v;
    }
    bool contain(int k)
    {
        return qp[k] != -1;
    }
    int top()//get the min. value
    {
        return key[pq[1]];
    }
    int topIndex()
    {
        return pq[1];
    }
    void update(int k, int val)
    {
        if(-1 == qp[k]) insert(k,val);
        key[k] = val;
        swim(qp[k]);
        sink(qp[k]);
    }
    void del(int k)
    {
        int index = qp[k];
        exch(index, sz--);
        swim(index);
        sink(index);
        key[k]=NULL;
        qp[k]=-1;
    }
    bool empty()
    {
        return sz==0;
    }
    int size()
    {
        return sz;
    }

    void print()
    {
        for(int i=1;i<=sz;i++) std::cout<<i<<'\t'<<pq[i]<<":\t"<<key[pq[i]]<< std::endl;
    }

private:
    bool cmp(int a, int b)//if a<b, returns true
    {
        return a<b;
    }
    void swim(int n){//O(lgN)
        while(n>1 && cmp(key[pq[n]],key[pq[n>>1]]))//compare it with parent node
        {
            exch(n,n>>1);
            n>>=1;
        }
    }
    void sink(int n){//O(lgN)
        while(2*n<=sz)//make sure it has child node
        {
            int k=2*n;
            if(k<sz && cmp(key[pq[k+1]],key[pq[k]]))    k++;//select the one with high priority among the left and right child nodes
            if(cmp(key[pq[k]],key[pq[n]]))
            {//if k has higher priority than n, n sinks
                exch(n,k);
                n=k;
            }
            else break;
        }
    }
    void exch(int a,int b){
        int i=pq[a],j=pq[b];
        int temp;
        temp = pq[a];   pq[a] = pq[b];  pq[b] = temp;
        temp = qp[i];   qp[i] = qp[j];  qp[j] = temp;
    }
};
