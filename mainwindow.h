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
    void on_actionShutdown_triggered();
    void on_actionConfigurations_triggered();
    void on_actionHost_triggered();
    void on_actionOptions_triggered();
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init();
    
private:
    Ui::MainWindow *ui;
    void addServerTab(QString name);
    void removeSelectedServerTab();
};

#endif // MAINWINDOW_H
