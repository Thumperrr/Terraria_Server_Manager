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

#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QDialog>
#include <QListWidgetItem>
#include <QMessageBox>
#include "ConfigEditor.h"
#include "Utility.h"

namespace Ui {
class ConfigManager;
}

class ConfigManager : public QDialog
{
    Q_OBJECT
    
public:
    explicit ConfigManager(QWidget *parent = 0);
    ~ConfigManager();

public slots:
    void slot_pushbutton_Delete_clicked();
    void slot_pushbutton_Edit_clicked();
    void slot_pushbutton_New_clicked();
    void slot_pushbutton_Done_clicked();
    
private:
    void refresh_listWidget_ConfigList();
    Ui::ConfigManager *ui;
};

#endif // CONFIGMANAGER_H
