#include <iostream>
#include <string>

#include <sourcelib/coolthing.hpp>

CoolThing::CoolThing(const char *name)
{
    m_name = std::string(name);
}

CoolThing::~CoolThing()
{
}

std::string CoolThing::toString(void)
{
    return m_name;
}
