#include "chatserver.hpp"
#include "chatservice.hpp"
#include "json.hpp"

#include <string>
#include <functional>
using namespace std;
using namespace placeholders;
using json = nlohmann::json;

// 初始化聊天服务器对象
ChatServer::ChatServer(net::EventLoop *loop,
                       const net::InetAddress &listenAddr,
                       const string &nameArg)
    : _server(loop, listenAddr, nameArg), _loop(loop)
{
    // 注册链接回调
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));

    // 注册消息回调
    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

    // 设置线程数量
    _server.setThreadNum(4);
}

void ChatServer::start()
{
    _server.start();
}

// 上报链接相关信息的回调函数
void ChatServer::onConnection(const net::TcpConnectionPtr &conn)
{
    //客户端断开链接
    if(!conn->connected())
    {

        ChatService::instance()->clientCloseException(conn);
        conn->shutdown();
    }
}
// 上报读写事件相关信息的回调函数
void ChatServer::onMessage(const net::TcpConnectionPtr &conn,
                           net::Buffer *buffer,
                           Timestamp time)
{
    string buf = buffer->retrieveAllAsString();
    //数据的反序列化
    json js = json::parse(buf);
    //通过js["msgid"]获取一个业务处理器handler，将conn、js、time传给handler
    //从而实现对网络模块和业务模块的解耦
    auto msghandler = ChatService::instance()->getHandler(js["msgid"].get<int>());
    //回调消息所绑定事件处理器，以执行相应业务处理
    msghandler(conn, js, time);
}