#include "ui_ErrorEditDialog.h"
#include "ErrorEditDialog.h"

#include <QTableWidgetItem>
#include <QStringList>
#include <QDebug>
#include <QBrush>
#include <QColor>
#include <QAbstractButton>
#include <QMessageBox>

std::vector<std::vector<int>> errorLocationList;
int locationNum;
int errorNum;

/*
 * Load data contained in the errors vector into a QWidgetTable
 * Fields will be marked red and editable if they are a mandatory field
 * and editable.  Otherwise all other fields will not be editable.
 * Clicking Save in the dialog will return the corrected entries to the main
 * program through the errors parameter.  If not all marked fields are edited
 * then a warning message will be displayed.  If cancel is clicked all errors
 * are discarded.
 */
ErrorEditDialog::ErrorEditDialog(QWidget *parent,
                                 std::vector<std::vector<std::string>*>& errors,
                                 std::vector<std::string>& headers,
                                 std::vector<std::string>& mandatory) :
    QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
    errorList(errors),
    headerList(headers),
    mandatoryList(mandatory),
    ui(new Ui::ErrorEditDialog)
{
    ui->setupUi(this);
    locationNum = 0;
    ui->tableWidget->setRowCount((int) errors.size());
    ui->tableWidget->setColumnCount((int) headers.size());

    QStringList listHeaders;
    for (int i = 0; i < (int) headers.size(); i++) {
        listHeaders << headers[i].c_str();
    }

    ui->tableWidget->setHorizontalHeaderLabels(listHeaders);
    QTableWidgetItem* item;
    QBrush brush(QColor(255, 0, 0, 100));
    std::vector<std::vector<std::string>*>::iterator it;
    int row = 0;
    for (it = errors.begin(); it != errors.end(); it++) {
        for (int col = 0; col < (int) headers.size() && col < (int) (*it)->size(); col++) {
            item = new QTableWidgetItem();
            item->setText((*it)->at(col).c_str());
            for (int i = 0; i < (int) mandatory.size(); i++) {
                if (mandatory[i].compare(headers.at(col)) == 0
                        && (*it)->at(col).compare("") == 0) {
                    std::vector<int> location;
                    location.push_back(row);
                    location.push_back(col);
                    errorLocationList.push_back(location);
                    item->setBackground(brush);
                }
            }
            ui->tableWidget->setItem(row, col, item);
        }
        row++;
    }
    errorNum = errorLocationList.size();
    modify_errorLabel();
    connect(ui->tableWidget,SIGNAL(cellChanged(int,int)),this,SLOT(modify_cell(int,int)),Qt::UniqueConnection);
}

//Clean up allocated memory for the table items
ErrorEditDialog::~ErrorEditDialog()
{
    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        for (int j = 0; j < ui->tableWidget->columnCount(); j++) {
            delete ui->tableWidget->item(i,j);
        }
    }
    delete ui;
}

//Save the new data entered by the user via the error reference var
void ErrorEditDialog::saveData() {
    for (int row = 0; row < ui->tableWidget->rowCount(); row++) {
        for (int col = 0; col < ui->tableWidget->columnCount() && col < (int) errorList[row]->size(); col++) {
            std::vector<std::string>::iterator it = errorList[row]->begin()+col;
            if (errorList[row]->at(col).compare("") == 0) {
                it = errorList[row]->erase(it);
                errorList[row]->insert(it, ui->tableWidget->item(row, col)->text().toStdString());
            }
        }
    }
    accept();
}

void ErrorEditDialog::on_save_clicked()
{
    bool search = true;
    //check if mandatory fields have been filled
    for (int row = 0; row < ui->tableWidget->rowCount() && search; row++) {
        for (int j = 0; j < (int) mandatoryList.size() && search; j++) {
            std::vector<std::string>::iterator it = std::find(headerList.begin(), headerList.end(), mandatoryList[j]);
            int col = it - headerList.begin();
            QTableWidgetItem* item = ui->tableWidget->item(row, col);
            if (item->text().compare("") == 0) {
                QMessageBox::critical(this, "Error", "Mandatory fields are still empty.");
                search = false;
            }
        }
    }
    if (search) {
        saveData();
    }
}

void ErrorEditDialog::on_cancel_clicked()
{
    reject();
}

void ErrorEditDialog::on_nextButton_clicked()
{
    locationNum++;
    if(locationNum>=errorLocationList.size()){
        locationNum = 0;
    }
    std::vector<int> location = errorLocationList.at(locationNum);
    ui->tableWidget->setCurrentCell(location.at(0), location.at(1));
    ui->tableWidget->setFocus();
}


void ErrorEditDialog::on_prevButton_clicked()
{
    locationNum--;
    if(locationNum<0){
        locationNum = errorLocationList.size() - 1;
    }
    std::vector<int> location = errorLocationList.at(locationNum);
    ui->tableWidget->setCurrentCell(location.at(0), location.at(1));
    ui->tableWidget->setFocus();
}

void ErrorEditDialog::modify_cell(int row, int col)
{
    QBrush brush(QColor(0, 0, 0, 0));
    std::vector<int> modifiedCell;
    modifiedCell.push_back(row);
    modifiedCell.push_back(col);
    int findCell = std::find(errorLocationList.begin(),errorLocationList.end(),modifiedCell) - errorLocationList.begin();
    if(findCell < errorLocationList.size()){
        errorLocationList.erase(errorLocationList.begin() + findCell);
        errorNum--;
        locationNum--;
        if(locationNum<0){
            locationNum = errorLocationList.size() - 1;
        }
        if(errorNum==0){
            ui->nextButton->setEnabled(false);
            ui->prevButton->setEnabled(false);
        }
        ui->tableWidget->item(row, col)->setBackground(brush);
        modify_errorLabel();
    }

}

void ErrorEditDialog::modify_errorLabel()
{
    ui->errorLabel->setText(QString::number(errorNum));
}
