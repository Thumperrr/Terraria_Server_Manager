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
            if(line.contains("!server noon"))
                writeToProcess("noon");
            ui->textBrowser_ServerOutput->append(line);
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
    writeToProcess("save");
    saveTimer->start();
}
