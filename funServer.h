#ifndef FUNSERVER_H
#define FUNSERVER_H

#include <QByteArray>
#include <stack>
#include <string>

QByteArray parsing(QByteArray str);
QByteArray auth(std::string login, std::string pass);
QByteArray reg(std::string sname, std::string name, std::string lname, std::string log, std::string pas, std::string email, std::string group);

#endif // FUNSERVER_H
