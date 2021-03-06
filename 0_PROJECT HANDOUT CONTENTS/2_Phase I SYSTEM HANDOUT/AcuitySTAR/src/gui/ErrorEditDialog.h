#ifndef ERROREDITDIALOG_H
#define ERROREDITDIALOG_H

#include <QDialog>
#include <vector>
#include <string>

class QAbstractButton;

namespace Ui {
    class ErrorEditDialog;
}

class ErrorEditDialog : public QDialog
{
    Q_OBJECT

public:
     ErrorEditDialog(QWidget *parent,
                     std::vector<std::vector<std::string>*>& errors,
                     std::vector<std::string>& headers,
                     std::vector<std::string>& mandatory);
    ~ErrorEditDialog();

private slots:
     void on_save_clicked();
     void on_cancel_clicked();
     void on_nextButton_clicked();
     void modify_errorLabel();
     void on_prevButton_clicked();
     void modify_cell(int row, int col);

private:
    std::vector<std::vector<std::string>*> errorList;
    std::vector<std::vector<int>> errorLocationList;
    int ErrorNum;
    std::vector<std::string> headerList;
    std::vector<std::string> mandatoryList;
    Ui::ErrorEditDialog *ui;

    void saveData();
};

#endif // ERROREDITDIALOG_H
