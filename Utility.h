#ifndef UTILITY_H
#define UTILITY_H

#include <QString>
#include <string>
#include <QDir>

namespace Utility
{
    QString left(QString line, char separator);
    QString right(QString line, char separator);
    QString word(QString line, int wordNumber = 1);
    QStringList splitString(QString line, QString separator = " ");
    QStringList getDirectoryEntryList(QStringList nameFilters, QString path = QDir::currentPath());
}

#endif // UTILITY_H
