#include "Options.h"
#include "ui_Options.h"

Options::Options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);
}

Options::~Options()
{
    delete ui;
}

int Options::getSaveMinutes()
{
    return ui->spinBox_SaveMinutes->value();
}