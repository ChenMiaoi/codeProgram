#ifndef SPEEDINGTICKETSSYSTEM_TICKETS_H
#define SPEEDINGTICKETSSYSTEM_TICKETS_H

#include <iostream>
#include <string>

typedef enum TICKET_TYPE {
    DRINKING = 0,           // 酒驾
    DRUNK = 0,              // 醉驾
    JAYWALKING = 0,         // 闯红灯
    REAR_END = 0,           // 追尾
    PARKING = 0,            // 违章停车
    E_BUS_LINE = 0,         // 擅行公交车道
    LIMIT_DRIVE = 0,        // 限行日出行
    COVER_PLATE = 0,        // 遮挡污损车牌
    NO_PLATE_DRIVE = 0,     // 无牌驾驶
    NO_LISENCE_DRIVE = 0    // 无照驾驶
}TICKET_TYPE;

typedef enum PUNISH_TYPE {
    UNSCENE = 0,            // 非现场
    SCENE = 0               // 现场
}PUNISH_TYPE;

class Tickets {
public:
    Tickets(std::string car_num, std::string driving_num, std::string police_num, std::string ticket_num,
            TICKET_TYPE ticket_type, std::string punish_time, PUNISH_TYPE punish_type, double punish_money, bool punish_state)
            : _car_num(car_num)
            , _driving_num(driving_num)
            , _police_num(police_num)
            , _ticket_num(ticket_num)
            , _ticket_type(ticket_type)
            , _punish_time(punish_time)
            , _punish_type(punish_type)
            , _punish_money(punish_money)
            , _punish_state(punish_state)
    {}
public:
    std::string _car_num;
    std::string _driving_num;
    std::string _police_num;
    std::string _ticket_num;
    TICKET_TYPE _ticket_type;   //位图
    std::string _punish_time;
    PUNISH_TYPE _punish_type;
    double _punish_money;
    bool _punish_state;
};
#endif // !SPEEDINGTICKETSSYSTEM_TICKETS_H
