#ifndef WIDGET_MAP_H
#define WIDGET_MAP_H

#include <QFrame>
#include "core/game_object.h"
#include "model/table_model_map.h"

namespace Ui {
class WidgetMap;
}

class WidgetMap : public QFrame
{
    Q_OBJECT

public:
    explicit WidgetMap(GameData& data, QWidget *parent = nullptr);
    ~WidgetMap();

    void setLevel(const QString& levelName);

private:
    Ui::WidgetMap *ui;
    TableModelMap tableModelMap;
};

#endif // WIDGET_MAP_H
