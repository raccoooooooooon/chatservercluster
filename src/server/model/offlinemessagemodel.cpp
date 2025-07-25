#include "offlinemessagemodel.hpp"
#include "db/db.h"

// 存储用户离线消息
void offlineMsgModel::insert(int userid, const std::string& msg)
{
    MySQL mysql;
    if (!mysql.connect())
        return;

    string escapedMsg = MySQL::escapeString(msg, mysql.getConnection());

    char sql[2048] = {0};
    snprintf(sql, sizeof(sql), "INSERT INTO OfflineMessage (userid, message) VALUES (%d, %s)",
             userid, escapedMsg.c_str());

    mysql.update(sql);
}

// 删除用户离线消息
void offlineMsgModel::remove(int userid)
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "delete from OfflineMessage where userid=%d", userid);
    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }
}

// 查询用户离线消息
vector<string> offlineMsgModel::query(int userid)
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "SELECT message FROM OfflineMessage WHERE userid=%d", userid);
    vector<string> vec;
    MySQL mysql;
    if (mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            // 把userid所有离线消息放入vec中返回
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                vec.push_back(row[0]);
            }

            mysql_free_result(res);
            return vec;
        }
    }
    return vec;
} 