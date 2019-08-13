#ifndef LIST_MODEL_OBJECT_TYPES_H
#define LIST_MODEL_OBJECT_TYPES_H

#include <QAbstractListModel>
#include "core/game_object_description.h"

class ListModelObjectTypes : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ListModelObjectTypes(QVector<GObjectType>* pData_, QObject* perent = nullptr);
    //amount elements
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    //retune value
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
//    //set new value
//    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    //is can edit
    Qt::ItemFlags flags(const QModelIndex &index) const override;
private:
    QVector<GObjectType>* pData;
};

#endif // LIST_MODEL_OBJECT_TYPES_H
