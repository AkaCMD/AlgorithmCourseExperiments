#include "percolation.h"
#include <vector>
#include <random>
#include <numeric>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <chrono>

class PercolationStats
{
    private:
        int n, t;
        bool isQF;
        double mean, stddev, confidence_lo, confidence_hi;
        std::vector<double> experiments;

    public:
        PercolationStats(int N, int T, bool choice)// perform T independent computational experiments 
        {
            if(N<=0 || T<=0)
                throw std::invalid_argument("Illegal Argument");
            n = N;
            t = T;
            isQF = choice;

            // random number generator
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> dist(1,n);// distribution in range [min, max]

            for(int i=0; i<t; i++)
            {
                Percolation percolation(n, isQF);
                int count = 0;
                while(!percolation.Percolates())
                {
                    int random_row = dist(rng);
                    int random_col = dist(rng);
                    if(!percolation.IsOpen(random_row, random_col))// if the random site has not opened, then open it
                    {
                        percolation.Open(random_row, random_col);
                        count++;
                    }
                }
                experiments.push_back(count*1.0/(n*n));// calculate the site vacancy probability
            }
            mean = Mean();// 样本均值
            stddev = Stddev();// 标准差
            confidence_lo = ConfidenceLo();// 95％置信区间下限
            confidence_hi = ConfidenceHi();// 95％置信区间上限
        }

        double Mean()// sample mean of percolation threshold
        {
            double sum = accumulate(experiments.begin(), experiments.end(), 0.0);
            return sum/(experiments.size()*1.0);
        }

        double Stddev()// sample standard deviation of percolation threshold
        {   
            double accum = 0.0;
	        for_each(experiments.begin(), experiments.end(), [&](const double d) 
            {
		        accum += (d - mean)*(d - mean);
	        });
	        double variance = accum / (experiments.size()-1); //方差
	        return sqrt(variance); //标准差
        }

        double ConfidenceLo()// returns lower bound of the 95% confidence interval
        {
            return mean - (1.96 * stddev) / sqrt(t);
        }

        double ConfidenceHi()// returns upper bound of the 95% confidence interval
        {
            return mean + (1.96 * stddev) / sqrt(t);
        }

        void Print()
        {
            std::cout << "mean:\t\t\t" << mean << std::endl;
            std::cout << "stddev:\t\t\t" << stddev << std::endl;
            std::cout << "confidence_lo:\t\t" << confidence_lo << std::endl;
            std::cout << "confidence_hi:\t\t" << confidence_hi << std::endl;
        }

};

int main()
{
    int N, T;
    std::chrono::system_clock::time_point start_time, end_time;
    std::cout << "Please enter N and T(T independent computational experiments on an N × N grid):" << std::endl;
    std::cin >> N >> T;
    std::cout << "Example values after creating PercolationStats(" << N << "," << T << ")" << std::endl;
    
    // QuickFind 
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "QuickFind" << std::endl;
    start_time = std::chrono::system_clock::now();
    PercolationStats percolation_stats_QF(N, T, true);
    end_time = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    percolation_stats_QF.Print();
    std::cout << "runtime:\t\t" << double(duration.count())/1000.0f << " ms" << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    // WeightedQuickUnion 
    std::cout << "WeightedQuickUnion" << std::endl;
    start_time = std::chrono::system_clock::now();
    PercolationStats percolation_stats_WQU(N, T, false);
    end_time = std::chrono::system_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    percolation_stats_WQU.Print();
    std::cout << "runtime:\t\t" << double(duration.count())/1000.0f << " ms" << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;
    return 0;
}