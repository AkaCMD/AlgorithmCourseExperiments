#include "buttom_up_merge_sort.h"
#include "djistra_3way_quick_sort.h"
#include "insertion_sort.h"
#include "random_quick_sort.h"
#include "top_down_merge_sort.h"
#include <ctime>
#include <chrono>

double times[5][10];
std::vector<double> average_times(5);
std::chrono::system_clock::time_point start_time, end_time;

class Experiments
{
public:
    template <typename T>
    static void show(std::vector<T> &a)
    {// print the array
        for(auto i=a.begin();i!=a.end();i++)
        {
            std::cout << *i << " ";
        }
        std::cout << std::endl;
    }

    static bool is_sorted(std::vector<int> &a)
    {// test if the array has sorted
        for(auto i = a.begin(); i!=a.end();i++)
        {
            if(*i < *(i-1))    return false;
        }
        return true;
    }

    static void generate_data(std::vector<int> &data, int count)
    {
        // random number generator
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(1, 1000);        // distribution in range [min, max]

        // insert the random numbers
        data = std::vector<int>(count);
        for (int i = 0; i < count; ++i)
            data[i] = distribution(generator);
    }

    static void show_times()
    {
        for(int i = 0; i < 5; i++)
        {
            switch (i)
            {
            case 0:
                std::cout << "IS:\t";
                break;
            case 1:
                std::cout << "TDM:\t";
                break;
            case 2:
                std::cout << "BUM:\t";
                break;
            case 3:
                std::cout << "RQ:\t";
                break;
            case 4:
                std::cout << "QD3P:\t";
                break;
            default:
                break;
            }
            for(int j = 0; j < 10; j++)
            {
                std::cout << times[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    static void get_average_times()
    {
        double sum = 0;
        for(int i = 0; i < 5; i++)
        {
            sum = 0;
            for(int j = 0; j < 10; j++)
            {
                sum += times[i][j];
            }
            average_times[i] = sum/10.0f;
        }
    }
    static void start_timer()
    {
        start_time = std::chrono::system_clock::now();
    }
    static void end_timer()
    {
        end_time = std::chrono::system_clock::now();
    }
    static double get_elasped_time()
    {
        return double(std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count())/1000.0f;
    }
};

int main()
{
    std::vector<int> data_set;
    std::vector<int> temp_data_set;
    int count;  // amount of test data
    std::cout << "Please enter the size of data set: " << std::endl;
    std::cin >> count;
    Experiments::generate_data(data_set, count);
    std::cout << std::endl <<  "random data: " << std::endl;
    Experiments::show(data_set);
    for(int i = 0; i < 10; i++)
    {
        temp_data_set = data_set;
        Experiments::start_timer();
        InsertionSort::sort(temp_data_set);
        Experiments::end_timer();
        times[0][i] = Experiments::get_elasped_time();

        temp_data_set = data_set;
        Experiments::start_timer();
        TopDownMergeSort TDMsort;
        TDMsort.sort(temp_data_set);
        Experiments::end_timer();
        times[1][i] = Experiments::get_elasped_time();

        temp_data_set = data_set;
        Experiments::start_timer();
        ButtomUpMergeSort BUMsort;
        BUMsort.sort(temp_data_set);
        Experiments::end_timer();
        times[2][i] = Experiments::get_elasped_time();

        temp_data_set = data_set;
        Experiments::start_timer();
        RandomQuickSort::sort(temp_data_set);
        Experiments::end_timer();
        times[3][i] = Experiments::get_elasped_time();

        temp_data_set = data_set;
        Experiments::start_timer();
        ThreeWayQuickSort::sort(temp_data_set);
        Experiments::end_timer();
        times[4][i] = Experiments::get_elasped_time();
    }
    std::cout << std::endl << "sorted:" << std::endl;
    Experiments::show(temp_data_set);
    std::cout << std::endl;

    std::cout << "times(ms): " << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;
    Experiments::show_times();
    std::cout << std::endl;
    std::cout << "average times(ms): " << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;
    Experiments::get_average_times();
    Experiments::show(average_times);

    return 0;
}