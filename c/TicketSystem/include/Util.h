#ifndef TICKETSYSTEM_UTIL_H
#define TICKETSYSTEM_UTIL_H

#include "allInc.h"
#include "ticket.h"

typedef enum MENU_ALL {
    EXIT_ALL,
    ROOT,
    POLICE,
    DRIVER
}MENU_ALL;

typedef enum MENU_POLICE {
    EXIT_POLICE,
    INSERT,
    MODIFY,
    DELETE,
    SEARCH,
    SHOW
}MENU_POLICE;

typedef char* Tickettype;
typedef char* Punishtype;
typedef char* Punishstat;

//主菜单
extern void Menu_ALL();
//交警菜单
extern void Menu_Police();
//罚单类型菜单
extern void Menu_Ticket_Type();
//罚单状态菜单
extern void Menu_Punish_Stat();
//处罚方式菜单
extern void Menu_Punish_Type();
//查询方式菜单
extern void Menu_Search();
//修改方式菜单
extern void Menu_Modify();
//显示菜单
extern void Menu_Show();
//判断密码
extern bool IsPasswd(const char* passwd);
//修改密码
extern bool ModifyPasswd();
//录入信息
extern void Info(Ticket* ticket);
//查询方式
extern Ticket* SearchType(Ticket* ticket, char* type_var, int type);
//寻找前驱
extern Ticket* searchPrev(Ticket* ticket, char* car_num);
//打印信息
extern void Print(Ticket* ticket);
//罚单类型的插入
extern void TicketType(int type, Tickettype ticket_type);
//处罚类型的插入
extern void PunishType(int type, Punishtype punish_type);
//处理状态的插入
extern void PunishStat(int type, Punishstat punish_stat);
//排序(从小到大)
extern void Sort(Ticket* ticket);
//统计未处理
extern void Dealed(Ticket* ticket);
//统计年月罚单次数
extern void Count(Ticket* ticket);

#endif //TICKETSYSTEM_UTIL_H
