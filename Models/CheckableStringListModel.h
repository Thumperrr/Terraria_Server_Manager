#ifndef ADAPTEDSTRINGLISTMODEL_H
#define ADAPTEDSTRINGLISTMODEL_H

#include <QAbstractListModel>
#include <QVariant>
#include <QStringList>
#include <vector>

struct CheckableStringListItem
{
    QString text;
    Qt::CheckState checkState;
    CheckableStringListItem() {}
    CheckableStringListItem(QString t, Qt::CheckState c) : text(t), checkState(c) {}
};

class CheckableStringListModel : public QAbstractListModel
{
public:
    CheckableStringListModel(QObject *parent = 0);
    CheckableStringListModel(const QStringList &strings, QObject *parent = 0);

    //Reimplemented virtual functions
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    //Functions specific to this model
    void setStringList(QStringList &l); //set string list. Everything defaults to unchecked.
    QStringList getCheckedItems(); //returns a stringlist of all checked items
private:
    std::vector<CheckableStringListItem> list;
};

#endif // ADAPTEDSTRINGLISTMODEL_H
