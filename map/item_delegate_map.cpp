#include "map/item_delegate_map.h"
#include <QEvent>
#include <QMouseEvent>

void ItemDelegateMap::initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) const
{
    QStyledItemDelegate::initStyleOption(option, index);
    option->decorationPosition = QStyleOptionViewItem::Top;
}

bool ItemDelegateMap::editorEvent( QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index )
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
