#ifndef BIGSTRUCT_H 
#define BIGSTRUCT_H
#include <iostream>
/* A big struct for complementary exercise */
struct bigStruct
{
    bigStruct(const size_t valIn = 0);
    bool operator < (const bigStruct& bs) const;
    // << operator overloaded for display 
    friend std::ostream& operator << (std::ostream& out, const bigStruct& bs);
    size_t val;
    size_t bigArr[100000];
};
#endif
