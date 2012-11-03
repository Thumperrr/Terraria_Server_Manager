#ifndef CONFIGSELECTOR_H
#define CONFIGSELECTOR_H

#include <QDialog>

namespace Ui {
class ConfigSelector;
}

class ConfigSelector : public QDialog
{
    Q_OBJECT
    
public:
    explicit ConfigSelector(QWidget *parent = 0);
    ~ConfigSelector();
    QString getConfig();

public slots:
    void listWidget_DoubleClicked();
    
private:
    Ui::ConfigSelector *ui;
    QString config;
    QString left(QString &configLine, char separator);
};

#endif // CONFIGSELECTOR_H
