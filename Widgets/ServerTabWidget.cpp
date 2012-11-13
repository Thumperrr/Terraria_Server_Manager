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
    delete playersFilterModel;
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

    Utility::Configuration configuration;
    if(Utility::loadConfig(this->config, configuration))
        worldPath = configuration.world;

    connect(serverProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(slot_serverProcess_readyReadStandardOutput()));
    connect(ui->lineEdit_ServerInput, SIGNAL(returnPressed()), this, SLOT(slot_lineEdit_ServerInput_returnPressed()));
    connect(saveTimer, SIGNAL(timeout()), this, SLOT(slot_saveTimer_Timeout()));
    connect(ui->lineEdit_SearchPlayers, SIGNAL(textChanged(QString)), this, SLOT(slot_lineEdit_SearchPlayers_textChanged()));
    connect(ui->listView_Players, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_listView_Players_customContextMenuRequested(QPoint)));

    update_textBrowser_WorldInfo();

    QString pro = "TerrariaServer.exe";
    QStringList args;
    args << "-config" << config + ".cfg";
    serverProcess->start(pro, args);

    if(!serverProcess->waitForStarted())
    {
        QMessageBox::information(this, tr("Error"), tr("Unable to start the server."), QMessageBox::Ok);
        close();
    }

}

void ServerTabWidget::slot_serverProcess_readyReadStandardOutput()
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

void ServerTabWidget::slot_lineEdit_ServerInput_returnPressed()
{
    writeToProcess(ui->lineEdit_ServerInput->text());
    ui->lineEdit_ServerInput->clear();
}

void ServerTabWidget::slot_saveTimer_Timeout()
{
    if(!players.isEmpty()) //don't save if no one is connected -- no changes could be made.
    {
        writeToProcess("save");
        ui->textBrowser_ServerOutput->append("Saving world...");
        saveTimer->start();
    }
}

void ServerTabWidget::slot_lineEdit_SearchPlayers_textChanged()
{
    update_listView_Players_Filter();
}

void ServerTabWidget::slot_listView_Players_customContextMenuRequested(QPoint p)
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

void ServerTabWidget::update_textBrowser_WorldInfo()
{
    if(worldPath.isNull() || worldPath.isEmpty())
    {
        ui->textBrowser_WorldInfo->setText("Unable to determine world location.");
        return;
    }

    QString info;
    Utility::WorldHeader header;
    if(!Utility::getWorldHeader(worldPath, header))
    {
        ui->textBrowser_WorldInfo->setText("Unable to open .wld file.");
        return;
    }
    info.append(QString("%1\n").arg(header.name));
    info.append(QString("Version: %1\n").arg(header.releaseNumber));
    info.append(QString("ID: %1\n").arg(header.id));
    info.append(QString("Spawn Point: (%1, %2)\n").arg(header.spawnPoint.x()).arg(header.spawnPoint.y()));
    info.append(QString("Players Online: %1\n\n").arg(players.size()));
    info.append("Bosses Downed:\n");
    if(header.isBoss1Dead)
        info.append("Eye of Cthulhu\n");
    if(header.isBoss2Dead)
        info.append("Eater of Worlds\n");
    if(header.isBoss3Dead)
        info.append("Skeletron\n");
    info.append("\n");
    if(header.hardMode)
        info.append("Hardmode enabled: Yes");
    else
        info.append("Hardmode enabled: No");

    ui->textBrowser_WorldInfo->setText(info);
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
            update_textBrowser_WorldInfo();
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
            update_textBrowser_WorldInfo();
        }
    }
    else if(line.contains("Saving world data:"))
    {    //do nothing to prevent output area from being clogged up.
        appendOutput = false;
    }

    if(appendOutput)
        ui->textBrowser_ServerOutput->append(line);
}
