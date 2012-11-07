#include "Utility.h"

namespace Utility {
    QString left(QString line, char separator)
    {
        std::string stdLine = line.toStdString();
        std::string ret = stdLine.substr(0, stdLine.find(separator));
        return QString::fromStdString(ret);
    }
    QString right(QString line, char separator)
    {
        std::string stdLine = line.toStdString();
        std::string ret = stdLine.substr(stdLine.find(separator)+1, std::string::npos);
        return QString::fromStdString(ret);
    }

    QStringList getDirectoryEntryList(QStringList nameFilters, QString path)
    {
        QDir dir(path);
        return dir.entryList(nameFilters, QDir::NoFilter, QDir::Name);
    }
}
