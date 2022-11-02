#ifndef SPEEDINGTICKETSSYSTEM_DRIVER_H
#define SPEEDINGTICKETSSYSTEM_DRIVER_H

#include <iostream>
#include <string>

class Driver {
public:
    Driver(std::string driver_name, std::string car_num)
        : _driver_name(driver_name)
        , _car_num(car_num)
    {}

private:
    std::string _driver_name;
    std::string _car_num;
};

#endif // !SPEEDINGTICKETSSYSTEM_DRIVER_H
