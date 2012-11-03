#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>

namespace Ui {
class Options;
}

class Options : public QDialog
{
    Q_OBJECT
    
public:
    explicit Options(QWidget *parent = 0);
    ~Options();
    int getSaveMinutes();
    
private:
    Ui::Options *ui;
    int *saveMinutes;
};

#endif // OPTIONS_H
