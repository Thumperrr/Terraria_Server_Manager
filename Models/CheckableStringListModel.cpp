#include "CheckableStringListModel.h"

CheckableStringListModel::CheckableStringListModel(QObject *parent) : QAbstractListModel(parent)
{
}
CheckableStringListModel::CheckableStringListModel(const QStringList &strings, QObject *parent)
    : QAbstractListModel(parent)
{
    QString str;
    foreach(str, strings)
        list.push_back(CheckableStringListItem(str, Qt::Unchecked));
}

int CheckableStringListModel::rowCount(const QModelIndex &parent) const
{
    return list.size();
}

QVariant CheckableStringListModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    if(index.row() > rowCount())
        return QVariant();
    if(role == Qt::DisplayRole)
        return list[index.row()].text;
    if(role == Qt::CheckStateRole)
        return list[index.row()].checkState;
    return QVariant();
}

bool CheckableStringListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
        return false;
    if(index.row() > rowCount())
        return false;

    if(role == Qt::DisplayRole)
    {
        list[index.row()].text = value.toString();
        emit dataChanged(index, index);
    }
    if(role == Qt::CheckStateRole)
    {
        list[index.row()].checkState = static_cast<Qt::CheckState>(value.toUInt());
        emit dataChanged(index, index);
    }
    return true;
}

Qt::ItemFlags CheckableStringListModel::flags(const QModelIndex &index) const
{
    return QAbstractListModel::flags(index) | Qt::ItemIsUserCheckable;
}

void CheckableStringListModel::setStringList(QStringList &l)
{
    list.clear();
    QString str;
    foreach(str, l)
        list.push_back(CheckableStringListItem(str, Qt::Unchecked));
    emit dataChanged(this->index(0), this->index(rowCount()));
}

QStringList CheckableStringListModel::getCheckedItems()
{
    QStringList ret;
    std::vector<CheckableStringListItem>::iterator it;
    for(it = list.begin(); it != list.end(); ++it)
        if(it->checkState == Qt::Checked)
            ret.push_back(it->text);
    return ret;
}
