#include <iostream>

#include <sourcelib/coolthing.hpp>

int main(int argc, char *argv[])
{
    CoolThing thing = CoolThing("hello world");
    std::cout << thing.toString() << std::endl;
    return 0;
}
