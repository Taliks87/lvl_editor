#ifndef TREE_MODEL_PAWN_H
#define TREE_MODEL_PAWN_H

#include <QAbstractTableModel>
#include <QStyleOptionViewItem>
#include <QStyledItemDelegate>
#include "core/game_object.h"

class TreeModelPawn : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum {
        TYPE_NAME_FIELD = 0,
        POSITION_FIELD,
        NAME_FIELD,
        AMOUNT_COMMON_FIELD
    };

    explicit TreeModelPawn(GameData& data, QObject* perent = nullptr);
    TreeModelPawn(const TreeModelPawn&) = delete;
    TreeModelPawn& operator=(const TreeModelPawn&) = delete;

    void refreshLevelData(const QString& levelName);
    void selectPawn(const QModelIndex& index);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setRolesData(const QModelIndex &/*index*/, const QVariant &/*value*/, int /*role*/) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    GameData* pGameData;
    PawnTypes* pPawnTypes;
    LevelMap* pLevelMaps;
    GamePawn* pSelectPawn;
    QPoint pawnPos;
};

class ItemDelegatePawn: public QStyledItemDelegate{
public:
    using QStyledItemDelegate::QStyledItemDelegate;
protected:
    QWidget* createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override
    {
//        int type = index.data(MyTypeRole).toInt();

//        switch (type)
//        {
//        case DT_Text:
//            return new QLinedEdit;
//        case DT_Checkbox:
//            return new QCheckBox;
//        case DT_Combo:
//            return new QComboBox;
//        default:
//            return QItemDelegate::createEditor(parent, option, index);
//        }
    }
};




#endif // TREE_MODEL_PAWN_H
