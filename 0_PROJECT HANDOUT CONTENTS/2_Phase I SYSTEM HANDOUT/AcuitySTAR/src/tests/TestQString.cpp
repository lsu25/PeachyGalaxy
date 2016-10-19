#include <QtTest/QtTest>
#include <tests/TestQString.h>

void TestQString::toUpper()
{
    QString str = "Hello";
    QVERIFY(str.toUpper() == "HELLO");
}
