#ifndef WIDGET_MAP_H
#define WIDGET_MAP_H

#include <QFrame>
#include "core/game_object.h"

namespace Ui {
class WidgetMap;
}

class WidgetMap : public QFrame
{
    Q_OBJECT

public:
    explicit WidgetMap(GameData* pData, QWidget *parent = nullptr);
    ~WidgetMap();

private:
    Ui::WidgetMap *ui;
};

#endif // WIDGET_MAP_H
