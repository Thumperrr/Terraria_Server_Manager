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
    connect(ui->actionHost, SIGNAL(triggered()), this, SLOT(actionHost_Triggered()));
    connect(ui->actionShutdown, SIGNAL(triggered()), this, SLOT(removeSelectedServerTab()));
    connect(ui->actionConfigurations, SIGNAL(triggered()), this, SLOT(actionConfigurations_Triggered()));
    connect(ui->actionOptions, SIGNAL(triggered()), this, SLOT(actionOptions_Triggered()));
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

void MainWindow::actionConfigurations_Triggered()
{
    ConfigManager *configManager = new ConfigManager(this);
    configManager->exec();
    delete configManager;
}

void MainWindow::actionHost_Triggered()
{
    //launch a ConfigBrowser
    ConfigSelector *configSelector = new ConfigSelector(this);
    configSelector->exec();

    QString config = configSelector->getConfig();
    if(!config.isNull() && !config.isEmpty())
        addServerTab(config);
    delete configSelector;
}

void MainWindow::actionOptions_Triggered()
{
   /* Options *options = new Options(this);
    options->exec();
    int isaveTimer = options->getSaveMinutes();
    delete options;*/

    //TODO
}
