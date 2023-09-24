#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QtTest/QtTest>

class test : public QObject {
    Q_OBJECT

private slots:
    void testParsing();
    void testAuth();
    void testReg();
};

#endif // TEST_H
