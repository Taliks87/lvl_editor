#ifndef WIDGET_OBJECT_TYPES_H
#define WIDGET_OBJECT_TYPES_H

#include <QFrame>
#include "pawn_type/list_model_object_types.h"
#include "data/game_data.h"

namespace Ui {
class WidgetObjectTypes;
}

class WidgetObjectTypes : public QFrame
{
    Q_OBJECT

public:
    explicit WidgetObjectTypes(GameData& data, QWidget *parent = nullptr);
    WidgetObjectTypes(const WidgetObjectTypes&) = delete;
    WidgetObjectTypes& operator=(const WidgetObjectTypes&) = delete;
    ~WidgetObjectTypes();

    void refreshData();
    void setLevel(const QString& levelName);

private:
    Ui::WidgetObjectTypes* ui;
    ListModelObjectTypes listModelObjectTypes;
};

#endif // WIDGET_OBJECT_TYPES_H
