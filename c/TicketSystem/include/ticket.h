#ifndef TICKETSYSTEM_TICKET_H
#define TICKETSYSTEM_TICKET_H

#include "allInc.h"

#define DRINKING            "酒驾"
#define DRUNK               "醉驾"
#define JAYWALKING          "闯红灯"
#define REAR_END            "追尾"
#define PARKING             "违章停车"
#define E_BUS_LINE          "擅行公交车道"
#define LIMIT_DRIVE         "限行日出行"
#define COVER_PLATE         "遮挡污损车牌"
#define NO_PLATE_DRIVE      "无牌驾驶"
#define NO_LISENCE_DRIVE    "无照驾驶"

#define ON_SCENE            "现场"
#define NON_SCENE           "非现场"

#define DEALED              "已处理"
#define UN_DEALED           "未处理"

#define CAR_ID               1
#define DRIVER_ID            2
#define POLICE_ID            3
#define TICKET_ID            4

#define TICKET_TYPE          1
#define PUNISH_TYPE          2
#define PUNISH_MONEY         3
#define PUNISH_STAT          4

#define CAR_MAX             32
#define DRIVER_MAX          32
#define POLICE_MAX          32
#define TICKET_MAX          32
#define PUNISH_MAX          32x
#define TYPE_MAX            32
#define SIZE_MAX            32

#define SHOW_SHOW           1
#define SHOW_SORT           2
#define SHOW_DEALED         3
#define COUNT_BY_YEAR       4

typedef struct Data {
    char car_num[CAR_MAX] = {0};          //车牌号
    char driver_id[DRIVER_MAX] = {0};     //驾驶证号
    char police_id[POLICE_MAX] = {0};     //交警编号
    char ticket_id[TICKET_MAX] = {0};     //罚单号
    char ticket_type[TYPE_MAX] = {0};                   //罚单类型
    char punish_time[PUNISH_MAX] = {0};             //处罚时间
    char punish_type[TYPE_MAX] = {0};                 //处罚类型
    double punish_money = 0;                  //处罚金额
    char punish_stat[TYPE_MAX] = {0};                 //处罚状态
}Data;

typedef struct Ticket {
    Ticket* next;
    Data data;
}Ticket;

extern Ticket* init();
extern bool insert(Ticket** pTicket);
extern bool modify(Ticket** pTicket);
extern Ticket* search(Ticket* ticket);
extern bool erase(Ticket** pTicket);
extern void show(Ticket* ticket);

#endif //TICKETSYSTEM_TICKET_H
