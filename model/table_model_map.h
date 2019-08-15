#ifndef TABLE_MODEL_MAP_H
#define TABLE_MODEL_MAP_H

#include <QAbstractTableModel>
#include "core/game_object.h"

class TableModelMap : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TableModelMap(GameData& data, QObject* perent = nullptr);
    TableModelMap(const TableModelMap&) = delete;
    TableModelMap& operator=(const TableModelMap&) = delete;

    void refreshLevelMap(const QString& levelName);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setRolesData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    Qt::DropActions supportedDragActions() const override;
    QStringList mimeTypes() const override;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;

private:
    GameData* pGameData;
    GameRules* pRules;
    PawnTypes* pPawnTypes;
    LevelMap* pLevelMaps;
};

#endif // TABLE_MODEL_MAP_H
