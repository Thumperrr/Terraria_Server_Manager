#ifndef UTILITY_H
#define UTILITY_H

#include <QString>
#include <string>
#include <QDir>

namespace Utility
{
    QString left(QString line, char separator);
    QString right(QString line, char separator);
    QStringList getDirectoryEntryList(QStringList nameFilters, QString path = QDir::currentPath());
}

#endif // UTILITY_H
