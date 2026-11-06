#ifndef __COOLTHING_HPP__
#define __COOLTHING_HPP__

#include <common.hpp>

#include <string>

class CoolThing : public Stringable
{
public:
    CoolThing(const char *name);
    virtual ~CoolThing();

    std::string toString(void);
private:
    std::string m_name;
};

#endif  //__COOLTHING_HPP__
