#ifndef GROUPUSER_H
#define GROUPUSER_H

#include "user.hpp"

//GroupUser表的ORM类
//群组用户，相较于User，除与群组业务无关的password外，
//还多了一个role角色信息， 从User类继承，复用User的其他信息
class GroupUser : public User
{
public:
    void setRole(string role) {this->role = role;}
    string getRole() {return this->role;}
private:
    string role;
};

#endif