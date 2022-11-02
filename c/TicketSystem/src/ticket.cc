#include "../include/ticket.h"
#include "../include/Util.h"

Ticket* init() {
    Ticket* ticket = (Ticket*) malloc(sizeof(Ticket));
    ticket->next = NULL;
    FILE* fp = fopen(PATH_TICKET, "r");
    if (fp != NULL) {
        while (!feof(fp)) {
            Ticket* temp = (Ticket*) malloc(sizeof (Ticket));
            fscanf(fp, "%s", temp->data.car_num);
            fscanf(fp, "%s", temp->data.driver_id);
            fscanf(fp, "%s", temp->data.police_id);
            fscanf(fp, "%s", temp->data.ticket_id);
            fscanf(fp, "%s", temp->data.ticket_type);
            fscanf(fp, "%s", temp->data.punish_time);
            fscanf(fp, "%s", temp->data.punish_type);
            fscanf(fp, "%lf", &temp->data.punish_money);
            fscanf(fp, "%s", temp->data.punish_stat);
            temp->next = ticket->next;
            ticket->next = temp;
        }
        fclose(fp);
    }else {
        perror("FILE TICKET OPEN ERROR!");
    }
    return ticket;
}

bool insert(Ticket** pTicket) {
    char option = 0;
    Ticket* tail, *node;
    FILE* fp;
    do {
        while (getchar() != '\n');
        printf("您是否想要进行插入(Y/N): ");
        scanf("%c", &option);
        switch (option) {
            case 'y':
            case 'Y':
                tail = *pTicket;
                while (tail->next != NULL) {
                    tail = tail->next;
                }
                tail->next = (Ticket *) malloc(sizeof(Ticket));
                node = tail->next;
                node->next = NULL;
                Info(node);
                fp = fopen(PATH_TICKET, "a+");
                if (fp != NULL) {
                    fprintf(fp, "%s %s %s %s %s %s %s %.2lf %s\n",
                            node->data.car_num, node->data.driver_id, node->data.police_id,
                            node->data.ticket_id, node->data.ticket_type, node->data.punish_time,
                            node->data.punish_type, node->data.punish_money, node->data.punish_stat);
                    fclose(fp);
                    return true;
                } else {
                    perror("FILE TICKET OPEN ERROR!");
                    return false;
                }
            case 'n':
            case 'N':
                printf("已结束插入!\n");
                option = 0;
                break;
            default:
                break;
        }
    } while (option);
}

bool modify(Ticket** pTicket) {
    Ticket* temp, *head = *pTicket;
    int option = 0, type = 0;
    printf("在修改之前，您需要对需要修改的数据进行查询！\n");
    if ((temp = search(head)) != NULL) {
        while (getchar() != '\n');
        Menu_Modify();
        printf("进入修改系统，请选择您要修改的选项: ");
        scanf("%d", &option);
        switch (option) {
            case TICKET_TYPE:
                Menu_Ticket_Type();
                printf("请输入新的罚单类型: ");
                scanf("%d", &type);
                TicketType(type, temp->data.ticket_type);
                break;
            case PUNISH_TYPE:
                Menu_Punish_Type();
                printf("请输入新的处罚类型: ");
                scanf("%d", &type);
                PunishType(type, temp->data.punish_type);
                break;
            case PUNISH_MONEY:
                printf("请输入新的处罚金额: ");
                scanf("%lf", &temp->data.punish_money);
                break;
            case PUNISH_STAT:
                Menu_Punish_Stat();
                printf("请输入新的处罚状态: ");
                scanf("%d", &type);
                PunishStat(type, temp->data.punish_stat);
                break;
            default:
                printf("您的输入有误!\n");
                break;
        }
        FILE* fp = fopen(PATH_TICKET, "w+");
        if (fp != NULL) {
            while (head->next != NULL) {
                fprintf(fp, "%s %s %s %s %s %s %s %.2lf %s\n",
                        head->next->data.car_num, head->next->data.driver_id, head->next->data.police_id,
                        head->next->data.ticket_id, head->next->data.ticket_type, head->next->data.punish_time,
                        head->next->data.punish_type, head->next->data.punish_money, head->next->data.punish_stat);
                head = head->next;
            }
            fclose(fp);
        }else {
            perror("FILE TICKET OPEN ERROR!\n");
        }
    }else {
        printf("查询结果为空，修改失败!\n");
    }
    return false;
}

