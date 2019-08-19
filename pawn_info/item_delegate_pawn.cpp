#include "item_delegate_pawn.h"

#include <QComboBox>
#include <QSpinBox>
#include <QDebug>

QWidget* ItemDelegatePawn::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
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

void ItemDelegatePawn::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QStyledItemDelegate::setEditorData(editor, index);
}

void ItemDelegatePawn::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QVariant value = index.data(Qt::WhatsThisPropertyRole);
    if(value.type() == QVariant::StringList)
    {
        QComboBox* comboBox = dynamic_cast<QComboBox*>(editor);
        if(comboBox)
        {
            model->setRolesData(index, comboBox->itemText(comboBox->currentIndex()));
        } else {
            qWarning() << "wrong widget";
        }
    } else {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

void ItemDelegatePawn::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& /*index*/) const
{
    editor->setGeometry(option.rect);
}

void ItemDelegatePawn::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QStyledItemDelegate::paint(painter, option, index);
}
