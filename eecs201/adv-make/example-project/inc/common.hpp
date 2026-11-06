#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#include <string>

class Stringable
{
public:
    virtual ~Stringable() {};
    virtual std::string toString(void)=0;
};

#endif  //__COMMON_HPP__
