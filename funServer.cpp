#include "funServer.h"
#include "database.h"

#include <QString>
#include <QDebug>

#include <iostream>

QByteArray parsing(QByteArray str)
{
    std::string mystr = str.trimmed().toStdString().substr(0,str.toStdString().find(" "));

    if (mystr == "Auth") {
        mystr = str.toStdString().substr(str.toStdString().find(" ")+1, -1);

        QStringList str_list = (QString(str)).split(" ");
        std::string log = str_list[1].toStdString();
        std::string pas = str_list[2].toStdString();

        return auth(log,pas);
    }
    else if (mystr == "Reg") {
        mystr = str.toStdString().substr(str.toStdString().find(" ")+1, -1);
        QStringList str_list = (QString(str)).split(" ");

        std::string surname = str_list[1].toStdString();
        std::string name = str_list[2].toStdString();
        std::string lastname = str_list[3].toStdString();
        std::string login = str_list[4].toStdString();
        std::string password = str_list[5].toStdString();
        std::string email = str_list[6].toStdString();
        std::string group = str_list[7].toStdString();

        return reg(surname, name, lastname, login, password, email, group);
    }
    return "";
}

QByteArray auth(std::string login, std::string pass)
{
    QString res = SingletonDataBase::getInstance()->queryToDB(QString::fromStdString("SELECT * FROM users  where user_login = \"" + login + "\""));
    QString name = SingletonDataBase::getInstance()->queryToDB(QString::fromStdString("SELECT user_name FROM users  where user_login = \"" + login + "\""));
    QString surname = SingletonDataBase::getInstance()->queryToDB(QString::fromStdString("SELECT user_surname FROM users  where user_login = \"" + login + "\""));
    qDebug()<<res;

    if (res!="")
        return QString::fromStdString((std::string)"auth+" + (login) + (std::string)"\r\n").toUtf8();
    else
        return "auth-\r\n";
}

QByteArray reg(std::string sname, std::string name, std::string lname, std::string log, std::string pas, std::string email, std::string group)
{
    std::string note_id = (SingletonDataBase::getInstance()->queryToDB(QString::fromStdString("SELECT note_id+1 FROM users ORDER BY note_id DESC LIMIT 1;"))).toStdString();
    note_id = note_id.substr(1,note_id.length()-2);
    SingletonDataBase::getInstance()->queryToDB(QString::fromStdString(
        "INSERT INTO "
        "users(note_id,user_socket,user_login,user_password,user_email,user_surname,user_name,user_patronymic,user_group,task_1,task_2,task_3)"
        "VALUES"
        "("+note_id+",0,'"+log+"','"+pas+"','"+email+"','"+sname+"','"+name+"','"+lname+"','"+group+"',0,0,0);"));

    QString res = SingletonDataBase::getInstance()->queryToDB(QString::fromStdString("SELECT * FROM users where user_login = '"+log+"';"));
    qDebug()<<"Registration completed"<<res;

    QString res_auth = QString::fromUtf8(auth(log,pas));
    if(res_auth.left(5)=="auth+")
        return res_auth.toUtf8();

    return QString::fromStdString((std::string)"reg-"+(log) + (std::string)"\r\n").toUtf8();
}
