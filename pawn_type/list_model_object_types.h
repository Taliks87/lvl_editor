#ifndef LIST_MODEL_OBJECT_TYPES_H
#define LIST_MODEL_OBJECT_TYPES_H

#include <QAbstractListModel>
#include "data/game_object.h"

class ListModelObjectTypes : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ListModelObjectTypes(GameData& data, QObject* perent = nullptr);
    ListModelObjectTypes(const ListModelObjectTypes&) = delete;
    ListModelObjectTypes& operator=(const ListModelObjectTypes&) = delete;

    void refreshLevelData(const QString& levelName);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;    
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setRolesData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    Qt::DropActions supportedDragActions() const override;
//    Qt::DropActions supportedDropActions() const override;
//    QStringList mimeTypes() const override;
    QMimeData* mimeData(const QModelIndexList &indexes) const override;

private:
    bool isPawnLimit(const QModelIndex& index) const;

    GameData* pGameData;
    GameRules* pRules;
    LevelStatistic* pLevelStutistic;
    PawnTypes* pPawnTypes;
};

#endif // LIST_MODEL_OBJECT_TYPES_H
