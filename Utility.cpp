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
    QString word(QString line, int wordNumber)
    {
        QStringList words = splitString(line);
        return words[wordNumber-1];
    }
    QStringList splitString(QString line, QString separator)
    {
        QStringList ret;
        std::string stdLine = line.toStdString(), stdSeparator = separator.toStdString();
        std::string::size_type start = 0, end = 0;
        while((end = stdLine.find(stdSeparator, start)) != std::string::npos)
        {
            ret.push_back(QString::fromStdString(stdLine.substr(start, end - start)));
            start = end + stdSeparator.size();
        }
        ret.push_back(QString::fromStdString(stdLine.substr(start)));
        return ret;
    }

    QStringList getDirectoryEntryList(QStringList nameFilters, QString path)
    {
        QDir dir(path);
        return dir.entryList(nameFilters, QDir::NoFilter, QDir::Name);
    }
}
