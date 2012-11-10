/* This file is part of Terraria Server Manager.

Terraria Server Manager is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Terraria Server Manager is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Terraria Server Manager.  If not, see <http://www.gnu.org/licenses/>. */

#include "ConfigManager.h"
#include "ui_ConfigManager.h"

ConfigManager::ConfigManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigManager)
{
    ui->setupUi(this);
    connect(ui->pushButton_Done, SIGNAL(clicked()), this, SLOT(on_pushButton_Done_clicked()));
    connect(ui->pushButton_Delete, SIGNAL(clicked()), this, SLOT(on_pushButton_Delete_clicked()));
    connect(ui->pushButton_Edit, SIGNAL(clicked()), this, SLOT(on_pushButton_Edit_clicked()));
    connect(ui->pushButton_New, SIGNAL(clicked()), this, SLOT(on_pushButton_New_clicked()));
    connect(ui->listWidget_ConfigList, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_pushButton_Edit_clicked()));

    //load configs into list view (every file in the directory with a .cfg extension)
    refresh_listWidget_ConfigList();
}

ConfigManager::~ConfigManager()
{
    delete ui;
}

void ConfigManager::on_pushButton_Done_clicked()
{
    close();
}
void ConfigManager::on_pushButton_Delete_clicked()
{
    QString configName = ui->listWidget_ConfigList->currentItem()->text();

    if(QMessageBox::information(this, tr("Warning"), tr("Are you sure you want to delete this configuration?"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
        return;

    QFile configFile(configName + ".cfg");
    configFile.remove();
    refresh_listWidget_ConfigList();
}
void ConfigManager::on_pushButton_Edit_clicked()
{
    QString configName = ui->listWidget_ConfigList->currentItem()->text();
    ConfigEditor *configEditor = new ConfigEditor(this);
    configEditor->editConfig(ConfigEditor::loadConfig(configName));
    configEditor->exec();
    delete configEditor;

    refresh_listWidget_ConfigList();
}
void ConfigManager::on_pushButton_New_clicked()
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
