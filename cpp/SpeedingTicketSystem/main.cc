#pragma warning(disable:4996)

#include "Driver.h"
#include "Police.h"
#include "Tickets.h"
#include "System.h"
#include "src.h"

int main() {
    int option = 0;
    System sys;
    sys.InitSystem();
    do {
        Menu_1();
        std::cout << "请选择您要进入的渠道: ";
        std::cin >> option;
        switch (option) {
            case EXIT_1:
                std::cout << "欢迎下次使用交通处罚单管理系统，感谢您的使用" << std::endl;
                sleep(1);
                break;
            case ROOT:
                system("clear");
                load();
                if (CheckPasswd(sys)) {
                    int option1 = 0;
                    do {
                        Menu_2();
                        std::cout << "欢迎进入管理(ROOT)权限，请选择需要的功能: ";
                        std::cin >> option1;
                        switch (option1) {
                            case EXIT_2:
                                std::cout << "已退出管理(ROOT)权限!" << std::endl;
                                sleep(1);
                                break;
                            case ADD_POLICE:
                                AddPolice(sys);
                                break;
                            case DEL_POLICE:
                                DelPolice(sys);
                                break;
                            case MOD_POLICE:
                                ModPolice(sys);
                                break;
                            case DES_POLICE:
                                sys.PoliceShow();
                                break;
                            case PASSWD_SYS:
                                PasswdSys(sys);
                                break;
                            default:
                                std::cerr << "请输入正确的选项(0 ~ 5)!" << std::endl;
                                break;
                        } // end switch root
                    } while (option1); // end do while option 1
                }// end if
                break;
            case POLICE:
                break;
            case DRIVER:
                break;
            default:
                std::cerr << "请输入正确的选项(0 ~ 3)!" << std::endl;
                break;
        } // end switch
    } while(option);
    return 0;
}