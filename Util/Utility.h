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
#include <QRect>
#include <QPoint>
#include <QTextStream>
#include <QMessageBox>
#include "BinaryReader.h"

namespace Utility
{
    struct WorldHeader
    {
        int releaseNumber;
        QString name;
        int id;
        QRect worldCoords;
        QPoint maxTiles;
        QPoint spawnPoint;
        double surfaceLevel;
        double rockLayer;
        double temporaryTime;
        bool isDayTime;
        int moonPhase;
        bool isBloodMoon;
        QPoint dungeonPoint;
        bool isBoss1Dead;
        bool isBoss2Dead;
        bool isBoss3Dead;
            bool isGoblinSaved;
            bool isWizardSaved;
            bool isMechanicSaved;
            bool isGoblinArmyDefeated;
            bool isClownDefeated;
            bool isFrostDefeated;
        bool isShadowOrbSmashed;
        bool isMeteorSpawned;
        unsigned char shadowOrbsSmashed;
            int altarsDestroyed;
            bool hardMode;
        int invasionDelay;
        int invasionSize;
        int invasionType;
        double invasionPointX;
    };

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

    QString left(QString line, char separator);
    QString right(QString line, char separator);
    QString word(QString line, int wordNumber = 1);
    QStringList splitString(QString line, QString separator = " ");
    QStringList getDirectoryEntryList(QStringList nameFilters, QString path = QDir::currentPath());
    bool getWorldHeader(QString path, WorldHeader &header);
    bool loadConfig(QString configName, Configuration &config);
}

#endif // UTILITY_H
