#include <iostream>
#include <chrono>
#include <iomanip>
#include <random>
#include <algorithm>
#include <sstream>
#include <vector>
#include <ctime>
#include <list>
#include <locale>
#include <unordered_set>
#include <string>
#include <map>
#include <type_traits>
#include <functional>
#include "bigStruct.h"

using namespace std::chrono;

/* size_t for main exercise and bigStruct for complementary exercise */
typedef size_t dataType;
//typedef bigStruct dataType;

template <class T>
duration<double> measure(T& container, const std::vector<size_t>& nums, 
                         void(*func)(T& c, const std::vector<size_t>& v));

template <class T>
void populate(T& container, const std::vector<size_t>& nums); 

template <class T>
void remove(T& container, const std::vector<size_t>& idx);

template <class T>
void display(const T& container);

std::string format(const size_t x);

int main()
{
    const size_t SIZES = 15;
    const size_t MAXSIZE[SIZES] = {1,10,20,30,40,50,100,500,1000,2000,3000,4000,5000,6000,7000};

    /* Number of experiments for each size */
    const size_t NUMOFEXPS = 1;
    
    std::cout.precision(8);
    std::cout << std::fixed;

    for(size_t i = 0; i < SIZES; ++i)
    {
        /*
         *  first element is time taken for insertion
         *  second element is time taken for removal
         */
        std::vector<duration<double>> vector(2);
        std::vector<duration<double>> list(2);
        std::vector<duration<double>> map(2);

        std::cout << format(MAXSIZE[i]) << " elements\n";

        for(size_t j = 0; j < NUMOFEXPS; ++j)
        {
            unsigned seed = system_clock::now().time_since_epoch().count();
            std::mt19937 generator(seed);
            std::uniform_int_distribution<size_t> uid (0, MAXSIZE[i] * 10000);
            
            /* generating random unique values for insertion and indices for removal */
            auto nums = [&generator,&uid](const size_t size)
            {
                std::vector<std::vector<size_t>> res(2);
                std::unordered_set<size_t> myset;

                for (size_t k = 0; k < size; ++k)
                {
                    size_t num;
                    do
                        num = uid(generator);
                    while(myset.count(num) == 1);
                    res[0].push_back(num);
                    res[1].push_back(generator() % (size - k));
                    myset.insert(num);
                }
                return res;
            }(MAXSIZE[i]);

            std::vector<dataType> vect;
            std::list<dataType> lst;
            std::map<dataType,size_t> mp;

            /* Measure insertion time */
            vector[0] += measure(vect,nums[0],populate);
            list[0] += measure(lst,nums[0],populate);
            map[0] += measure(mp,nums[0],populate);

            //display(vect);
            //display(lst);
            //display(mp);

            /* Measure removal time */
            vector[1] += measure(vect,nums[1],remove);
            list[1] += measure(lst,nums[1],remove);
            map[1] += measure(mp,nums[1],remove);
        }

        /* Get the average of experiments */
        std::cout << "Vector:\t" << std::setw(15) << vector[0].count() / NUMOFEXPS << std::setw(15) << vector[1].count() / NUMOFEXPS << '\n'; 
        std::cout << "List  :\t" << std::setw(15) << list[0].count() / NUMOFEXPS << std::setw(15) << list[1].count() / NUMOFEXPS << '\n'; 
        std::cout << "Map   :\t" << std::setw(15) << map[0].count() / NUMOFEXPS << std::setw(15) << map[1].count() / NUMOFEXPS << "\n\n"; 
    }
    return 0;
}

template <class T>
duration<double> measure(T& container, const std::vector<size_t>& nums,
                         void(*func)(T& c, const std::vector<size_t>& v))
{
    high_resolution_clock::time_point t1;
    high_resolution_clock::time_point t2;
    duration<double> timeSpan;

    t1 = high_resolution_clock::now();
    func(container,nums);
    t2 = high_resolution_clock::now();

    timeSpan = duration_cast<duration<double>>(t2-t1);
    return t2-t1;
}

template <class T>
void populate(T& container, const std::vector<size_t>& nums)
{
    for (size_t i = 0; i < nums.size(); ++i)
    {
        if constexpr (std::is_same<T,std::map<dataType,size_t>>::value)
            container.insert(std::pair<dataType,size_t>(nums[i],0));
        else
        {
            auto it = container.begin();
            while(it != container.end() && *it < nums[i])
                ++it;
            container.insert(it,nums[i]);
        }
    }
}

template <class T>
void remove(T& container, const std::vector<size_t>& idx)
{
    for(size_t i = 0; i < idx.size(); ++i)
    {
        auto it = container.begin();
        for(size_t j = 0; j < idx[i]; ++j)
            ++it;
        container.erase(it);
    }
}

template <class T>
void display(const T& container)
{
    if constexpr (std::is_same<T,std::map<dataType,size_t>>::value)
        std::for_each(container.begin(),container.end(),[](const std::pair<dataType,size_t>& x){std::cout << x.first << ' ';});
    else
        std::for_each(container.begin(),container.end(),[](const dataType& n){std::cout << n << ' ';});
    std::cout << '\n';
}

std::string format(const size_t x)
{
    std::stringstream ss;
    ss.imbue(std::locale("en_US.UTF-8"));
    ss << x;
    return ss.str();
}
