# chatservercluster
集群聊天服务器及命令行客户端源码，基于Muduo网络库实现，通过Nginx代理TCP请求实现服务器集群，通过Redis发布-订阅机制将Redis作为消息中间件实现跨服务器通信

编译方式
cd build
rm -rf *
cmake ..
make

确保Nginx包含stream模块以支持TCP代理，并在配置文件中定义TCP后端服务器组与TCP监听服务，指定负载均衡算法

本项目Redis封装类使用无密码连接，如需支持带密码访问，请自行修改
