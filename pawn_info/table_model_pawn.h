#ifndef TREE_MODEL_PAWN_H
#define TREE_MODEL_PAWN_H

#include <QAbstractTableModel>
#include "data/game_object.h"

class TableModelPawn : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum {
        TYPE_NAME_FIELD = 0,
        POSITION_FIELD,
        NAME_FIELD,
        AMOUNT_COMMON_FIELD
    };

    explicit TableModelPawn(GameData& data, QObject* perent = nullptr);
    TableModelPawn(const TableModelPawn&) = delete;
    TableModelPawn& operator=(const TableModelPawn&) = delete;

    void refreshLevelData(const QString& levelName);
    void selectPawn(const QModelIndex& index);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setRolesData(const QModelIndex& index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    GameData* pGameData;
    PawnTypes* pPawnTypes;
    LevelMap* pLevelMaps;
    GamePawn* pSelectedPawn;
    FieldDescriptions* pFieldDescriptions;
    QPoint pawnPos;
};

#endif // TREE_MODEL_PAWN_H
