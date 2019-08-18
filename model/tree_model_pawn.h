#ifndef TREE_MODEL_PAWN_H
#define TREE_MODEL_PAWN_H

#include <QAbstractTableModel>
#include <QStyleOptionViewItem>
#include <QStyledItemDelegate>
#include <QSlider>
#include <QComboBox>
#include <QSpinBox>
#include <QDebug>
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

class ItemDelegatePawn: public QStyledItemDelegate{
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        QVariant value = index.data(Qt::WhatsThisPropertyRole);

        if(value.type() == QVariant::StringList)
        {
            QComboBox* comboBox = new QComboBox(parent);
            comboBox->setAttribute( Qt::WA_DeleteOnClose );
            comboBox->setAutoFillBackground(true);
            comboBox->addItems(value.toStringList());
            return comboBox;
        } else if (value.type() == QVariant::Point) {
            QSpinBox* spinBox = new QSpinBox(parent);
            spinBox->setAttribute( Qt::WA_DeleteOnClose );
            spinBox->setAutoFillBackground(true);
            QPoint range = value.toPoint();
            spinBox->setRange(range.x(), range.y());//x - from, y - to
            return spinBox;
        } else if (value.type() == QVariant::PointF) {
            QDoubleSpinBox* spinBox = new QDoubleSpinBox(parent);
            spinBox->setAttribute( Qt::WA_DeleteOnClose );
            spinBox->setAutoFillBackground(true);
            QPointF range = value.toPoint();
            spinBox->setRange(range.x(), range.y());//x - from, y - to
            return spinBox;
        }

        return QStyledItemDelegate::createEditor(parent, option, index);
    }

    void setEditorData(QWidget *editor, const QModelIndex &index) const override
    {
        QStyledItemDelegate::setEditorData(editor, index);
    }

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override
    {
        QVariant value = index.data(Qt::WhatsThisPropertyRole);
        if(value.type() == QVariant::StringList)
        {
            QComboBox* comboBox = dynamic_cast<QComboBox*>(editor);
            if(comboBox)
            {
                qWarning() << comboBox->currentIndex() << comboBox->itemText(comboBox->currentIndex());
                model->setRolesData(index, comboBox->itemText(comboBox->currentIndex()));
            } else {
                qWarning() << "wrong widget";
            }
        } else {
            QStyledItemDelegate::setModelData(editor, model, index);
        }
    }

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        editor->setGeometry(option.rect);
    }
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        QStyledItemDelegate::paint(painter, option, index);
    }
};




#endif // TREE_MODEL_PAWN_H
