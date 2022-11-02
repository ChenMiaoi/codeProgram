#include <iostream>
#include <string>
#include "../src/Util.hpp"
#include "../../mysqldb/include/mysql.h"

bool Insert(const std::string& sql) {
    MYSQL* conn = mysql_init(nullptr);
    mysql_set_character_set(conn, "utf8");
    if (mysql_real_connect(conn, "127.0.0.1", "http_client", "302606-00", "http_test", 3306, nullptr, 0) == nullptr) {
        LOG(FATAL, "Connect Error!");
        return false;
    }
    LOG(INFO, "Connect Success!");
    int ret = mysql_query(conn, sql.c_str());
    LOG(INFO, "result: " + std::to_string(ret));
    mysql_close(conn);
    return true;
}

void InsertSql(std::string& sql, std::unordered_map<std::string, std::string> url) {
    sql += url["name"];
    sql += "\", \"";
    sql += url["email"];
    sql += "\", \"";
    sql += url["phone"];
    sql += "\", \"";
    sql += url["subject"];
    sql += "\", \"";
    sql += url["message"];
    sql += "\")";
}

/*
 * name=test&email=test%40test.com&phone=123456&subject=test&message=test
 *
 * insert into contact (name, email, phone, subject, msg)
    values ("test", "test@test.com", "123456", "test subject", "test msg");
 * */
int main(){
    std::string query_string;
    if (Util::GetQueryString(query_string)) {
        //std::cout << "DeBug: " << query_string << std::endl;
        std::cerr << "DeBug: " << query_string << std::endl;
        std::unordered_map<std::string, std::string> url_param;
        Util::GetUrl(query_string, url_param);
        //for (auto e : url_param) std::cerr << "DeBug: " << e.first << " : " << e.second << "\n";
        std::string sql = "insert into contact (name, email, phone, subject, msg) values (\"";
        InsertSql(sql, url_param);
        std::cerr << sql << "\n";
        if (Insert(sql)) {
            LOG(INFO, "Insert Success!");
        }else {
            LOG(ERROR, "Insert Error!");
            return 1;
        }
    }
    return 0;
}