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
