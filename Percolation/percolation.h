#include "weighted_quick_union.h"
#include "quick_find.h"
#include <vector>
#include <exception>
#ifndef _PERCOLATION_H_
#define _PERCOLATION_H_
class Percolation
{
    private:
        int N, count;
        bool isQF;
        std::vector<bool> sites;
        WeightedQuickUnion WQU = WeightedQuickUnion(1);
        QuickFind QF = QuickFind(1);

    public:
        Percolation(int n, bool choice)// create N-by-N grid, with all sites blocked
        {
            if(n<=0)
                throw std::invalid_argument("Illegal Argument");
            N = n;
            count = 0;
            isQF = choice;
            sites = std::vector<bool>(N*N+2, false);
            sites[0] = true;
            sites[N*N+1] = true;
            WQU = WeightedQuickUnion(N*N+2);
            QF = QuickFind(N*N+2);
        }

        void Open(int row, int col)// open site (row i, column j) if it is not already
        {
            if(row<1 || row>N || col<1 || col>N)
                throw std::out_of_range("Index Out Of Bounds");

            int current_site = (row-1)*N+col;
            if(sites[current_site])    return;
            
            sites[current_site] = true;
            count++;
            if(isQF)
            {
                // connect the site with top site or buttom site
                if(row==1)
                    QF.Union(0, current_site);
                if(row==N)
                    QF.Union(current_site, N*N+1);

                // connect the sites: up, down, left, right    
                if(row!=1 && sites[(row-2)*N+col])
                {
                    QF.Union(current_site, (row-2)*N+col);
                }
                if(row!=N && sites[row*N+col])
                {
                    QF.Union(current_site, row*N+col);
                }
                if(col!=1 && sites[(row-1)*N+col-1])
                {
                    QF.Union(current_site, (row-1)*N+col-1);
                }
                if(col!=N && sites[(row-1)*N+col+1])
                {
                    QF.Union(current_site, (row-1)*N+col+1);
                }
            }
            else
            {
                // connect the site with top site or buttom site
                if(row==1)
                    WQU.Union(0, current_site);
                if(row==N)
                    WQU.Union(current_site, N*N+1);

                // connect the sites: up, down, left, right    
                if(row!=1 && sites[(row-2)*N+col])
                {
                    WQU.Union(current_site, (row-2)*N+col);
                }
                if(row!=N && sites[row*N+col])
                {
                    WQU.Union(current_site, row*N+col);
                }
                if(col!=1 && sites[(row-1)*N+col-1])
                {
                    WQU.Union(current_site, (row-1)*N+col-1);
                }
                if(col!=N && sites[(row-1)*N+col+1])
                {
                    WQU.Union(current_site, (row-1)*N+col+1);
                }
            }
        }

        bool IsOpen(int row, int col)// is site (row i, column j) open?
        {
            if(row<1 || row>N || col<1 || col>N)
                throw std::out_of_range("Index Out Of Bounds");
            return sites[(row-1)*N+col];
        }

        bool Percolates()// does the system percolate?
        {
            if(isQF)
                return QF.Connected(0, N*N+1);
            else
                return WQU.Connected(0, N*N+1);
        }
};
#endif