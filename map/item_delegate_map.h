#ifndef ITEM_DELEGATE_MAP_H
#define ITEM_DELEGATE_MAP_H

#include <QStyledItemDelegate>

class ItemDelegateMap: public QStyledItemDelegate{
public:
    using QStyledItemDelegate::QStyledItemDelegate;
protected:
    void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) const override;
    bool editorEvent( QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index ) override;
};

#endif // ITEM_DELEGATE_MAP_H
