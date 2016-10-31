#include <iostream>
#include <stdio.h>
#include <QApplication>
#include <QTreeView>
#include <QtTest/QtTest>
#include <tests/TestQString.h>
#include <tests/TestSuite.h>

#include "gui/mainwindow.h"
#include "database/TestCSVReader.h"
using namespace std;

int main(int argc, char *argv[]) {
    int test = 1;   /* test off */

    if (test) {
        TestQString *test_obj = new TestQString();
        QTest::qExec(test_obj);
        TestSuite *test_suite= new TestSuite();
        QTest::qExec(test_suite);
    }

    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    return 0;
}
