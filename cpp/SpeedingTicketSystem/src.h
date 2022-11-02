#ifndef SPEEDINGTICKETSYSTEM_SRC_H
#define SPEEDINGTICKETSYSTEM_SRC_H

#include <iostream>
//#include <Windows.h>
#include <unistd.h>
#include <cstring>

typedef enum MENU_1 {
    EXIT_1,
    ROOT,
    POLICE,
    DRIVER
}MENU_1;

typedef enum MENU_2 {
    EXIT_2,
    ADD_POLICE,
    DEL_POLICE,
    MOD_POLICE,
    DES_POLICE,
    PASSWD_SYS
}MENU_2;

typedef enum MP {
    NAME = 1,
    ID,
    PASSWD
}MP;

void Menu_1() {
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=\n");
    printf("|\t\t\t1.ROOT     2.POLICE\t\t\t|\n");
    printf("|                                       |\n");
    printf("|\t\t\t3.DRIVER   0.EXIT\t\t\t|\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=\n");
}

void Menu_2() {
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("|\t\t\t1.ADD_POLICE     2.DEL_POLICE\t\t\t|\n");
    printf("|                                       \t\t\t|\n");
    printf("|\t\t\t3.MOD_POLICE     4.DES_POLICE\t\t\t|\n");
    printf("|                                       \t\t\t|\n");
    printf("|\t\t\t5.PASSWD_SYS     0.EXIT      \t\t\t|\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=\n");
}

void Mp() {
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=\n");
    printf("|\t\t\t                   \t\t\t|\n");
    printf("|     1.NAME     2.ID     3.PASSWD      |\n");
    printf("|\t\t\t                   \t\t\t|\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=\n");
}

#define NUM 101
#define SLEEP_TIME 20000
void load() {
    printf("正在加载中...\n");
    char lable[4] = { '-', '\\', '|', '/' };
    char bar[NUM] = {};
    memset(bar, '\0', NUM);
    int count = 0;
    while (count < 100) {
        //fflush(stdout);
        setbuf(stdout, nullptr);
        bar[count++] = '*';
        usleep(SLEEP_TIME);
        printf("[%-100s][%3d%%][%c]\r", bar, count, lable[count % 4]);
    }
    printf("加载完毕!\n");
    sleep(1);
}

template <class T>
bool CheckPasswd(T& pswd) {
    std::string passwd;
    std::cout << "请输入您的密码: ";
    std::cin >> passwd;
    if (pswd.CheckSysPasswd(passwd)) {
        std::cout << "密码正确，欢迎您的使用" << std::endl;
        return true;
    }else {
        std::cerr << "密码错误，请重新输入" << std::endl;
        sleep(1);
        return false;
    }
}

void AddPolice(System& sys) {
    std::string name;
    std::string id;
    std::string pswd;
    std::cout << "请输入警官的姓名: ";
    std::cin >> name;
    std::cout << "请输入警官的警号: ";
    std::cin >> id;
    std::cout << "请输入登陆的密码: ";
    std::cin >> pswd;

    if (sys.PoliceInsert(name, id, pswd)) {
        std::cout << "添加成功，警号为: " << id << std::endl;
    }else {
        std::cerr << "添加失败，警号为: " << id << std::endl;
    }
}

void DelPolice(System& sys) {
    std::string id;
    std::cout << "请输入您要删除警官的警号: ";
    std::cin >> id;
    if (sys.PoliceErase(id)) {
        std::cout << "删除成功，警号为: " << id << std::endl;
    }else {
        std::cerr << "删除失败，警号为: " << id << std::endl;
    }
}

void ModPolice(System& sys) {
    std::string name;
    std::string id;
    std::string pswd;
    std::cout << "请输入您想要修改警官的警号: ";
    std::cin >> id;

    auto pos = sys.PolicePos(id);
    int option = 0;
    Mp();
    std::cout << "请选择需要更改的选项: ";
    std::cin >> option;
    switch (option) {
        case NAME:
            std::cout << "请输入您想更改的名字: ";
            std::cin >> name;
            if (sys.PoliceModify(pos, name, "", "")) {
                std::cout << "修改成功！" << std::endl;
            }
            break;
        case ID:
            std::cout << "请输入您想更改的警号: ";
            std::cin >> id;
            if (sys.PoliceModify(pos, "", id, "")) {
                std::cout << "修改成功！" << std::endl;
            }
            break;
        case PASSWD:
            std::cout << "请输入您想更改的密码: ";
            std::cin >> pswd;
            if (sys.PoliceModify(pos, "", "", pswd)) {
                std::cout << "修改成功！" << std::endl;
            }
            break;
        default:
            std::cerr << "请输入正确的选项(1 ~ 3)!" << std::endl;
            break;
    }
}

void PasswdSys(System& sys) {
    std::string pswd;
    std::cout << "请输入您要修改的密码";
    std::cin >> pswd;
    sys.PasswdSys(pswd);
}

#endif //SPEEDINGTICKETSYSTEM_SRC_H
