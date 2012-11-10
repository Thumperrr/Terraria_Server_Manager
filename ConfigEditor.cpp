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

#include "ConfigEditor.h"
#include "ui_ConfigEditor.h"

ConfigEditor::ConfigEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigEditor)
{
    editingMode = false;

    ui->setupUi(this);
    connect(ui->pushButton_Cancel, SIGNAL(clicked()), this, SLOT(slot_pushButton_Cancel_clicked()));
    connect(ui->pushButton_Save, SIGNAL(clicked()), this, SLOT(slot_pushButton_Save_clicked()));
    connect(ui->pushButton_World, SIGNAL(clicked()), this, SLOT(slot_pushButton_World_clicked()));
    ui->lineEdit_AutoCreateName->setText("Auto Created World");
}

ConfigEditor::~ConfigEditor()
{
    delete ui;
}

void ConfigEditor::slot_pushButton_Cancel_clicked()
{
    done(0);
}

void ConfigEditor::slot_pushButton_Save_clicked()
{
    config.name = ui->lineEdit_Name->text();
    config.world = ui->lineEdit_World->text();
    config.password = ui->lineEdit_Password->text();
    config.motd = ui->lineEdit_MOTD->text();
    config.worldname = ui->lineEdit_AutoCreateName->text();
    config.banlist = (config.name + "_banlist.txt");
    config.autocreate = ui->comboBox_AutoCreateSize->currentIndex()+1;
    config.lang = ui->comboBox_Language->currentIndex()+1;
    config.port = ui->spinBox_Port->value();
    config.maxPlayers = ui->spinBox_MaxPlayers->value();
    config.priority = 1;

    if(ui->checkBox_Secure->isChecked())
        config.secure = 1;
    else
        config.secure = 0;

    //TODO: check if everything is filled out.
    //if(!checkRequiredFields())


    //Delete everything after the last '\' in the world path to leave
    //the folder location of the world.
    //ex: C:\users\terraria\world1.wld
    //'\world1.wld' is deleted to leave "C:\users\terraria\"
    QString temp = config.world;
    int index = temp.lastIndexOf("/");
    config.worldpath = temp.left(index+1);

    saveToFile();
    close();
}

void ConfigEditor::slot_pushButton_World_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                            tr("Select World File"), QString(),
                                            tr("Terraria World (*.wld);;All Files (*)"));
    ui->lineEdit_World->setText(fileName);
}

void ConfigEditor::saveToFile()
{
    QFile file(config.name + ".cfg");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
        QMessageBox::information(this, tr("Error"), tr("Unable to open file"), QMessageBox::Ok);
        return;
    }

    QTextStream stream(&file);
    stream << "#This is a Terraria Server config file generated by Terraria Server Manager 1.0\n";
    stream << "@" << config.name << endl;
    stream << "maxplayers=" << config.maxPlayers << endl;
    stream << "world=" << config.world << endl;
    stream << "port=" << config.port << endl;
    stream << "password=" << config.password << endl;
    stream << "motd=" << config.motd << endl;
    stream << "worldpath=" << config.worldpath << endl;
    stream << "autocreate=" << config.autocreate << endl;
    stream << "worldname=" << config.worldname << endl;
    stream << "banlist=" << config.banlist << endl;
    stream << "secure=" << config.secure << endl;
    stream << "lang=" << config.lang << endl;
    stream << "priority=" << config.priority << endl;

    if(editingMode)
        if(oldName != config.name)
        {
            QFile oldFile(oldName + ".cfg");
            oldFile.remove();
        }
}

Configuration ConfigEditor::loadConfig(QString _config)
{
    Configuration ret;

    QFile file(_config + ".cfg");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return ret;
    }

    QTextStream stream(&file);
    while(true)
    {
        QString line = stream.readLine();
        if(line.isEmpty() || line.isNull() || stream.atEnd())
            break;
        if(!line.contains("#")) //is a comment (first line); ignore
        {
            if(line[0] == '@') //Configuration.name
                ret.name = Utility::right(line, '@');
            else if(line.contains("maxplayers="))
                ret.maxPlayers = Utility::right(line, '=').toInt();
            else if(line.contains("world="))
                ret.world = Utility::right(line, '=');
            else if(line.contains("port="))
                ret.port = Utility::right(line, '=').toInt();
            else if(line.contains("password="))
                ret.password = Utility::right(line, '=');
            else if(line.contains("motd="))
                ret.motd = Utility::right(line, '=');
            else if(line.contains("worldpath="))
                ret.worldpath = Utility::right(line, '=');
            else if(line.contains("autocreate="))
                ret.autocreate = Utility::right(line, '=').toInt();
            else if(line.contains("worldname="))
                ret.worldname = Utility::right(line, '=');
            else if(line.contains("banlist="))
                ret.banlist = Utility::right(line, '=');
            else if(line.contains("secure="))
                ret.secure = Utility::right(line, '=').toInt();
            else if(line.contains("lang="))
                ret.lang = Utility::right(line, '=').toInt();
            else if(line.contains("priority"))
                ret.priority = Utility::right(line, '=').toInt();
        }
    }

    return ret;
}

void ConfigEditor::editConfig(Configuration _config)
{
    editingMode = true;
    oldName = _config.name;

    ui->lineEdit_Name->setText(_config.name);
    ui->spinBox_MaxPlayers->setValue(_config.maxPlayers);
    ui->lineEdit_World->setText(_config.world);
    ui->spinBox_Port->setValue(_config.port);
    ui->lineEdit_Password->setText(_config.password);
    ui->lineEdit_MOTD->setText(_config.motd);
    ui->comboBox_AutoCreateSize->setCurrentIndex(_config.autocreate - 1);
    ui->lineEdit_AutoCreateName->setText(_config.worldname);
    ui->comboBox_Language->setCurrentIndex(_config.lang - 1);
    if(_config.secure == 1)
        ui->checkBox_Secure->setCheckState(Qt::Checked);
    else
        ui->checkBox_Secure->setCheckState(Qt::Unchecked);
}
