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
along with Foobar.  If not, see <http://www.gnu.org/licenses/>. */

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
