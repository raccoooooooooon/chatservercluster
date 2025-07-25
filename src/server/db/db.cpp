#include "db/db.h"

#include <muduo/base/Logging.h>
using namespace muduo;

// 数据库配置信息
static string server = "192.168.137.128";
static string user = "root";
static string password = "qazplm@12589";
static string dbname = "chat";

// 初始化数据库连接
MySQL::MySQL()
{
    _conn = mysql_init(nullptr);
}
MySQL::~MySQL()
{
    if (_conn != nullptr)
        mysql_close(_conn);
}
// 连接数据库
bool MySQL::connect()
{
    MYSQL *p = mysql_real_connect(_conn, server.c_str(), user.c_str(),
                                  password.c_str(), dbname.c_str(), 3306, nullptr, 0);
    if (p != nullptr)
    {
        // c和c++默认字符编码为ASCII，若不设置编码格式，从MySQL上拉取中文会显示？
        mysql_query(_conn, "set names utf8mb4");
        LOG_INFO << "connect mysql success!";
    }
    else
    {
        LOG_INFO << "connect mysql fail! Error: " << mysql_error(_conn);
    }
    return p;
}
// 更新操作
bool MySQL::update(string sql)
{
    if (mysql_query(_conn, sql.c_str()))
    {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":"
                 << sql << "更新失败！";
        return false;
    }
    return true;
}
// 查询操作
MYSQL_RES *MySQL::query(string sql)
{
    if (mysql_query(_conn, sql.c_str()))
    {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":"
                 << sql << "查询失败！";
        return nullptr;
    }
    return mysql_use_result(_conn);
}
// 获取连接
MYSQL *MySQL::getConnection()
{
    return _conn;
}

string MySQL::escapeString(const std::string &input, MYSQL *conn)
{
    if (input.empty())
        return "''";

    char *buffer = new char[input.size() * 2 + 1];
    unsigned long len = mysql_real_escape_string(conn, buffer, input.c_str(), input.size());

    std::string escaped(buffer, len);
    delete[] buffer;

    return "'" + escaped + "'";
}