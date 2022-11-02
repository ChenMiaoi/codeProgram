#ifndef SPEEDINGTICKETSSYSTEM_POLICE_H
#define SPEEDINGTICKETSSYSTEM_POLICE_H

#include <iostream>
#include <string>

class Police {
    friend std::ostream& operator<< (std::ostream& _out, const Police& police);
public:
    Police(std::string police_name, std::string police_num, std::string police_passwd)
        : _police_name(police_name)
        , _police_num(police_num)
        , _police_passwd(police_passwd)
    {}

public:
    std::string GetNum() const {
        return this->_police_num;
    }

    std::string GetName() const {
        return this->_police_name;
    }

    std::string GetPasswd() const {
        return this->_police_passwd;
    }

    void SetName(const std::string name) {
        _police_name = name;
    }

    void SetNum(const std::string id) {
        _police_num = id;
    }

    void SetPswd(const std::string pswd) {
        _police_passwd = pswd;
    }

    bool CheckSysPasswd(const std::string passwd) {
        return this->_police_passwd == passwd;
    }
private:
    std::string _police_name;
    std::string _police_num;
    std::string _police_passwd;
};

std::ostream & operator<< (std::ostream& _out, const Police& police){
    _out << "警察姓名：" << police._police_name << " 警号：" << police._police_num << " 登陆密码：" << police._police_passwd;
    return _out;
}

#endif // !SPEEDINGTICKETSSYSTEM_POLICE_H
