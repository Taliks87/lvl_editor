#ifndef TABLE_MODEL_MAP_H
#define TABLE_MODEL_MAP_H

#include <QAbstractTableModel>
#include <QEvent>
#include <QMouseEvent>
#include "core/game_object.h"

class TableModelMap : public QAbstractTableModel
{
    Q_OBJECT
public:

    explicit TableModelMap(GameData& data, QObject* perent = nullptr);
    TableModelMap(const TableModelMap&) = delete;
    TableModelMap& operator=(const TableModelMap&) = delete;

    void refreshLevelData(const QString& levelName);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setRolesData(const QModelIndex& index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    Qt::DropActions supportedDragActions() const override;
    QStringList mimeTypes() const override;
    QMimeData* mimeData(const QModelIndexList& indexes) const override;
    bool canDropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const override;
    bool dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;
signals:
    void change_completed(const QModelIndex& index);

private:
    GameData* pGameData;
    GameRules* pRules;
    PawnTypes* pPawnTypes;
    LevelMap* pLevelMaps;
    LevelStatistic* pLevelStutistic;
    const QStringList mimeList;
};

#include <QStyledItemDelegate>

class ItemDelegateMap: public QStyledItemDelegate{
public:
    using QStyledItemDelegate::QStyledItemDelegate;
protected:
    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const override
    {
        QStyledItemDelegate::initStyleOption(option, index);
        option->decorationPosition = QStyleOptionViewItem::Top;
    }

    bool editorEvent( QEvent * event, QAbstractItemModel * model, const QStyleOptionViewItem & option, const QModelIndex & index ) override
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent* me = dynamic_cast<QMouseEvent*>(event);
            if( me->button() == Qt::MidButton )
            {
                QStyleOptionViewItem opt = option;
                model->setRolesData(index, QVariant());
            }
        }

        return QStyledItemDelegate::editorEvent(event, model, option, index);
    }
};

#endif // TABLE_MODEL_MAP_H
