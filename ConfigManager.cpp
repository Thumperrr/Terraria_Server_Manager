#include "ConfigManager.h"
#include "ui_ConfigManager.h"

ConfigManager::ConfigManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigManager)
{
    ui->setupUi(this);
    connect(ui->pushButton_Done, SIGNAL(clicked()), this, SLOT(pushButton_Done_Pressed()));
    connect(ui->pushButton_Delete, SIGNAL(clicked()), this, SLOT(pushButton_Delete_Pressed()));
    connect(ui->pushButton_Edit, SIGNAL(clicked()), this, SLOT(pushButton_Edit_Pressed()));
    connect(ui->pushButton_New, SIGNAL(clicked()), this, SLOT(pushButton_New_Pressed()));
    connect(ui->listWidget_ConfigList, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(pushButton_Edit_Pressed()));

    //load configs into list view (every file in the directory with a .cfg extension)
    refresh_listWidget_ConfigList();
}

ConfigManager::~ConfigManager()
{
    delete ui;
}

void ConfigManager::pushButton_Done_Pressed()
{
    close();
}
void ConfigManager::pushButton_Delete_Pressed()
{
    QString configName = ui->listWidget_ConfigList->currentItem()->text();

    if(QMessageBox::information(this, tr("Warning"), tr("Are you sure you want to delete this configuration?"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
        return;

    QFile configFile(configName + ".cfg");
    configFile.remove();
    refresh_listWidget_ConfigList();
}
void ConfigManager::pushButton_Edit_Pressed()
{
    QString configName = ui->listWidget_ConfigList->currentItem()->text();
    ConfigEditor *configEditor = new ConfigEditor(this);
    configEditor->editConfig(ConfigEditor::loadConfig(configName));
    configEditor->exec();
    delete configEditor;

    refresh_listWidget_ConfigList();
}
void ConfigManager::pushButton_New_Pressed()
{
    //start a ConfigEditor, then refresh the listWidget.
    ConfigEditor *configEditor = new ConfigEditor();
    configEditor->exec();
    delete configEditor;

    refresh_listWidget_ConfigList();
}

void ConfigManager::refresh_listWidget_ConfigList()
{
    ui->listWidget_ConfigList->clear(); //clear list

    QStringList files = Utility::getDirectoryEntryList(QStringList("*.cfg"));

    QString str;
    foreach(str, files)
        ui->listWidget_ConfigList->addItem(Utility::left(str, '.'));
}
