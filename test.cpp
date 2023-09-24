#include <QtTest/QtTest>
#include "funServer.h"

class test : public QObject {
    Q_OBJECT

private slots:
    void testParsing();
    void testAuth();
    void testReg();
};

void test::testParsing() {
    QByteArray input("Auth username password");
    QByteArray result = parsing(input);
    QCOMPARE(result, QByteArray("authResult"));
}

void test::testAuth() {
    QByteArray result = auth("username", "password");
    QCOMPARE(result, QByteArray("authResult"));
}

void test::testReg() {
    QByteArray result = reg("surname", "name", "lastname", "login", "password", "email", "group");
    QCOMPARE(result, QByteArray("regResult"));
}

//QTEST_MAIN(test)
#include "test.moc"
