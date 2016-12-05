#include <QtTest/QtTest>
#include <tests/TestSuite.h>
#include <./database/CSVReader.h>
#include <./gui/mainwindow.h>
#include <./database/RecordsManager.h>
#include <./gui/ErrorEditDialog.h>
#include <./gui/qcustomplot.h>
#include <QMessageBox>
#include <QPrintDialog>
#include <iostream>
#include <vector>
using namespace std;

// Tests to check if the correct files are loaded and headers are populated
// within the vector for headers
void TestSuite:: testHeaderCount() {
    CSVReader readerOne("./Sample Data/Teaching_sample.csv");
    QVERIFY(readerOne.getHeaders().size() == 28);

    CSVReader readerTwo("./Sample Data/Presentations_sample.csv");
    QVERIFY(readerTwo.getHeaders().size() == 30);

    CSVReader readerThree("./Sample Data/GrantsClinicalFunding_sample.csv");
    QVERIFY(readerThree.getHeaders().size() == 38);

    CSVReader readerFour("./Sample Data/Publications_sample.csv");
    QVERIFY(readerFour.getHeaders().size() == 44);

    CSVReader readerFive("./Sample Data/Program_Teaching_expanded.csv");
    QVERIFY(readerFive.getHeaders().size() == 27);

    CSVReader readerSix("./Sample Data/Presentations_expanded.csv");
    QVERIFY(readerSix.getHeaders().size() == 25);

    CSVReader readerSeven("./Sample Data/Grants_expanded.csv");
    QVERIFY(readerSeven.getHeaders().size() == 37);

    CSVReader readerEight("./Sample Data/Publications_expanded.csv");
    QVERIFY(readerEight.getHeaders().size() == 34);

    CSVReader readerNine("NO FILE");
    QVERIFY(readerNine.getHeaders().empty() == true);

    CSVReader readerTen("./Sample Data/Publications_expandedt.csv");
    QVERIFY(readerTen.getHeaders().size()  == 0);

    CSVReader myReader("./Sample Data/TestInput.csv");
    QVERIFY(myReader.getHeaders().size() == 4);
}

// Tests to make sure the exact headers are loaded
// as they're listed within the csv
void TestSuite:: testCorrectHeaderObject() {
    CSVReader myReader("./Sample Data/TestInput.csv");

    vector<string> myVector = {"Record Info", "B Group", "C Group", "D Group"};
    QVERIFY(myReader.getHeaders() == myVector);
}

// Tests to make sure the data vector corresponds to the right assignment
void TestSuite:: testGetData() {
    CSVReader readerOne("./Sample Data/Teaching_sample.csv");
    vector<vector <string>> allDataOne = readerOne.getData();
    QVERIFY(allDataOne.size() > 0);

    CSVReader readerTwo("./Sample Data/Presentations_sample.csv");
    vector<vector <string>> allDataTwo = readerTwo.getData();
    QVERIFY(allDataTwo.size() > 0);

    CSVReader readerThree("./Sample Data/GrantsClinicalFunding_sample.csv");
    vector<vector <string>> allDataThree = readerThree.getData();
    QVERIFY(allDataThree.size() > 0);

    CSVReader readerFour("./Sample Data/Publications_sample.csv");
    vector<vector <string>> allDataFour = readerFour.getData();
    QVERIFY(allDataFour.size() > 0);

    CSVReader myReader("./Sample Data/TestInput.csv");
    vector<vector <string>> myData = myReader.getData();
    QVERIFY(myData.empty() == false);

    vector<vector <string>> mockData = {{"1", "James Harden", "Houston", "MVP"},
                                        {"2", "LeBron James", "Cleveland", "Scrub"},
                                        {"3", "Steph Curry", "Golden State", "Fluke"}};
    QCOMPARE(myData, mockData);
}

// Tests to make sure the program launches and closes without any errors
void TestSuite:: testMainWindow() {
#ifdef _WIN32
    MainWindow *mainWindow = new MainWindow();

    QVERIFY(mainWindow);

    delete mainWindow;

#endif
}

// Test the number of headers within the Record Manager
void TestSuite:: testRecordsManagerHeaderCount() {
    CSVReader myReader("./Sample Data/TestInput.csv");
    vector<string> myHeaders = myReader.getHeaders();
    QVERIFY(myHeaders.size() == 4);
}

// Tests to see if a record can be found
void TestSuite:: testRecordsManagerFindRecord() {
    CSVReader myReader("./Sample Data/TestInput.csv");
    vector<string> myHeaders = myReader.getHeaders();

    RecordsManager recordsManager(&myHeaders);
    vector<vector <string>> myData = myReader.getData();

    recordsManager.addRecord(0, &myData[0]);
    recordsManager.addRecord(1, &myData[1]);
    recordsManager.addRecord(2, &myData[2]);

    vector<BasicRecord*> foundRecord = recordsManager.findRecord(0);

    QVERIFY(foundRecord.empty() == false);

    foundRecord = recordsManager.findRecord(100);

    QVERIFY(foundRecord.empty() == true);
}

// Test that the result of adding a record to the Record Manager will be updated
void TestSuite:: testRecordsManagerAddRecord() {
    CSVReader myReader("./Sample Data/TestInput.csv");
    vector<string> myHeaders = myReader.getHeaders();

    RecordsManager recordsManager(&myHeaders);
    vector<vector <string>> myData = myReader.getData();

    recordsManager.addRecord(0, &myData[0]);
    recordsManager.addRecord(1, &myData[1]);
    recordsManager.addRecord(2, &myData[2]);

    vector<string> mockRecord = {"4", "Klay Thompson", "Golden State", "Overrated"};

    vector<BasicRecord*> foundRecord = recordsManager.findRecord(4);

    QVERIFY(foundRecord.empty() == true);

    recordsManager.addRecord(4, &mockRecord);

    foundRecord = recordsManager.findRecord(4);

    QVERIFY(foundRecord.empty() == false);
}

void TestSuite:: testQCPScatterConstructors()
{
    //tests mPen in QCPScatterStyle to see if it is not defined
    QCPScatterStyle scattConstruct1;
    bool result = scattConstruct1.isPenDefined();
    QVERIFY(result == false);
    //checks if the Qpixmap constructor for QCPScatterStyle is defined
    QPixmap pixmap;
    QCPScatterStyle scattConstruct7(pixmap);
    bool result7 = scattConstruct7.isPenDefined();
    QVERIFY(result7 == true);
}
void TestSuite:: testDivisionsHeader()
{
    CSVReader readerOne("./New_Sample_Data/New_Program_Teaching_expanded.csv");
    QVERIFY(readerOne.getHeaders().size() == 19);

    CSVReader readerTwo("./New_Sample_Data/New_Presentations_expanded.csv");
    QVERIFY(readerTwo.getHeaders().size() == 17);

    CSVReader readerThree("./New_Sample_Data/New_Grants_expanded.csv");
    QVERIFY(readerThree.getHeaders().size() == 19);

    CSVReader readerFour("./New_Sample_Data/Publications_expanded.csv");
    QVERIFY(readerFour.getHeaders().size() == 17);

    CSVReader readerFive("NO FILE");
    QVERIFY(readerFive.getHeaders().empty() == true);

    CSVReader myReader("./Sample Data/TestInput.csv");
    QVERIFY(myReader.getHeaders().size() == 4);
}
