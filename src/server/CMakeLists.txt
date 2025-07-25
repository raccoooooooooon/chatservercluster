#定义SRC_LIST包含该目录下所有源文件
aux_source_directory(. SRC_LIST)
#定义DB_LIST包含db目录下所有源文件
aux_source_directory(./db DB_LIST)
#定义MODEL_LIST包含model目录下所有源文件
aux_source_directory(./model MODEL_LIST)
#定义REDIS_LIST包含redis目录下所有源文件
aux_source_directory(./redis REDIS_LIST)

#指定生成可执行文件
add_executable(ChatServer ${SRC_LIST} ${DB_LIST} ${MODEL_LIST} ${REDIS_LIST})
#指定可执行文件链接时所依赖的库文件
target_link_libraries(ChatServer muduo_net muduo_base mysqlclient hiredis pthread)