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
