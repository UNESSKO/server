#include <QCoreApplication>
#include "mytcpserver.h"
//#include "test.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

   // test ts;

    MyTcpServer server;

    return a.exec();
}
