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

#ifndef SERVERTABWIDGET_H
#define SERVERTABWIDGET_H

#include <QWidget>
#include <QProcess>
#include <QTimer>
#include <QMap>
#include <QPointer>
#include <QListWidgetItem>
#include "Utility.h"

namespace Ui {
   class ServerTabWidget;
}

class ServerTabWidget : public QWidget
{
    Q_OBJECT
public:
    ServerTabWidget(QString _config, QWidget *parent = 0);
    ~ServerTabWidget();
    void init();
    void writeToProcess(QString text);

public slots:
    void readAllStandardOutput();
    void writeToProcess();
    void saveTimer_Timeout();

private:
    Ui::ServerTabWidget *ui;
    QProcess *serverProcess;
    QString config;
    QTimer *saveTimer;
    QMap<QString, QListWidgetItem*> players;

    void processLine(QString line);

    bool playerConnecting;
};

#endif // SERVERTABWIDGET_H
