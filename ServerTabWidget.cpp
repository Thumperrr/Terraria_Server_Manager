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

#include "ServerTabWidget.h"
#include "ui_ServerTabWidget.h"

ServerTabWidget::ServerTabWidget(QString _config, QWidget *parent) : QWidget(parent), ui(new Ui::ServerTabWidget)
{
    ui->setupUi(this);
    config = _config;
    init();
}

ServerTabWidget::~ServerTabWidget()
{
    delete ui;
    delete serverProcess;
    delete saveTimer;
    delete playersModel;
}

void ServerTabWidget::init()
{
    serverProcess = new QProcess();
    saveTimer = new QTimer;
    playersModel = new QStringListModel(players);
    playersFilterModel = new QSortFilterProxyModel();

    saveTimer->setInterval(60000);
    saveTimer->start();
    playersFilterModel->setSourceModel(playersModel);
    ui->listView_Players->setModel(playersFilterModel);

    connect(serverProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(on_serverProcess_readyReadStandardOutput()));
    connect(ui->lineEdit_ServerInput, SIGNAL(returnPressed()), this, SLOT(on_lineEdit_ServerInput_returnPressed()));
    connect(saveTimer, SIGNAL(timeout()), this, SLOT(on_saveTimer_Timeout()));
    connect(ui->lineEdit_SearchPlayers, SIGNAL(textChanged(QString)), this, SLOT(on_lineEdit_SearchPlayers_textChanged()));
    connect(ui->listView_Players, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_listView_Players_customContextMenuRequested(QPoint)));

    QString pro = "TerrariaServer.exe";
    QStringList args;
    args << "-config" << config;
    serverProcess->start(pro, args);

    if(!serverProcess->waitForStarted())
    {
        QMessageBox::information(this, tr("Error"), tr("Unable to start the server."), QMessageBox::Ok);
        close();
    }
}

void ServerTabWidget::on_serverProcess_readyReadStandardOutput()
{
    QTextStream stream(serverProcess->readAllStandardOutput());
    while(true)
    {
        QString line = stream.readLine();
        if(line.isNull())
            break;
        else
        {
            processLine(line);
        }
    }
}

void ServerTabWidget::on_lineEdit_ServerInput_returnPressed()
{
    writeToProcess(ui->lineEdit_ServerInput->text());
    ui->lineEdit_ServerInput->clear();
}

void ServerTabWidget::on_saveTimer_Timeout()
{
    if(!players.isEmpty()) //don't save if no one is connected -- no changes could be made.
    {
        writeToProcess("save");
        ui->textBrowser_ServerOutput->append("Saving world...");
        saveTimer->start();
    }
}

void ServerTabWidget::on_lineEdit_SearchPlayers_textChanged()
{
    update_listView_Players_Filter();
}

void ServerTabWidget::on_listView_Players_customContextMenuRequested(QPoint p)
{
    if(players.isEmpty())
        return;
    if(!ui->listView_Players->indexAt(p).isValid())
        return;

    QMenu contextMenu;
    contextMenu.addAction("Kick");

    QAction *selectedAction = contextMenu.exec(ui->listView_Players->mapToGlobal(p));
    if(selectedAction)
    {
        if(selectedAction->text() == "Kick")
        {
            QString playerName = ui->listView_Players->indexAt(p).data().toString();
            writeToProcess("kick " + playerName);
        }
    }
}

void ServerTabWidget::writeToProcess(QString text)
{
    QByteArray toWrite;
    toWrite.append(text + "\n");
    serverProcess->write(toWrite);
}

void ServerTabWidget::update_listView_Players()
{
    playersModel->setStringList(players);
}

void ServerTabWidget::update_listView_Players_Filter()
{
    QRegExp regExp(ui->lineEdit_SearchPlayers->text(), Qt::CaseInsensitive, QRegExp::Wildcard);
    playersFilterModel->setFilterRegExp(regExp);
}

void ServerTabWidget::processLine(QString line)
{
    bool appendOutput = true;

    if(line.contains("has joined.")) //a player might be joining
    {
        QString playerName = Utility::word(line);

        //check to see if a player actually joined
        //and someone didn't just type "has joined." in chat.
        if(playerName + " has joined." == line)
        {
            players.push_back(playerName);
            update_listView_Players();
        }
    }
    else if(line.contains("has left.")) //a player might have left
    {
        QString playerName;
        if(line[0] == ':')
            playerName = Utility::word(line, 2); //line is different when kicking a player
        else
            playerName = Utility::word(line);

        if(playerName + " has left." == line || ": " + playerName + " has left." == line)
        {
            QStringList::Iterator i;
            for(i = players.begin(); i < players.end(); ++i) {
                if(*i == playerName) {
                    players.removeOne(playerName);
                    break;
                }
            }
            update_listView_Players();
        }
    }
    else if(line.contains("Saving world data:"))
    {    //do nothing to prevent output area from being clogged up.
        appendOutput = false;
    }

    if(appendOutput)
        ui->textBrowser_ServerOutput->append(line);
}
