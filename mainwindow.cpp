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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ServerTabWidget.h"
#include "ConfigManager.h"
#include "ConfigSelector.h"
#include "Options.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionHost, SIGNAL(triggered()), this, SLOT(slot_actionHost_triggered()));
    connect(ui->actionShutdown, SIGNAL(triggered()), this, SLOT(slot_actionShutdown_triggered()));
    connect(ui->actionConfigurations, SIGNAL(triggered()), this, SLOT(slot_actionConfigurations_triggered()));
    connect(ui->actionOptions, SIGNAL(triggered()), this, SLOT(slot_actionOptions_triggered()));
}

void MainWindow::slot_actionShutdown_triggered()
{
    removeSelectedServerTab();
}

void MainWindow::slot_actionConfigurations_triggered()
{
    ConfigManager *configManager = new ConfigManager(this);
    configManager->exec();
    delete configManager;
}

void MainWindow::slot_actionHost_triggered()
{
    //launch a ConfigSelector
    ConfigSelector *configSelector = new ConfigSelector(this);
    configSelector->exec();

    QString config = configSelector->getConfig();
    if(!config.isNull() && !config.isEmpty())
        addServerTab(config);
    delete configSelector;
}

void MainWindow::slot_actionOptions_triggered()
{
   /* Options *options = new Options(this);
    options->exec();
    int isaveTimer = options->getSaveMinutes();
    delete options;*/

    //TODO
}

void MainWindow::addServerTab(QString name) {
    QWidget *tabWidget = new ServerTabWidget(name + ".cfg");
    ui->tabWidget->addTab(tabWidget, name);
}

void MainWindow::removeSelectedServerTab() {
    int index = ui->tabWidget->currentIndex();
    QWidget *instance = ui->tabWidget->widget(index);
    ui->tabWidget->removeTab(index);
    delete instance;
}
