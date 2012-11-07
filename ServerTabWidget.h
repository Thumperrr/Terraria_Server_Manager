#ifndef SERVERTABWIDGET_H
#define SERVERTABWIDGET_H

#include <QWidget>
#include <QProcess>
#include <QTimer>

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
    QStringList *players;
};

#endif // SERVERTABWIDGET_H
