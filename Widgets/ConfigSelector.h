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

#ifndef CONFIGSELECTOR_H
#define CONFIGSELECTOR_H

#include <QDialog>
#include "../Util/Utility.h"

namespace Ui {
class ConfigSelector;
}

class ConfigSelector : public QDialog
{
    Q_OBJECT
    
public:
    explicit ConfigSelector(QWidget *parent = 0);
    ~ConfigSelector();
    QString getConfig();

public slots:
    void slot_listWidget_doubleClicked();
    
private:
    Ui::ConfigSelector *ui;
    QString config;
};

#endif // CONFIGSELECTOR_H
