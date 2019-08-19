#ifndef WIDGET_OBJECTS_H
#define WIDGET_OBJECTS_H

#include <QFrame>
#include "data/game_data.h"
#include "pawn_info/table_model_pawn.h"
#include "pawn_info/item_delegate_pawn.h"

namespace Ui {
class WidgetObjects;
}

class WidgetObjects : public QFrame
{
    Q_OBJECT

public:
    explicit WidgetObjects(GameData& data, QWidget* parent = nullptr);
    ~WidgetObjects();

    void setLevel(const QString& levelName);
private:
    Ui::WidgetObjects* ui;
    TableModelPawn tableModelPawn;
    std::unique_ptr<ItemDelegatePawn> pDelegatePawn;
private slots:
    void select_pawn(const QModelIndex& index);
};

#endif // WIDGET_OBJECTS_H
