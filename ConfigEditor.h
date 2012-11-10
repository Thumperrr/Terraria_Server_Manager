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

#ifndef ConfigEditor_H
#define ConfigEditor_H

#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include "Utility.h"

struct Configuration {
    QString name; //name of the configuration
    QString world; //location of the world to load on startup
    QString password;
    QString motd;
    QString worldpath; //path where world files are stored
    QString worldname; //name for autocreated worlds
    QString banlist;
    int maxPlayers;
    int autocreate; //Auto create size, 1:small 2:medium 3:large
    int port;
    int secure; //Enable security, 0:no, 1:yes
    int lang; //language, 1:English, 2:German, 3:Italian, 4:French, 5:Spanish
    int priority; //native priority, 0:Realtime, 1:High, 2:AboveNormal, 3:Normal, 4:BelowNormal, 5:Idle
};

namespace Ui {
    class ConfigEditor;
}

class ConfigEditor : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigEditor(QWidget *parent = 0);
    ~ConfigEditor();

    static Configuration loadConfig(QString _config);
    void editConfig(Configuration _config);

public slots:
    void on_pushButton_Save_clicked();
    void on_pushButton_Cancel_clicked();
    void on_pushButton_World_clicked();

private:
    void saveToFile();

    Ui::ConfigEditor *ui;
    Configuration config;

    bool editingMode;
    QString oldName; //used to tell if the name changed, so that ConfigEditor doesn't create a new file with a new name and leave the old one.
};

#endif // ConfigEditor_H
