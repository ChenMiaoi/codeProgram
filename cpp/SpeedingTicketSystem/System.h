#ifndef SPEEDINGTICKETSYSTEM_SYSTEM_H
#define SPEEDINGTICKETSYSTEM_SYSTEM_H

#include "Driver.h"
#include "Tickets.h"
#include "Police.h"
#include <vector>
#include <fstream>

#define POLICE_INIT_NUM 100
#define DRIVER_INIT_NUM 10000
#define TICKETS_INIT_NUM 10000
#define PATH "/home/zack/code_work/github_work/My_Cpp_Programming/SpeedingTicketSystem/PoliceData.txt"

class System {
public:
    System(std::vector<Police> police = {}, std::vector<Driver> driver = {}, std::vector<Tickets> tickets = {})
        : _police(police)
        , _driver(driver)
        , _tickets(tickets)
    {
        _police.reserve(POLICE_INIT_NUM);
        _driver.reserve(DRIVER_INIT_NUM);
        _tickets.reserve(TICKETS_INIT_NUM);
    }

public:
    bool InitSystem() {
        std::string police_name;
        std::string police_num;
        std::string police_passwd;
        std::ifstream ifs;
        //ofs.open("D:\\ClionProgram\\SpeedingTicketSystem\\PoliceData.txt", std::ios::out);
        ifs.open(PATH, std::ios::in);
        if (ifs.is_open()) {
            while (!ifs.eof()) {
                ifs >> police_name >> police_num >> police_passwd;
                _police.emplace_back(Police(police_name, police_num, police_passwd));
            }
        }else {
            std::cerr << "InitSystem error!" << std::endl;
            return false;
        }
        ifs.close();
        return true;
    }

    bool CheckSysPasswd(const std::string passwd) {
        return this->_sys_passwd == passwd;
    }

    bool PoliceInsert(const std::string police_name, const std::string police_num, const std::string police_passwd) {
        if (!CheckPoliceId(police_num)) {
            _police.emplace_back(Police(police_name, police_num, police_passwd));
        }else {
            std::cout << "police id is primary key!" << std::endl;
            return false;
        }

        std::ofstream ofs;
        //ofs.open("D:\\ClionProgram\\SpeedingTicketSystem\\PoliceData.txt", std::ios::out);
        ofs.open(PATH, std::ios::out | std::ios::app);
        if (ofs.is_open()) {
            ofs << police_name << " " << police_num << " " << police_passwd;
        }else {
            std::cerr << "PoliceInsert PoliceData.txt open error!" << std::endl;
            return false;
        }
        ofs.close();

        //_police_count++;
        return true;
    }

    bool PoliceErase(const std::string police_num) {
        if (_police.empty()) {
            perror("police queue is empty, can't do Erase!\n");
            return false;
        }

        bool flag = true;
        for (auto item = _police.begin(); item != _police.end(); item++) {
            if (police_num == item->GetNum()) {
                item = _police.erase(item);

                std::ofstream ofs;
                //ofs.open("D:\\ClionProgram\\SpeedingTicketSystem\\PoliceData.txt", std::ios::out);
                ofs.open(PATH, std::ios::out);
                if (ofs.is_open()) {
                    for (auto it = _police.begin(); it != _police.end(); it++) {
                        ofs << it->GetName() << " " << it->GetNum() << " " << it->GetPasswd() << "\n";
                    }
                }else {
                    std::cerr << "PoliceErase PoliceData.txt open error!" << std::endl;
                    return false;
                }
                ofs.close();
                flag = false;
            }
        }
        if (flag) {
            std::cout << "PoliceErase error: can't find police id!" << std::endl;
            return false;
        }
        //_police_count--;
        return true;
    }

    bool PoliceModify(int pos, const std::string police_name, const std::string police_num, const std::string police_pswd) {
        if (police_pswd == "" && police_num == "" && police_name != "") {
            _police[pos].SetName(police_name);
            return true;
        }else if (police_pswd == "" && police_name == "" && police_num != "") {
            _police[pos].SetNum(police_num);
            return true;
        }else if (police_name == "" && police_num == "" && police_pswd != "") {
            _police[pos].SetPswd(police_pswd);
            return true;
        }
        return false;
    }

    auto PolicePos(const std::string police_num) {
        for (auto i = 0; i < _police.size(); i++) {
            if (_police[i].GetNum() == police_num) {
                return i;
            }
        }
        std::cerr << "PolicePos: can't find id!" << std::endl;
    }

    void PoliceShow() const {
        for(auto e : _police) {
            std::cout << e << std::endl;
        }
#if 0
        std::ifstream ifs;
        ifs.open(PATH, std::ios::in);
        if (ifs.is_open()) {
            std::string buffer = "";
            while (!ifs.eof()) {
                ifs >> buffer;
                std::cout << buffer;
            }
        }else {
            std::cerr << "PoliceShow PoliceData.txt open error!" << std::endl;
            exit(3);
        }
#endif
    }

    bool PasswdSys(const std::string pswd) {
        if (_sys_passwd == pswd) {
            std::cerr << "不能与原密码一致" << std::endl;
            return false;
        }else {
            _sys_passwd = pswd;
            return true;
        }
    }
private:
    bool CheckPoliceId(std::string id) const {
        for (auto const e : _police) {
            if (e.GetNum() == id) {
                return true;
            }
        }
        return false;
    }
private:
    //size_t _police_count;
    //size_t _driver_count;
    //size_t _ticket_count;
    std::string _sys_passwd = "123456";
    std::vector<Police> _police;
    std::vector<Driver> _driver;
    std::vector<Tickets> _tickets;
};

#endif //SPEEDINGTICKETSYSTEM_SYSTEM_H