bool erase(Ticket** pTicket) {
    char option = 0;
    char car_num[SIZE_MAX] = {};
    FILE* fp;
    Ticket* prev, *next;
    do {
        while (getchar() != '\n');
        printf("您是否要进行删除(Y/N): ");
        scanf("%c", &option);
        switch (option) {
            case 'y':
            case 'Y':
                printf("请输入您想要删除信息的车牌号: ");
                scanf("%s", car_num);
                prev = searchPrev(*pTicket, car_num);
                if (prev == NULL) {
                    printf("插入失败\n");
                    return false;
                }
                next = prev->next;
                prev->next = next->next;
                fp = fopen(PATH_TICKET, "w+");
                if (fp != NULL) {
                    prev = *pTicket;
                    while (prev->next != NULL) {
                        fprintf(fp, "%s %s %s %s %s %s %s %.2lf %s\n",
                                prev->next->data.car_num, prev->next->data.driver_id, prev->next->data.police_id,
                                prev->next->data.ticket_id, prev->next->data.ticket_type, prev->next->data.punish_time,
                                prev->next->data.punish_type, prev->next->data.punish_money, prev->next->data.punish_stat);
                        prev = prev->next;
                    }
                    printf("插入成功!\n");
                    fclose(fp);
                }else {
                    perror("FILE TICKET OPEN ERROR!\n");
                }
                break;
            case 'n':
            case 'N':
                printf("已退出!\n");
                option = 0;
                break;
            default:
                printf("");
                break;
        }
    } while (option);
    return true;
}

Ticket* search(Ticket* ticket) {
    int option = 0; char option1 = 0;
    char id[SIZE_MAX] = {};
    Ticket* ref;
    do {
        while (getchar() != '\n');
        printf("您是否想要进行查询(Y/N): ");
        scanf("%c", &option1);
        switch (option1) {
            case 'y':
            case 'Y':
                do {
                    Menu_Search();
                    printf("请选择您需要查询的方式: ");
                    scanf("%d", &option);
                    switch (option) {
                        case CAR_ID:
                            printf("请输入您要查询的车牌号: ");
                            scanf("%s", id);
                            ref = SearchType(ticket, id, option);
                            break;
                        case DRIVER_ID:
                            ref = SearchType(ticket, id, option);
                            break;
                        case POLICE_ID:
                            ref = SearchType(ticket, id, option);
                            break;
                        case TICKET_ID:
                            ref = SearchType(ticket, id, option);
                            break;
                        case EXIT_ALL:
                            break;
                        default:
                            printf("您输入的选项有误!\n");
                            break;
                    }
                } while (option);
            case 'n':
            case 'N':
                printf("已退出查询!\n");
                option1 = 0;
                break;
            default:
                printf("您的输入有误!\n");
                break;
        }
    } while (option1);
    return ref;
}

void show(Ticket* ticket) {
    int option = 0;
    Ticket* head;
    do {
        Menu_Show();
        printf("请输入您的需求: ");
        scanf("%d", &option);
        switch (option) {
            case SHOW_SHOW:
                head = ticket->next;
                if (head == NULL) {
                    printf("目前系统内没有数据,请先添加数据!\n");
                }
                while (head != NULL) {
                    Print(head);
                    head = head->next;
                }
                break;
            case SHOW_SORT:
                Sort(ticket);
                break;
            case SHOW_DEALED:
                Dealed(ticket);
                break;
            case COUNT_BY_YEAR:
                Count(ticket);
                break;
            default:
                printf("您的输入有误!\n");
                break;
        }
    } while (option);

}