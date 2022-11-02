#include "./include/Util.h"
#include "./include/ticket.h"
#include <sys/stat.h>

int main() {
    int option1 = 0, option2 = 0;
    char option3 = 0;
    char passwd[PASSWD_MAX] = {};
    Ticket* ticket = init();
    do {
        Menu_ALL();
        printf("请选择您要进入的渠道: ");
        scanf("%d", &option1);
        switch (option1) {
            case ROOT:
                if (ModifyPasswd()) {
                    printf("密码修改成功!请牢记您的密码!\n");
                }else {
                    printf("密码修改失败!\n");
                }
                break;
            case POLICE:
                printf("请输入密码: ");
                while (getchar() != '\n');
                scanf("%s", passwd);
                if (IsPasswd(passwd)) {
                    do {
                        Menu_Police();
                        printf("请选择您需要的操作: ");
                        fflush(stdout);
                        scanf("%d", &option2);
                        switch (option2) {
                            case INSERT:
                                insert(&ticket);
                                break;
                            case MODIFY:
                                modify(&ticket);
                                break;
                            case DELETE:
                                erase(&ticket);
                                break;
                            case SEARCH:
                                search(ticket);
                                break;
                            case SHOW:
                                show(ticket);
                                break;
                            case EXIT_POLICE:
                                break;
                            default:
                                break;
                        }
                    } while (option2);
                }// end if
                break;
            case DRIVER:
                do {
                    printf("(DRIVER)您是否需要进行查询(Y/N): ");
                    while (getchar() != '\n');
                    scanf("%c", &option3);
                    switch (option3) {
                        case 'y':
                        case 'Y':
                            search(ticket);
                            break;
                        case 'n':
                        case 'N':
                            printf("已退出系统!\n");
                            option3 = 0;
                            break;
                        default:
                            printf("您的输入有误!\n");
                            break;
                    }
                } while (option3);
                break;
            case EXIT_ALL:
                break;
            default:
                break;
        }
    } while (option1);
    return 0;
}
