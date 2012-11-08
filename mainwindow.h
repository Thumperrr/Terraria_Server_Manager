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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void addServerTab(QString name);
    void removeSelectedServerTab();
    void actionConfigurations_Triggered();
    void actionHost_Triggered();
    void actionOptions_Triggered();
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init();
    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
