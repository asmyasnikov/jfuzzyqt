#ifndef CALCULATIONDIALOG_H
#define CALCULATIONDIALOG_H

#include <QtGui/QDialog>
#include <../../include/jfuzzyqt.h>

namespace Ui
{
    class CalculationDialogClass;
}

class CalculationDialog : public QDialog
{
    Q_OBJECT

public:
    CalculationDialog(QWidget *parent = 0);
    ~CalculationDialog();
public slots:
    void initFuzzyModel(QString fileUri);
    void changeInputData();
    void evaluate();

private:
    Ui::CalculationDialogClass *ui;
    jfuzzyqt::JFuzzyQt *model;
};

#endif // CALCULATIONDIALOG_H
