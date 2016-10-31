#ifndef TESTCSVREADER_H
#define TESTCSVREADER_H
#include <QtTest/QtTest>

class TestSuite: public QObject {
    Q_OBJECT
private slots:
    void testHeaderCount();
    void testGetData();
    void testMainWindow();
    void testCorrectHeaderObject();
    void testRecordsManagerHeaderCount();
    void testRecordsManagerFindRecord();
    void testRecordsManagerAddRecord();
};

#endif // TESTCSVREADER_H
