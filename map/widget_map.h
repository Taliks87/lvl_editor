#ifndef WIDGET_MAP_H
#define WIDGET_MAP_H

#include <QFrame>
#include "data/game_data.h"
#include "map/table_model_map.h"
#include "map/item_delegate_map.h"

namespace Ui {
class WidgetMap;
}

class WidgetMap : public QFrame
{
    Q_OBJECT

public:
    explicit WidgetMap(GameData& data, QWidget *parent = nullptr);
    WidgetMap(const WidgetMap&) = delete;
    WidgetMap& operator=(const WidgetMap&) = delete;
    ~WidgetMap();

    void setLevel(const QString& levelName);

signals:
    void select_pawn(const QModelIndex& index);
private slots:
    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::WidgetMap* ui;
    TableModelMap tableModelMap;
    std::unique_ptr<ItemDelegateMap> pDelegateMap;
};

#endif // WIDGET_MAP_H
