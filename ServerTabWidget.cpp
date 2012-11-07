#include <QMessageBox>
#include <QTextStream>
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
}

void ServerTabWidget::init()
{
    serverProcess = new QProcess();
    saveTimer = new QTimer;
    saveTimer->setInterval(60000);
    saveTimer->start();

    connect(serverProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(readAllStandardOutput()));
    connect(ui->lineEdit_ServerInput, SIGNAL(returnPressed()), this, SLOT(writeToProcess()));
    connect(saveTimer, SIGNAL(timeout()), this, SLOT(saveTimer_Timeout()));

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

void ServerTabWidget::readAllStandardOutput()
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

void ServerTabWidget::writeToProcess()
{
    writeToProcess(ui->lineEdit_ServerInput->text());
    ui->lineEdit_ServerInput->clear();
}

void ServerTabWidget::writeToProcess(QString text)
{
    QByteArray toWrite;
    toWrite.append(text + "\n");
    serverProcess->write(toWrite);
}

void ServerTabWidget::saveTimer_Timeout()
{
    if(!players.isEmpty()) //don't save if no one is connected -- no changes could be made.
    {
        writeToProcess("save");
        ui->textBrowser_ServerOutput->append("Saving world...");
        saveTimer->start();
    }
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
            QListWidgetItem *newItem = new QListWidgetItem(playerName);
            players.insert(playerName, newItem);
            ui->listWidget_Players->addItem(newItem);
        }
    }
    else if(line.contains("has left.")) //a player might have left
    {
        QString playerName = Utility::word(line);

        if(playerName + " has left." == line)
        {
            ui->listWidget_Players->removeItemWidget(players[playerName]);
            delete players[playerName];
            players.remove(playerName);
        }
    }
    else if(line.contains("Saving world data:"))
    {    //do nothing to prevent output area from being clogged up.
        appendOutput = false;
    }

    if(appendOutput)
        ui->textBrowser_ServerOutput->append(line);
}
