#include "../include/Util.h"

void Menu_ALL() {
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("|\t\t\t1.ROOT     2.POLICE\t\t\t|\n");
    printf("|                                                               |\n");
    printf("|\t\t\t3.DRIVER   0.EXIT\t\t\t|\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
}

void Menu_Police() {
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("|\t\t\t1.INSERT     2.MODIFY\t\t\t|\n");
    printf("|                                                               |\n");
    printf("|\t\t\t3.DELETE     4.SEARCH\t\t\t|\n");
    printf("|                                                               |\n");
    printf("|\t\t\t 5.SHOW       0.EXIT\t\t\t|\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
}

void Menu_Ticket_Type() {
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("|\t\t\t    罚单类型\t\t\t\t|\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("|\t1.酒驾\t\t    2.醉驾\t\t3.闯红灯\t|\n");
    printf("|                                                               |\n");
    printf("|\t4.追尾\t\t\t\t\t5.违章停车\t|\n");
    printf("|                                                               |\n");
    printf("|\t6.擅行公交车道\t\t\t\t7.限行日出行\t|\n");
    printf("|                                                               |\n");
    printf("|\t8.遮挡污损车牌\t    9.无牌驾驶\t\t10.无照驾驶\t|\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
}

void Menu_Punish_Type() {
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("|                                                               |\n");
    printf("|\t\t\t1.现场     0.非现场\t\t\t|\n");
    printf("|                                                               |\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
}

void Menu_Punish_Stat() {
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("|                                                               |\n");
    printf("|\t\t\t1.已处理     0.未处理\t\t\t|\n");
    printf("|                                                               |\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
}

void Menu_Search() {
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("|\t\t1.车牌号\t           2.驾驶证号\t\t|\n");
    printf("|                                                               |\n");
    printf("|\t\t3.开单交警号\t\t   4.处罚单号\t\t|\n");
    printf("|                                                               |\n");
    printf("|\t\t\t\t0.退出\t\t\t\t|\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
}

void Menu_Modify() {
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("|\t\t\t1.罚单类型     2.处罚方式\t\t|\n");
    printf("|                                                               |\n");
    printf("|\t\t\t3.罚款金额     4.处理状态\t\t|\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
}

void Menu_Show() {
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("|\t\t\t1.SHOW       2.SORT\t\t\t|\n");
    printf("|                                                               |\n");
    printf("|\t\t\t3.DEALED     4.COUNTByYEAR\t\t|\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
}

bool IsPasswd(const char* passwd) {
    FILE* fp = fopen(PATH_PASSWD, "r");
    if (fp == NULL) {
        perror("Passwd File Open Error!");
        return false;
    }else {
        char pswd[PASSWD_MAX];
        fscanf(fp, "%s", pswd);
        //printf("%s\n", pswd);
        if (strcmp(passwd, pswd) == 0) {
            printf("Passwd Correct!\n");
            fclose(fp);
            return true;
        }else {
            printf("Passwd Error!\n");
            fclose(fp);
            return false;
        }

    }
}

bool ModifyPasswd() {
    char pswd[PASSWD_MAX] = {}, passwd_1[PASSWD_MAX], passwd_2[PASSWD_MAX];
    int ref = 0, count = 2;
    printf("请输入您的密码: ");
    scanf("%s", pswd);
    if (IsPasswd(pswd)) {
        do {
            printf("请输入您想要修改的密码: ");
            scanf("%s", passwd_1);
            printf("请再次输入您的密码: ");
            scanf("%s", passwd_2);
            if ((ref = strcmp(passwd_1, passwd_2)) == 0) {
                FILE* fp = fopen(PATH_PASSWD, "w+");
                if (fp != NULL) {
                    fprintf(fp, "%s", passwd_1);
                    fclose(fp);
                    return true;
                }else {
                    perror("Passwd File Open Error!");
                    return false;
                }
            } else {
                if (count == 0) { break; }
                printf("两次密码不正确! 请重新输入, 您还有%d次机会\n", count);
            }
            count--;
        } while (ref);
    }else {
        return false;
    }
}

void TicketType(int type, Tickettype ticket_type) {
    switch (type) {
        case 1:
            strcpy(ticket_type, DRINKING);
            break;
        case 2:
            memcpy(ticket_type, DRUNK, strlen(DRUNK));
            break;
        case 3:
            memcpy(ticket_type, JAYWALKING, strlen(JAYWALKING));
            break;
        case 4:
            memcpy(ticket_type, REAR_END, strlen(REAR_END));
            break;
        case 5:
            memcpy(ticket_type, PARKING, strlen(PARKING));
            break;
        case 6:
            memcpy(ticket_type, E_BUS_LINE, strlen(E_BUS_LINE));
            break;
        case 7:
            memcpy(ticket_type, LIMIT_DRIVE, strlen(LIMIT_DRIVE));
            break;
        case 8:
            memcpy(ticket_type, COVER_PLATE, strlen(COVER_PLATE));
            break;
        case 9:
            memcpy(ticket_type, NO_PLATE_DRIVE, strlen(NO_PLATE_DRIVE));
            break;
        case 10:
            memcpy(ticket_type, NO_LISENCE_DRIVE, strlen(NO_LISENCE_DRIVE));
            break;
        default:
            printf("您输出的选项有误!\n");
            break;
    }
}

void PunishType(int type, Punishtype punish_type) {
    switch (type) {
        case 0:
            memcpy(punish_type, NON_SCENE, strlen(NON_SCENE));
            break;
        case 1:
            memcpy(punish_type, ON_SCENE, strlen(ON_SCENE));
            break;
        default:
            printf("您输入的选项有误!\n");
            break;
    }
}

void PunishStat(int type, Punishstat punish_stat) {
    switch (type) {
        case 0:
            memcpy(punish_stat, UN_DEALED, strlen(UN_DEALED));
            break;
        case 1:
            memcpy(punish_stat, DEALED, strlen(DEALED));
            break;
        default:
            printf("您输入的选项有误!\n");
            break;
    }
}

static void DealTime(char* time, struct tm* tmp_ptr) {
    char year[5], month[3], day[3], hour[3], min[3], sec[3];
    sprintf(year,"%d", tmp_ptr->tm_year + 1900);
    sprintf(month,"%d", tmp_ptr->tm_mon + 1);
    sprintf(day,"%d", tmp_ptr->tm_mday);
    sprintf(hour,"%d", tmp_ptr->tm_hour);
    sprintf(min,"%d", tmp_ptr->tm_min);
    sprintf(sec,"%d", tmp_ptr->tm_sec);
    memcpy(time, year, strlen(year));
    strcat(time, "-");
    strcat(time, month);
    strcat(time, "-");
    strcat(time, day);
    strcat(time, "-");
    strcat(time, hour);
    strcat(time, ":");
    strcat(time, min);
    strcat(time, ":");
    strcat(time, sec);
    time[strlen(time) + 1] = '\0';
}

typedef char* Punishtime;
#define PUNISH_TIME 32
static void PunishTime(Punishtime punish_time) {
    time_t local_time;
    struct tm* tmp_ptr = localtime(&local_time);
    char time[PUNISH_TIME] = {};
    DealTime(time, tmp_ptr);
    memcpy(punish_time, time, strlen(time));
}

void Info(Ticket* tail) {
    printf("请您输入车牌号: ");
    scanf("%s", tail->data.car_num);
    printf("请您输入驾驶证号: ");
    scanf("%s", tail->data.driver_id);
    printf("请您输入开单交警编号: ");
    scanf("%s", tail->data.police_id);
    printf("请您输入处罚单号: ");
    scanf("%s", tail->data.ticket_id);
    Menu_Ticket_Type();
    int type = 0;
    printf("请您输入罚单类型: ");
    scanf("%d", &type);
    TicketType(type, tail->data.ticket_type);
    PunishTime(tail->data.punish_time);
    printf("处罚时间: 已根据您的本地时间填入: %s\n", tail->data.punish_time);
    Menu_Punish_Type();
    printf("请您输入处罚方式: ");
    scanf("%d", &type);
    PunishType(type, tail->data.punish_type);
    printf("请您输入罚款金额: ");
    scanf("%lf", &tail->data.punish_money);
    Menu_Punish_Stat();
    printf("请您输入处理状态: ");
    scanf("%d", &type);
    PunishStat(type, tail->data.punish_stat);
}

Ticket* SearchType(Ticket* ticket, char* type_var, int type) {

    switch (type) {
        case CAR_ID:
            while (ticket != NULL) {
                if (strcmp(ticket->data.car_num, type_var) == 0) {
                    printf("查询成功，信息为: \n");
                    Print(ticket);
                    return ticket;
                }
                ticket = ticket->next;
            }
            printf("没有车牌号为%s的记录!\n", type_var);
            return NULL;
        case DRIVER_ID:
            while (ticket != NULL) {
                if (strcmp(ticket->data.driver_id, type_var) == 0) {
                    printf("查询成功，信息为: \n");
                    Print(ticket);
                    return ticket;
                }
                ticket = ticket->next;
            }
            printf("没有驾驶证号为%s的记录!\n", type_var);
            return NULL;
        case POLICE_ID:
            while (ticket != NULL) {
                if (strcmp(ticket->data.police_id, type_var) == 0) {
                    printf("查询成功，信息为: \n");
                    Print(ticket);
                    return ticket;
                }
                ticket = ticket->next;
            }
            printf("没有警号为%s的记录!\n", type_var);
            return NULL;
        case TICKET_ID:
            while (ticket != NULL) {
                if (strcmp(ticket->data.ticket_id, type_var) == 0) {
                    printf("查询成功，信息为: \n");
                    Print(ticket);
                    return ticket;
                }
                ticket = ticket->next;
            }
            printf("没有罚单单号为%s的记录!\n", type_var);
            return NULL;
            break;
    }
}

Ticket* searchPrev(Ticket* ticket, char* car_num) {
    Ticket* prev = ticket;
    while (prev->next != NULL) {
        if (strcmp(prev->next->data.car_num, car_num) == 0) {
            return prev;
        }
        prev = prev->next;
    }
    return NULL;
}

void Sort(Ticket* ticket) {
    if (ticket == NULL || ticket->next == NULL) {
        return;
    }
    Ticket* p = ticket->next;
    Ticket* pstart = (Ticket*) malloc(sizeof (Ticket));
    Ticket* pend = ticket;
    pstart->next = ticket;
    while (p != NULL) {
        Ticket* tmp = pstart->next, *pre = pstart;
        while(tmp != p && p->data.police_id >= tmp->data.police_id){
            tmp = tmp->next;
            pre = pre->next;
        }
        if(tmp == p) {
            pend = p;
        }else {
            pend->next = p->next;
            p->next = tmp;
            pre->next = p;
        }
            p = pend->next;
    }
    ticket = pstart->next;
    while (ticket->next != NULL) {
        Print(ticket->next);
        ticket->next = ticket->next->next;
    }
}

void Dealed(Ticket* ticket) {
    Ticket* head = ticket->next;
    while (head != NULL) {
        if (strcmp(head->data.punish_stat, UN_DEALED) == 0) {
            Print(head);
        }
        head = head->next;
    }
}

void Count_month(Ticket* head, char count[]) {
    char* time = head->data.punish_time;
    char month[3] = {};
    int tmp = 0;
    for (int i = 5; i < PUNISH_MAX; i++) {
        if (time[i] == '-') {
            break;
        }
        month[tmp++] = time[i];
    }
    if (strcmp(month, "1") == 0) {
        count[1]++;
    }else if (strcmp(month, "2") == 0) {
        count[2]++;
    }else if (strcmp(month, "3") == 0) {
        count[3]++;
    }else if (strcmp(month, "4") == 0) {
        count[4]++;
    }else if (strcmp(month, "5") == 0) {
        count[5]++;
    }else if (strcmp(month, "6") == 0) {
        count[6]++;
    }else if (strcmp(month, "7") == 0) {
        count[7]++;
    }else if (strcmp(month, "8") == 0) {
        count[8]++;
    }else if (strcmp(month, "9") == 0) {
        count[9]++;
    }else if (strcmp(month, "10") == 0) {
        count[10]++;
    }else if (strcmp(month, "11") == 0) {
        count[11]++;
    }else if (strcmp(month, "12") == 0) {
        count[12]++;
    }
}

void Count(Ticket* ticket) {
    Ticket* head = ticket->next;
    char count[10][13];
    while (head != NULL) {
        char *type = head->data.ticket_type;
        if (strcmp(type, DRINKING) == 0) {
            Count_month(head, count[0]);
        } else if (strcmp(type, DRUNK) == 0) {
            Count_month(head, count[1]);
        } else if (strcmp(type, JAYWALKING) == 0) {
            Count_month(head, count[2]);
        } else if (strcmp(type, REAR_END) == 0) {
            Count_month(head, count[3]);
        } else if (strcmp(type, PARKING) == 0) {
            Count_month(head, count[4]);
        } else if (strcmp(type, E_BUS_LINE) == 0) {
            Count_month(head, count[5]);
        } else if (strcmp(type, LIMIT_DRIVE) == 0) {
            Count_month(head, count[6]);
        } else if (strcmp(type, COVER_PLATE) == 0) {
            Count_month(head, count[7]);
        } else if (strcmp(type, NO_PLATE_DRIVE) == 0) {
            Count_month(head, count[8]);
        } else if (strcmp(type, NO_LISENCE_DRIVE) == 0) {
            Count_month(head, count[9]);
        }
        head = head->next;
    }

    for (int i = 0; i < 10; i++) {
        switch (i) {
            case 0:
                printf("这是%s的信息\n", DRINKING);
                break;
            case 1:
                printf("这是%s的信息\n", DRUNK);
                break;
            case 2:
                printf("这是%s的信息\n", JAYWALKING);
                break;
            case 3:
                printf("这是%s的信息\n", REAR_END);
                break;
            case 4:
                printf("这是%s的信息\n", PARKING);
                break;
            case 5:
                printf("这是%s的信息\n", E_BUS_LINE);
                break;
            case 6:
                printf("这是%s的信息\n", LIMIT_DRIVE);
                break;
            case 7:
                printf("这是%s的信息\n", COVER_PLATE);
                break;
            case 8:
                printf("这是%s的信息\n", NO_PLATE_DRIVE);
                break;
            case 9:
                printf("这是%s的信息\n", NO_LISENCE_DRIVE);
                break;
        }
        for (int j = 1; j < 13; i++) {
             printf("%d月有罚单%d次\n", j, count[i][j]);
        }
    }
}

void Print(Ticket* head) {
    printf("车牌号: %-20s\t\t驾驶证号: %-20s\n开单交警编号: %-20s\t处罚单号: %-20s\n",
           head->data.car_num, head->data.driver_id, head->data.police_id, head->data.ticket_id);
    printf("罚单类型: %-20s\t\t", head->data.ticket_type);
    printf("处罚时间: %-20s\n", head->data.punish_time);
    printf("处罚方式: %-20s\t\t", head->data.punish_type);
    printf("罚款金额: %.2lf\n", head->data.punish_money);
    printf("处理状态: %-20s\n", head->data.punish_stat);
    printf("----------------------------------------------------------------\n");
}