#include "calculationdialog.h"
#include "ui_calculationdialog.h"
#include <QtGui/QMessageBox>
#include <QtGui/QDoubleSpinBox>
#include <QtCore/QDir>

CalculationDialog::CalculationDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::CalculationDialogClass),
      model(NULL)
{
    ui->setupUi(this);
    QStringList headers;
    headers.append(trUtf8("Variable"));
    headers.append(trUtf8("Value"));
    ui->tbl_inputs->setColumnCount(2);
    ui->tbl_inputs->setHorizontalHeaderLabels(headers);
    ui->tbl_outputs->setColumnCount(2);
    ui->tbl_outputs->setHorizontalHeaderLabels(headers);
    QDir dir("../fcl");
    QStringList filter;
    filter.append("*.fcl");
    dir.setNameFilters(filter);
    QStringList fclfiles = dir.entryList();
    for(int i = 0; i < fclfiles.size(); i++)
    {
        ui->cmb_fcl_files->addItem(fclfiles.at(i));
    }
    initFuzzyModel(ui->cmb_fcl_files->currentText());
}

CalculationDialog::~CalculationDialog()
{
    if(model) delete model;
    delete ui;
}

void CalculationDialog::initFuzzyModel(QString fileUri)
{
    if(model) delete model;
    model = new jfuzzyqt::JFuzzyQt;
    if(!model->load(QString("../fcl/%1").arg(fileUri)))
    {
        QMessageBox::critical(this, trUtf8("Error opening file"),
                              trUtf8("Error loading file '%1'")
                              .arg(QString("../fcl/%1").arg(fileUri)));
        ui->cmb_fcl_files->removeItem(ui->cmb_fcl_files->currentIndex());
    }
    ui->tbl_inputs->setRowCount(0);
    QStringList funct_blocks = model->functBlocks();
    for(int i = 0; i < funct_blocks.size(); i++)
    {
        ui->tbl_inputs->setRowCount(ui->tbl_inputs->rowCount()+1);
        QTableWidgetItem*fb = new QTableWidgetItem(funct_blocks.at(i));
        fb->setTextAlignment(Qt::AlignCenter);
        QFont f = fb->font();
        f.setBold(true);
        fb->setFont(f);
        ui->tbl_inputs->setItem(ui->tbl_inputs->rowCount()-1, 0, fb);
        ui->tbl_inputs->setSpan(ui->tbl_inputs->rowCount()-1, 0, 1, 2);
        QStringList inputs = model->inputs(funct_blocks.at(i));
        for(int j = 0; j < inputs.size(); j++)
        {
            ui->tbl_inputs->setRowCount(ui->tbl_inputs->rowCount()+1);
            ui->tbl_inputs->setItem(ui->tbl_inputs->rowCount()-1, 0, new QTableWidgetItem(inputs.at(j)));
            QDoubleSpinBox* sb = new QDoubleSpinBox(this);
            sb->setRange(-10000.,10000.);
            sb->setDecimals(3);
            sb->setSingleStep(0.1);
            sb->setValue(0);
            sb->setReadOnly(false);
            QObject::connect(sb, SIGNAL(valueChanged(double)), this, SLOT(changeInputData()));
            ui->tbl_inputs->setCellWidget(ui->tbl_inputs->rowCount()-1, 1, sb);
        }

    }
    ui->tbl_outputs->setRowCount(0);
    for(int i = 0; i < funct_blocks.size(); i++)
    {
        ui->tbl_outputs->setRowCount(ui->tbl_outputs->rowCount()+1);
        QTableWidgetItem*fb = new QTableWidgetItem(funct_blocks.at(i));
        fb->setTextAlignment(Qt::AlignCenter);
        QFont f = fb->font();
        f.setBold(true);
        fb->setFont(f);
        ui->tbl_outputs->setItem(ui->tbl_outputs->rowCount()-1, 0, fb);\
        ui->tbl_outputs->setSpan(ui->tbl_outputs->rowCount()-1, 0, 1, 2);
        QStringList outputs = model->outputs(funct_blocks.at(i));
        for(int j = 0; j < outputs.size(); j++)
        {
            ui->tbl_outputs->setRowCount(ui->tbl_outputs->rowCount()+1);
            ui->tbl_outputs->setItem(ui->tbl_outputs->rowCount()-1, 0, new QTableWidgetItem(outputs.at(j)));
            ui->tbl_outputs->setItem(ui->tbl_outputs->rowCount()-1, 1,
                                     new QTableWidgetItem(QString("%1")
                                                          .arg(model->getValue(outputs.at(j),funct_blocks.at(i)),
                                                               0, 'f', 3)));
        }

    }
    ui->btn_eval->setEnabled(false);
}

void CalculationDialog::changeInputData()
{
    ui->btn_eval->setEnabled(true);
}

void CalculationDialog::evaluate()
{
    if(model)
    {
        QString funct_block;
        for(int i = 0; i < ui->tbl_inputs->rowCount(); i++)
        {
            if(ui->tbl_inputs->columnSpan(i, 0) == 2)
            {
                funct_block = ui->tbl_inputs->item(i, 0)->text();
            }else{
                model->setVariable(ui->tbl_inputs->item(i, 0)->text(),
                                   dynamic_cast<QDoubleSpinBox*>(ui->tbl_inputs->cellWidget(i, 1))->value());
            }
        }
        model->evaluate();
        ui->tbl_outputs->setRowCount(0);
        QStringList funct_blocks = model->functBlocks();
        for(int i = 0; i < funct_blocks.size(); i++)
        {
            ui->tbl_outputs->setRowCount(ui->tbl_outputs->rowCount()+1);
            QTableWidgetItem*fb = new QTableWidgetItem(funct_blocks.at(i));
            fb->setTextAlignment(Qt::AlignCenter);
            QFont f = fb->font();
            f.setBold(true);
            fb->setFont(f);
            ui->tbl_outputs->setItem(ui->tbl_outputs->rowCount()-1, 0, fb);\
            ui->tbl_outputs->setSpan(ui->tbl_outputs->rowCount()-1, 0, 1, 2);
            QStringList outputs = model->outputs(funct_blocks.at(i));
            for(int j = 0; j < outputs.size(); j++)
            {
                ui->tbl_outputs->setRowCount(ui->tbl_outputs->rowCount()+1);
                ui->tbl_outputs->setItem(ui->tbl_outputs->rowCount()-1, 0,
                                         new QTableWidgetItem(outputs.at(j)));
                ui->tbl_outputs->setItem(ui->tbl_outputs->rowCount()-1, 1,
                                         new QTableWidgetItem(QString("%1")
                                                              .arg(model->getValue(outputs.at(j),funct_blocks.at(i)),
                                                                   0, 'f', 3)));
            }

        }
    }
}
