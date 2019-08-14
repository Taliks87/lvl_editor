#ifndef WIDGET_OBJECT_TYPES_H
#define WIDGET_OBJECT_TYPES_H

#include <QFrame>
#include "model/list_model_object_types.h"
#include "core/game_object.h"

namespace Ui {
class WidgetObjectTypes;
}

class WidgetObjectTypes : public QFrame
{
    Q_OBJECT

public:
    explicit WidgetObjectTypes(GameData* pData, QWidget *parent = nullptr);
    void refreshData();
    ~WidgetObjectTypes();

private:
    Ui::WidgetObjectTypes *ui;
    ListModelObjectTypes listModelObjectTypes;
};

#endif // WIDGET_OBJECT_TYPES_H
