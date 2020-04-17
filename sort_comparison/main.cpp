#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <cstring>
#include <chrono>
#include <ctime>

using namespace std::chrono;

int randGene(const int low, const int high);
bool cstrAsc (const char* a, const char* b);
bool cstrDesc (const char* a, const char* b);
bool strAsc(const std::string* a, const std::string* b);
bool strDesc(const std::string* a, const std::string* b);
int qcstrAsc (const void* a, const void* b);
int qcstrDesc (const void* a, const void* b);
int qstrAsc(const void* a, const void* b);
int qstrDesc(const void* a, const void* b);
bool intAsc(const int* a, const int* b);
bool intDesc(const int* a, const int* b);
int qintAsc (const void* a, const void* b);
int qintDesc (const void* a, const void* b);
template <class T>
void measure(const char* msg, T action);
int main()
{
    static const char* ALPHANUM ="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    static const size_t ALPHALEN = strlen(ALPHANUM);

    srand((unsigned)time(NULL));

    std::cout << std::fixed;
    std::cout.precision(8);

    const int SIZE = 1000000;

    char** cstrs;
    cstrs = new char* [SIZE];

    for(int i = 0; i < SIZE; ++i)
    {
        cstrs[i] = new char[33];

        int len = randGene(1,7);

        for(int j = 0; j < len; ++j)
        {
            int idx = rand() % ALPHALEN;
            cstrs[i][j] = ALPHANUM[idx];
        }
        cstrs[i][len] = '\0';
    }
    
    char** cstr;
    cstr = new char* [SIZE];
    
    /* std::sort C strings in ascending order */
    std::copy(cstrs,cstrs+SIZE,cstr);
    measure("std::sort C strings in ascending order",[&cstr,SIZE](){std::sort(cstr,cstr+SIZE,cstrAsc);});

    /* std::sort C strings in descending order */
    std::copy(cstrs,cstrs+SIZE,cstr);
    measure("std::sort C strings in descending order",[&cstr,SIZE](){std::sort(cstr,cstr+SIZE,cstrDesc);});

    /* qsort C strings in ascending order */
    std::copy(cstrs,cstrs+SIZE,cstr);
    measure("qsort C strings in ascending order",[&cstr,SIZE](){std::qsort(cstr,SIZE,sizeof(*cstr),qcstrAsc);});

    /* qsort C strings in descending order */
    std::copy(cstrs,cstrs+SIZE,cstr);
    measure("qsort C strings in descending order",[&cstr,SIZE](){std::qsort(cstr,SIZE,sizeof(*cstr),qcstrDesc);});

    std::string** str;
    str = new std::string* [SIZE];

    /* std::sort C++ strings in ascending order */
    for(int i = 0; i < SIZE; ++i)
        str[i] = new std::string(cstrs[i]);
    measure("std::sort C++ strings in ascending order",[&str,SIZE](){std::sort(str,str+SIZE,strAsc);});

    /* std::sort C++ strings in descending order */
    for(int i = 0; i < SIZE; ++i)
        *str[i] = cstrs[i];
    measure("std::sort C++ strings in descending order",[&str,SIZE](){std::sort(str,str+SIZE,strDesc);});

    /* qsort C++ strings in ascending order */
    for(int i = 0; i < SIZE; ++i)
        *str[i] = cstrs[i];
    measure("qsort C++ strings in ascending order",[&str,SIZE](){std::qsort(str,SIZE,sizeof(*str),qstrAsc);});

    /* qsort C++ strings in ascending order */
    for(int i = 0; i < SIZE; ++i)
        *str[i] = cstrs[i];
    measure("qsort C++ strings in descending order",[&str,SIZE](){std::qsort(str,SIZE,sizeof(*str),qstrDesc);});

    for(int i = 0; i < SIZE; ++i)
    {
        int len = randGene(8,32);

        for(int j = 0; j < len; ++j)
        {
            int idx = rand() % ALPHALEN;
            cstrs[i][j] = ALPHANUM[idx];
        }
        cstrs[i][len] = '\0';
    }

    /* std::sort C strings in ascending order */
    std::copy(cstrs,cstrs+SIZE,cstr);
    measure("std::sort C strings in ascending order",[&cstr,SIZE](){std::sort(cstr,cstr+SIZE,cstrAsc);});

    /* std::sort C strings in descending order */
    std::copy(cstrs,cstrs+SIZE,cstr);
    measure("std::sort C strings in descending order",[&cstr,SIZE](){std::sort(cstr,cstr+SIZE,cstrDesc);});

    /* qsort C strings in ascending order */
    std::copy(cstrs,cstrs+SIZE,cstr);
    measure("qsort C strings in ascending order",[&cstr,SIZE](){std::qsort(cstr,SIZE,sizeof(*cstr),qcstrAsc);});

    /* qsort C strings in descending order */
    std::copy(cstrs,cstrs+SIZE,cstr);
    measure("qsort C strings in descending order",[&cstr,SIZE](){std::qsort(cstr,SIZE,sizeof(*cstr),qcstrDesc);});

    /* std::sort C++ strings in ascending order */
    for(int i = 0; i < SIZE; ++i)
        *str[i] = cstrs[i];
    measure("std::sort C++ strings in ascending order",[&str,SIZE](){std::sort(str,str+SIZE,strAsc);});

    /* std::sort C++ strings in descending order */
    for(int i = 0; i < SIZE; ++i)
        *str[i] = cstrs[i];
    measure("std::sort C++ strings in descending order",[&str,SIZE](){std::sort(str,str+SIZE,strDesc);});

    /* qsort C++ strings in ascending order */
    for(int i = 0; i < SIZE; ++i)
        *str[i] = cstrs[i];
    measure("qsort C++ strings in ascending order",[&str,SIZE](){std::qsort(str,SIZE,sizeof(*str),qstrAsc);});

    /* qsort C++ strings in ascending order */
    for(int i = 0; i < SIZE; ++i)
        *str[i] = cstrs[i];
    measure("qsort C++ strings in descending order",[&str,SIZE](){std::qsort(str,SIZE,sizeof(*str),qstrDesc);});

    /* deallocate memory */
    for(int i = 0; i < SIZE; ++i)
    {
        delete [] cstrs[i];
        delete str[i];
    }
    delete [] cstrs;
    delete [] cstr;
    delete [] str;
     
    int* nums;
    int** arr;
    
    nums = new int [SIZE];
    arr = new int* [SIZE];

    for(int i = 0; i < SIZE; ++i)
        nums[i] = randGene(0,SIZE*5);

    /* std::sort integer in ascending order */
    for(int i = 0; i < SIZE; ++i)
        arr[i] = &nums[i];
    measure("std::sort integer in ascending order",[&arr,SIZE](){std::sort(arr,arr+SIZE,intAsc);});

    /* std::sort integer in descending order */
    for(int i = 0; i < SIZE; ++i)
        arr[i] = &nums[i];
    measure("std::sort integer in decending order",[&arr,SIZE](){std::sort(arr,arr+SIZE,intDesc);});

    /* qsort integer in ascending order */
    for(int i = 0; i < SIZE; ++i)
        arr[i] = &nums[i];
    measure("qsort integer in ascending order",[&arr,SIZE](){std::qsort(arr,SIZE,sizeof(*arr),qintAsc);});

    /* qsort integer in descending order */
    for(int i = 0; i < SIZE; ++i)
        arr[i] = &nums[i];
    measure("qsort integer in descending order",[&arr,SIZE](){std::qsort(arr,SIZE,sizeof(*arr),qintDesc);});
    
    delete [] nums;
    delete [] arr;
    return 0;
}
int randGene(const int low, const int high)
{
    return rand() % (high - low + 1) + low;
}
bool cstrAsc (const char* a, const char* b)
{
    int res = strcmp(a,b);
    return res < 0;
}
bool cstrDesc (const char* a, const char* b)
{
    int res = strcmp(a,b);
    return res > 0;
}
bool strAsc(const std::string* a, const std::string* b)
{
    return *a < *b;
}
bool strDesc(const std::string* a, const std::string* b)
{
    return *a > *b;
}
int qcstrAsc (const void* a, const void* b)
{
    const char* x = *static_cast<const char* const*>(a);
    const char* y = *static_cast<const char* const*>(b);
    return strcmp(x,y);
}
int qcstrDesc (const void* a, const void* b)
{
    const char* x = *static_cast<const char* const*>(a);
    const char* y = *static_cast<const char* const*>(b);
    int res = strcmp(x,y);
    if (res > 0) return -1;
    else if (res < 0) return 1;
    else return 0;
}
int qstrAsc (const void* a, const void* b)
{
    const std::string* x = *static_cast<const std::string* const*>(a);
    const std::string* y = *static_cast<const std::string* const*>(b);
    return strcmp(x->c_str(),y->c_str());
}
int qstrDesc(const void* a, const void* b)
{
    const std::string* x = *static_cast<const std::string* const*>(a);
    const std::string* y = *static_cast<const std::string* const*>(b);
    int res = strcmp(x->c_str(),y->c_str());
    if (res > 0) return -1;
    else if (res < 0) return 1;
    else return 0;
}
template <class T>
void measure(const char* msg, T action)
{
    auto t1 = high_resolution_clock::now();
    action();
    auto t2 = high_resolution_clock::now();
    auto timespan = duration_cast<duration<double>>(t2-t1);
    std::cout << std::left << std::setw(50) << msg << timespan.count() << '\n'; 
}
int qintAsc (const void* a, const void* b)
{
    const int* x = *static_cast<const int* const*>(a);
    const int* y = *static_cast<const int* const*>(b);
    if(*x < *y) return -1;
    else if(*x > *y) return 1;
    else return 0;
}
int qintDesc (const void* a, const void* b)
{
    const int* x = *static_cast<const int* const*>(a);
    const int* y = *static_cast<const int* const*>(b);
    if(*x < *y) return 1;
    else if(*x > *y) return -1;
    else return 0;
}
bool intAsc(const int* a, const int* b)
{
    return *a < *b;
}
bool intDesc(const int* a, const int* b)
{
    return *a > *b;
}
