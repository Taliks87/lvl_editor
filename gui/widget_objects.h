#ifndef WIDGET_OBJECTS_H
#define WIDGET_OBJECTS_H

#include <QFrame>
#include "core/game_object.h"

namespace Ui {
class WidgetObjects;
}

class WidgetObjects : public QFrame
{
    Q_OBJECT

public:
    explicit WidgetObjects(GameData* pData, QWidget* parent = nullptr);
    ~WidgetObjects();

private:
    Ui::WidgetObjects *ui;
};

#endif // WIDGET_OBJECTS_H
