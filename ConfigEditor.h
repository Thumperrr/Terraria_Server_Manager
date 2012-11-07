#ifndef ConfigEditor_H
#define ConfigEditor_H

#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include "Utility.h"

struct Configuration {
    QString name; //name of the configuration
    QString world; //location of the world to load on startup
    QString password;
    QString motd;
    QString worldpath; //path where world files are stored
    QString worldname; //name for autocreated worlds
    QString banlist;
    int maxPlayers;
    int autocreate; //Auto create size, 1:small 2:medium 3:large
    int port;
    int secure; //Enable security, 0:no, 1:yes
    int lang; //language, 1:English, 2:German, 3:Italian, 4:French, 5:Spanish
    int priority; //native priority, 0:Realtime, 1:High, 2:AboveNormal, 3:Normal, 4:BelowNormal, 5:Idle
};

namespace Ui {
    class ConfigEditor;
}

class ConfigEditor : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigEditor(QWidget *parent = 0);
    ~ConfigEditor();

    static Configuration loadConfig(QString _config);
    void editConfig(Configuration _config);

public slots:
    void pushButton_Save_Pressed();
    void pushButton_Cancel_Pressed();
    void pushButton_World_Pressed();

private:
    void saveToFile();

    Ui::ConfigEditor *ui;
    Configuration config;

    bool editingMode;
    QString oldName; //used to tell if the name changed, so that ConfigEditor doesn't create a new file with a new name and leave the old one.
};

#endif // ConfigEditor_H
