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

    bool getWorldHeader(QString path, WorldHeader &header)
    {
        bool ret = true;
        BinaryReader reader(path.toStdString());
        if(reader.IsOpen())
        {
            header.releaseNumber = reader.ReadInt32();
            header.name = QString::fromStdString(reader.ReadString());
            header.id = reader.ReadInt32();
            int x, y, w, h;

            x = reader.ReadInt32();
            w = reader.ReadInt32();
            y = reader.ReadInt32();
            h = reader.ReadInt32();

            header.worldCoords = QRect(x, w, y, h);

            y = reader.ReadInt32();
            x = reader.ReadInt32();

            header.maxTiles = QPoint(x, y);
            header.spawnPoint = QPoint(reader.ReadInt32(), reader.ReadInt32());
            header.surfaceLevel = reader.ReadDouble();
            header.rockLayer = reader.ReadDouble();
            header.temporaryTime = reader.ReadDouble();
            header.isDayTime = reader.ReadBoolean();
            header.moonPhase = reader.ReadInt32();
            header.isBloodMoon = reader.ReadBoolean();
            header.dungeonPoint = QPoint(reader.ReadInt32(), reader.ReadInt32());
            header.isBoss1Dead = reader.ReadBoolean();
            header.isBoss2Dead = reader.ReadBoolean();
            header.isBoss3Dead = reader.ReadBoolean();
            if(header.releaseNumber >= 0x24)
            {
                header.isGoblinArmyDefeated = reader.ReadBoolean();
                header.isWizardSaved = reader.ReadBoolean();
                header.isMechanicSaved = reader.ReadBoolean();
                header.isGoblinArmyDefeated = reader.ReadBoolean();
                header.isClownDefeated = reader.ReadBoolean();
            }
            if(header.releaseNumber >= 0x25)
            {
                header.isFrostDefeated = reader.ReadBoolean();
            }
            header.isShadowOrbSmashed = reader.ReadBoolean();
            header.isMeteorSpawned = reader.ReadBoolean();
            header.shadowOrbsSmashed = reader.ReadByte();

            if(header.releaseNumber >= 0x24)
            {
                header.altarsDestroyed = reader.ReadInt32();
                header.hardMode = reader.ReadBoolean();
            }

            header.invasionDelay = reader.ReadInt32();
            header.invasionSize = reader.ReadInt32();
            header.invasionType = reader.ReadInt32();
            header.invasionPointX = reader.ReadDouble();
        }
        else
            ret = false;
        return ret;
    }

    bool loadConfig(QString configName, Configuration &config)
    {
        QFile file(QDir::currentPath() + "/" + configName + ".cfg");
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            return false;
        }

        QTextStream stream(&file);
        while(true)
        {
            QString line = stream.readLine();
            if(line.isEmpty() || line.isNull() || stream.atEnd())
                break;
            if(!line.contains("#")) //is a comment (first line); ignore
            {
                if(line[0] == '@') //Configuration.name
                    config.name = right(line, '@');
                else if(line.contains("maxplayers="))
                    config.maxPlayers = right(line, '=').toInt();
                else if(line.contains("world="))
                    config.world = right(line, '=');
                else if(line.contains("port="))
                    config.port = right(line, '=').toInt();
                else if(line.contains("password="))
                    config.password = right(line, '=');
                else if(line.contains("motd="))
                    config.motd = right(line, '=');
                else if(line.contains("worldpath="))
                    config.worldpath = right(line, '=');
                else if(line.contains("autocreate="))
                    config.autocreate = right(line, '=').toInt();
                else if(line.contains("worldname="))
                    config.worldname = right(line, '=');
                else if(line.contains("banlist="))
                    config.banlist = right(line, '=');
                else if(line.contains("secure="))
                    config.secure = right(line, '=').toInt();
                else if(line.contains("lang="))
                    config.lang = right(line, '=').toInt();
                else if(line.contains("priority"))
                    config.priority = right(line, '=').toInt();
            }
        }
        return true;
    }
}
