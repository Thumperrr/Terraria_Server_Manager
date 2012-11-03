#include "ConfigSelector.h"
#include "ui_ConfigSelector.h"
#include <QDir>

ConfigSelector::ConfigSelector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigSelector)
{
    ui->setupUi(this);
    connect(ui->listWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(listWidget_DoubleClicked()));

    QDir *currentDir = new QDir(QDir::currentPath());
    QStringList files = currentDir->entryList(QStringList("*.cfg"), QDir::NoFilter, QDir::Name);

    QString str;
    foreach(str, files)
        ui->listWidget->addItem(left(str, '.'));
    delete currentDir;
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

QString ConfigSelector::left(QString &configLine, char separator) {
    std::string stdConfigLine = configLine.toStdString();
    std::string ret = stdConfigLine.substr(0, stdConfigLine.find(separator));
    return QString::fromStdString(ret);
}
