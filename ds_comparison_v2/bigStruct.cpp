#include "bigStruct.h"
bigStruct::bigStruct(const size_t valIn):val(valIn)
{
}
bool bigStruct::operator < (const bigStruct& bs)const
{
    return val < bs.val;
}
std::ostream& operator << (std::ostream& out, const bigStruct& bs)
{
    out << bs.val;
    return out;
}
