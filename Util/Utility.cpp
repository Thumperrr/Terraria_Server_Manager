/* This file is part of Terraria Server Manager.

Terraria Server Manager is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Terraria Server Manager is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Terraria Server Manager.  If not, see <http://www.gnu.org/licenses/>. */

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
