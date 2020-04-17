#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <array>
#include <list>
#include <vector>
#include <set>
#include <ctime>
#include <chrono> 
#include <random> // mersenne_twister_engine constructor

typedef std::chrono::high_resolution_clock my_clock; // typedef clock
std::chrono::duration<double> t_span; // represents a time interval
const size_t SIZE = 500000;

void log_msg(const char* action, const char* type, const my_clock::time_point& t1, const my_clock::time_point& t2, const bool header = true); 
int main()
{
    // construct a trivial random generator engine from a time-based seed
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    
    std::mt19937 generator(seed); // mt19937 is a standard mersenne_twister_engine

    my_clock::time_point t1;
    my_clock::time_point t2;

    std::cout.precision(5);
    std::cout << std::fixed;

    std::cout << "Loading...\n\n";
    
    // Static Array 
    size_t static_array[SIZE];
    t1 = my_clock::now();
    for(size_t i =0; i < SIZE; ++i)
        static_array[i] = generator();
    t2 = my_clock::now();
    log_msg("load\n\n","Static array",t1,t2);

    // STL Array
    std::array<size_t,SIZE> stl_array;
    t1 = my_clock::now();
    for(size_t i = 0; i < SIZE; ++i)
        stl_array[i] = generator();
    t2 = my_clock::now();
    log_msg("load\n\n","STL array",t1,t2);
     
    // Dynamic Array
    size_t* ptr = new size_t[SIZE];
    t1 = my_clock::now();
    for(size_t i = 0; i < SIZE; ++i)
        ptr[i] = generator();
    t2 = my_clock::now();
    log_msg("load\n\n","Dynamic array",t1,t2);

    // STL Vector
    std::vector<size_t> vect(SIZE);
    t1 = my_clock::now();
    for(size_t i = 0; i < SIZE; ++i)
        vect[i] = generator();
    t2 = my_clock::now();
    log_msg("load\n\n","STL Vector",t1,t2);

    // STL List
    std::list<size_t> lst(SIZE);
    t1 = my_clock::now();
    for(auto it = lst.begin(); it != lst.end(); ++it)
        *it = generator();
    t2 = my_clock::now();
    log_msg("load\n\n","STL List",t1,t2);

    // Multi Set
    std::multiset<size_t> multi_set;
    std::multiset<size_t>::iterator msit;
    t1 = my_clock::now();
    for(size_t i =0; i < SIZE; ++i)
        msit = multi_set.insert(generator());
    t2 = my_clock::now();
    log_msg("load\n\n","Multi Set",t1,t2);

    ////////////////////////////////////////////////////////////////////////
    
    std::cout << "Finding an element...\n\n";
   
    // Static Array
    t1 = my_clock::now();
    std::find(static_array,static_array+SIZE,static_array[0]);
    t2 = my_clock::now();
    log_msg("find the first element\n","Static Array",t1,t2);
    t1 = my_clock::now();
    std::find(static_array,static_array+SIZE,static_array[SIZE/2]);
    t2 = my_clock::now();
    log_msg("find the middle element\n","Static Array",t1,t2,false);
    t1 = my_clock::now();
    std::find(static_array,static_array+SIZE, static_array[SIZE-1]);
    t2 = my_clock::now();
    log_msg("find the last element\n\n","Static Array",t1,t2,false);
    
    // STL Array
    t1 = my_clock::now();
    std::find(stl_array.begin(),stl_array.end(),stl_array[0]);
    t2 = my_clock::now();
    log_msg("find the first element\n","STL Array",t1,t2);
    t1 = my_clock::now();
    std::find(stl_array.begin(),stl_array.end(),stl_array[SIZE/2]);
    t2 = my_clock::now();
    log_msg("find the middle element\n","STL Array",t1,t2,false);
    t1 = my_clock::now();
    std::find(stl_array.begin(),stl_array.end(), stl_array[SIZE-1]);
    t2 = my_clock::now();
    log_msg("find the last element\n\n","STL Array",t1,t2,false);
   
    // Dynamic Array
    t1 = my_clock::now();
    std::find(ptr,ptr+SIZE,ptr[0]);
    t2 = my_clock::now();
    log_msg("find the first element\n","Dynamic Array",t1,t2);
    t1 = my_clock::now();
    std::find(ptr,ptr+SIZE,ptr[SIZE/2]);
    t2 = my_clock::now();
    log_msg("find the middle element\n","Dynamic Array",t1,t2,false);
    t1 = my_clock::now();
    std::find(ptr,ptr+SIZE, ptr[SIZE-1]);
    t2 = my_clock::now();
    log_msg("find the last element\n\n","Dynamic Array",t1,t2,false);
   
    // STL Vector
    t1 = my_clock::now();
    std::find(vect.begin(),vect.end(),vect[0]);
    t2 = my_clock::now();
    log_msg("find the first element\n","STL Vector",t1,t2);
    t1 = my_clock::now();
    std::find(vect.begin(),vect.end(),vect[SIZE/2]);
    t2 = my_clock::now();
    log_msg("find the middle element\n","STL Vector",t1,t2,false);
    t1 = my_clock::now();
    std::find(vect.begin(),vect.end(), vect[SIZE-1]);
    t2 = my_clock::now();
    log_msg("find the last element\n\n","STL Vector",t1,t2,false);
   
    // STL List
    t1 = my_clock::now();
    std::find(lst.begin(),lst.end(),lst.front());
    t2 = my_clock::now();
    log_msg("find the first element\n","STL List",t1,t2);
    std::list<size_t>::iterator lit = lst.begin();
    for(size_t i = 0; i < SIZE/2; ++i)
        ++lit;
    t1 = my_clock::now();
    std::find(lst.begin(),lst.end(),*lit);
    t2 = my_clock::now();
    log_msg("find the middle element\n","STL List",t1,t2,false);
    t1 = my_clock::now();
    std::find(lst.begin(),lst.end(), lst.back());
    t2 = my_clock::now();
    log_msg("find the last element\n\n","STL List",t1,t2,false);

    // Multi Set
    t1 = my_clock::now();
    std::find(multi_set.begin(),multi_set.end(),*multi_set.begin());
    t2 = my_clock::now();
    log_msg("find the first element\n","Multi Set",t1,t2);
    msit = multi_set.begin();
    for(size_t i =0; i < SIZE/2; ++i)
        ++msit;
    t1 = my_clock::now();
    std::find(multi_set.begin(),multi_set.end(),*msit);
    t2 = my_clock::now();
    log_msg("find the middle element\n","Multi Set",t1,t2,false);
    t1 = my_clock::now();
    std::find(multi_set.begin(),multi_set.end(), *multi_set.end());
    t2 = my_clock::now();
    log_msg("find the last element\n\n","Multi Set",t1,t2,false);

    delete [] ptr; 
    
    return 0;
}
void log_msg(const char* action, const char* type, const my_clock::time_point& t1, const my_clock::time_point& t2, const bool header) 
{  
    t_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2-t1);
    if(header)
        std::cout << '<' << type << '>' << " with " << SIZE << " random elements" << std::endl;
    std::cout << "It took " << t_span.count() << " seconds to " << action;
}
