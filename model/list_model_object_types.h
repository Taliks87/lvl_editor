#ifndef LIST_MODEL_OBJECT_TYPES_H
#define LIST_MODEL_OBJECT_TYPES_H

#include <QAbstractListModel>
#include "core/game_object.h"

class ListModelObjectTypes : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ListModelObjectTypes(GameData& data, QObject* perent = nullptr);
    ListModelObjectTypes(const ListModelObjectTypes&) = delete;
    ListModelObjectTypes& operator=(const ListModelObjectTypes&) = delete;

    //amount elements
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    //retune value
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
//    //set new value
//    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    //is can edit
    bool setRolesData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    Qt::DropActions supportedDragActions() const override;
//    Qt::DropActions supportedDropActions() const override;
//    QStringList mimeTypes() const override;
    QMimeData* mimeData(const QModelIndexList &indexes) const override;

private:    
    GameRules* pRules;
    PawnTypes* pPawnTypes;
};

#endif // LIST_MODEL_OBJECT_TYPES_H
