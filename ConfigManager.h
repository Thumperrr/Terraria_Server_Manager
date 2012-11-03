#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QDialog>

namespace Ui {
class ConfigManager;
}

class ConfigManager : public QDialog
{
    Q_OBJECT
    
public:
    explicit ConfigManager(QWidget *parent = 0);
    ~ConfigManager();

public slots:
    void pushButton_Delete_Pressed();
    void pushButton_Edit_Pressed();
    void pushButton_New_Pressed();
    void pushButton_Done_Pressed();
    
private:
    QString left(QString &configLine, char separator);
    void refresh_listWidget_ConfigList();
    Ui::ConfigManager *ui;
};

#endif // CONFIGMANAGER_H
