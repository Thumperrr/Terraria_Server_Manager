#include "ConfigSelector.h"
#include "ui_ConfigSelector.h"

ConfigSelector::ConfigSelector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigSelector)
{
    ui->setupUi(this);
    connect(ui->listWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(listWidget_DoubleClicked()));

    QStringList files = Utility::getDirectoryEntryList(QStringList("*.cfg"));

    QString str;
    foreach(str, files)
        ui->listWidget->addItem(Utility::left(str, '.'));
}

ConfigSelector::~ConfigSelector()
{
    delete ui;
}

void ConfigSelector::listWidget_DoubleClicked()
{
    config = ui->listWidget->currentItem()->text();
    close();
}

QString ConfigSelector::getConfig()
{
    return config;
}
